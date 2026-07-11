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
#include <verteilen2server/api/fs.h>
#include <verteilen2/path.h>

namespace verteilen2::server {

    static void register_fs_download_request(App_data& app_data) {
        CROW_ROUTE(app_data.app, "/api/fs/<string>/<string>")
        .methods(crow::HTTPMethod::GET)
        ([&app_data](const crow::request& req, crow::response& res, const std::string uuid, const std::string filename) {
            fs::path p = path_get_workpath(App_type::Server);
            p /= "fs";
            p /= uuid;
            p /= filename;
            if(!fs::exists(p)) {
                res.code = 404;
                res.body = "Cannot find the file";
                spdlog::warn("[API FS Download] Cannot find file: {}", p.string());
                return;
            }
            
            res.add_header("Content-Disposition", "attachment; filename=\"" + p.filename().string() + "\"");
            res.add_header("Content-Type", "application/octet-stream");

            res.set_static_file_info_unsafe(p.string());
            res.end();
        });
    }

    void register_fs_route(App_data& app_data) {
        register_fs_download_request(app_data);
    }
    
}