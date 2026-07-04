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
#include <verteilen2server/api/static.h>
#include <filesystem>
#include <spdlog/spdlog.h>
#include <crow.h>
#include <verteilen2/io.h>
#include <verteilen2server/config.h>

namespace verteilen2::server {

    static void register_index(WebServer& app) {
        CROW_ROUTE(app, "/")
        .methods(crow::HTTPMethod::GET)
        ([]() {
            crow::mustache::context ctx;
            
            ctx["title"] = "Testing Title";

            auto template_page = crow::mustache::load("index.html");

            return template_page.render(ctx);
        });
    }

    static void register_resource(WebServer& app) {
        CROW_ROUTE(app, "/css/<path>")
        .methods(crow::HTTPMethod::GET)
        ([](const std::string& path) {
            crow::response res;
            std::filesystem::path current_cwd = std::filesystem::current_path();
            std::filesystem::path _p = current_cwd / std::string(VERTEILEN2_STATIC_DIRECTORY) / "css" / path;
            std::string p = _p.lexically_normal().string();
            std::string buffer;
            if(!read_all_text(p, buffer)) res.code = 404;
            
            res.set_header("Content-Type", "text/css");
            res.body = buffer;
            res.code = 200;
            return res;
        });

        CROW_ROUTE(app, "/js/<path>")
        .methods(crow::HTTPMethod::GET)
        ([](const std::string& path) {
            crow::response res;
            std::filesystem::path current_cwd = std::filesystem::current_path();
            std::filesystem::path _p = current_cwd / std::string(VERTEILEN2_STATIC_DIRECTORY) / "js" / path;
            std::string p = _p.lexically_normal().string();
            std::string buffer;
            if(!read_all_text(p, buffer)) res.code = 404;
            
            res.set_header("Content-Type", "application/javascript");
            res.body = buffer;
            res.code = 200;
            return res;
        });

        CROW_ROUTE(app, "/favicon.ico")
        .methods(crow::HTTPMethod::GET)
        ([]() {
            crow::response res;
            std::filesystem::path current_cwd = std::filesystem::current_path();
            std::filesystem::path _p = current_cwd / std::string(VERTEILEN2_STATIC_DIRECTORY) / "favicon.ico";
            std::string p = _p.lexically_normal().string();
            std::string buffer;
            if(!read_all_text(p, buffer)) res.code = 404;
            
            res.set_header("Content-Type", "image/x-icon");
            res.body = buffer;
            res.code = 200;
            return res;
        });
    }

    void register_static_route(WebServer& app) {

        register_index(app);
        register_resource(app);
        
    }

}