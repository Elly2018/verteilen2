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
#include <verteilen2client/state/fs/filesystem.h>
#include <verteilen2/path.h>

namespace verteilen2::client {

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

    bool fs_create_filesystem(App_data& app_data, verteilen2::client::FileSystem* fs) {
        switch(fs->type()) {
            default:
            case ActionFSType::ActionFSType_CREATE:
            {
                int32_t ava = fs_worker_get_idle(app_data.fsworker);
                if(ava == -1) break;

                app_data.fsworker[ava].watcher = new efsw::FileWatcher();
                app_data.fsworker[ava].listener = new UpdateListener();
                fs::path p = path_get_workpath(App_type::Client);
                p /= "fs";
                p /= fs->fs().uuid();
                if(!fs::exists(p)) fs::create_directories(p);
                app_data.fsworker[ava].path = p.string();
                app_data.fsworker[ava].watch_ID = app_data.fsworker[ava].watcher->addWatch(p.string(), app_data.fsworker[ava].listener, true);
                app_data.fsworker[ava].watcher->watch();
                app_data.fsworker[ava].vaild = true;
                break;
            }
            case ActionFSType::ActionFSType_UPDATE:
            {
                break;
            }
        }
    }
    
    bool fs_delete_filesystem(App_data& app_data, verteilen2::client::FileSystem* fs) {
        switch(fs->type()) {
            default:
            case ActionFSType::ActionFSType_REMOVE:
            {
                break;
            }
        }
    }
    

}