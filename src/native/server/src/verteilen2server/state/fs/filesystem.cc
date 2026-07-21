/**
    MIT License

    Copyright (c) 2026 ZhuElly

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
 */
#include <verteilen2server/state/fs/filesystem.h>
#include <verteilen2/path.h>
#include <spdlog/spdlog.h>

namespace verteilen2::server {

    class UpdateListener : public efsw::FileWatchListener {
    public:
        void handleFileAction( efsw::WatchID watchid, const std::string& dir,
                            const std::string& filename, efsw::Action action,
                            const std::string& oldFilename ) override {
            switch ( action ) {
                case efsw::Actions::Add:
                    std::cout << "DIR (" << dir << ") FILE (" << filename << ") has event Added"
                            << std::endl;
                    break;
                case efsw::Actions::Delete:
                    std::cout << "DIR (" << dir << ") FILE (" << filename << ") has event Delete"
                            << std::endl;
                    break;
                case efsw::Actions::Modified:
                    std::cout << "DIR (" << dir << ") FILE (" << filename << ") has event Modified"
                            << std::endl;
                    break;
                case efsw::Actions::Moved:
                    std::cout << "DIR (" << dir << ") FILE (" << filename << ") has event Moved from ("
                            << oldFilename << ")" << std::endl;
                    break;
                default:
                    std::cout << "Should never happen!" << std::endl;
            }
        }
    };

    void fs_init_filesystem(App_data& app_data) {
        fs::path p = path_get_workpath(App_type::Server);
        p /= "fs";
        if(!fs::exists(p)) fs::create_directories(p);
        for(const auto& subdir : fs::directory_iterator(p)){
            std::string foldername = subdir.path().filename();
            spdlog::info("[FS Init] Detect file system folder: {}", foldername);
            fs_create_filesystem(app_data, foldername);
        }
    }

    bool fs_create_filesystem(App_data& app_data, std::string uuid) {
        if(uuid.size() == 0) {
            spdlog::warn("[FS Create Failed] UUID cannot be empty");
            return false;
        }
        fs::path p = path_get_workpath(App_type::Server);
        p /= "fs";
        p /= uuid;
        if(!fs::exists(p)) {
            spdlog::warn("[FS Create] Create the folder: {}", uuid);
            fs::create_directories(p);
        }
        std::string target_path = p.string();
        int32_t find = fs_worker_get_index_by_path(app_data.fsworker, target_path);

        if(find != -1) {
            spdlog::warn("[FS Create] File system already exist: {}", uuid);
            return false;
        }
        int32_t ava = fs_worker_get_idle(app_data.fsworker);
        if(ava == -1) {
            spdlog::error("[FS Create Failed] All file system worker has been taken");
            return false;
        }
        spdlog::info("[FS Create] {}", uuid);

        app_data.fsworker[ava].path = target_path;
        app_data.fsworker[ava].watcher = new efsw::FileWatcher();
        app_data.fsworker[ava].listener = new UpdateListener();
        app_data.fsworker[ava].watch_ID = app_data.fsworker[ava].watcher->addWatch(target_path, app_data.fsworker[ava].listener, true);
        app_data.fsworker[ava].watcher->watch();
        app_data.fsworker[ava].vaild = true;

        return true;
    }

    bool fs_delete_filesystem(App_data& app_data, std::string uuid) {
        if(uuid.size() == 0) {
            spdlog::warn("[FS Create Failed] UUID cannot be empty");
            return false;
        } 
        fs::path p = path_get_workpath(App_type::Server);
        p /= "fs";
        p /= uuid;
        if(!fs::exists(p)) {
            spdlog::warn("[FS Delete] The file system mount folder does not exist: {}", uuid);
            return false;
        }
        std::string target_path = p.string();
        int32_t find = fs_worker_get_index_by_path(app_data.fsworker, target_path);

        if(find == -1) {
            spdlog::warn("[FS Delete] Cannot find the file system worker: {}", uuid);
            return true;
        }
        spdlog::info("[FS Delete] {}", uuid);

        app_data.fsworker[find].path.clear();
        app_data.fsworker[find].watcher->removeWatch(app_data.fsworker[find].watch_ID);
        delete app_data.fsworker[find].listener;
        delete app_data.fsworker[find].watcher;
        app_data.fsworker[find].vaild = false;

        return true;
    }

    std::vector<std::string> fs_get_all_filesystem(App_data& app_data) {
        std::vector<std::string> a = std::vector<std::string>();
        for(auto& worker : app_data.fsworker){
            if(worker.vaild) {
                a.push_back(fs::path(worker.path).filename());
            }
        }
        return a;
    }

};