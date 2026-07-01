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
#include "template.h"
#include <crow.h>

namespace verteilen2::client {

    static void register_homepage(crow::SimpleApp& app) {
        CROW_ROUTE(app, "/template/homepage")
        ([]() {
            crow::mustache::context ctx;
            
            ctx["title"] = "Testing Title";

            auto template_page = crow::mustache::load("template/homepage.html");

            return template_page.render(ctx);
        });
    }

    static void register_viewer(crow::SimpleApp& app) {
        CROW_ROUTE(app, "/template/viewer")
        ([]() {
            crow::mustache::context ctx;
            
            ctx["title"] = "Testing Title";

            auto template_page = crow::mustache::load("template/viewer.html");

            return template_page.render(ctx);
        });
    }

    static void register_terminal(crow::SimpleApp& app) {
        CROW_ROUTE(app, "/template/terminal")
        ([]() {
            crow::mustache::context ctx;
            
            ctx["title"] = "Testing Title";

            auto template_page = crow::mustache::load("template/terminal.html");

            return template_page.render(ctx);
        });
    }

    static void register_setting(crow::SimpleApp& app) {
        CROW_ROUTE(app, "/template/setting")
        ([]() {
            crow::mustache::context ctx;
            
            ctx["title"] = "Testing Title";

            auto template_page = crow::mustache::load("template/setting.html");

            return template_page.render(ctx);
        });
    }

    static void register_log(crow::SimpleApp& app) {
        CROW_ROUTE(app, "/template/log")
        ([]() {
            crow::mustache::context ctx;
            
            ctx["title"] = "Testing Title";

            auto template_page = crow::mustache::load("template/log.html");

            return template_page.render(ctx);
        });
    }

    void register_template_route(crow::SimpleApp& app) {

        crow::mustache::set_global_base("static/client");

        register_homepage(app);
        register_viewer(app);
        register_terminal(app);
        register_setting(app);
        register_log(app);

    }

}