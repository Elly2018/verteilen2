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
#include <spdlog/spdlog.h>
#include <uuid.h>
#include <nlohmann/json.hpp>
#include "../config.h"
#include "../db/local_record.h"
#include "../state/analyzer.h"

using json = nlohmann::json;

namespace verteilen2::client {

    static std::string generate_uuid(){
        std::random_device rd;
        std::array<unsigned int, 8> seed_data;
        std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
        std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
        std::mt19937 generator(seq);
        
        uuids::uuid_random_generator gen(&generator);
        uuids::uuid id = gen();
        std::string uuid_str = uuids::to_string(id);

        return uuid_str;
    }

    static crow::mustache::context json_to_mustache(const nlohmann::json& j) {
        crow::mustache::context ctx;

        if (j.is_object()) {
            for (auto& [key, value] : j.items()) {
                if (value.is_object() || value.is_array()) {
                    ctx[key] = json_to_mustache(value);
                } else if (value.is_string()) {
                    ctx[key] = value.get<std::string>();
                } else if (value.is_number_integer()) {
                    ctx[key] = value.get<int64_t>();
                } else if (value.is_number_float()) {
                    ctx[key] = value.get<double>();
                } else if (value.is_boolean()) {
                    ctx[key] = value.get<bool>();
                } else if (value.is_null()) {
                    ctx[key] = ""; // Mustache handles empty strings nicely
                }
            }
        } else if (j.is_array()) {
            // Create an array context tree for loop blocks
            std::vector<crow::mustache::context> vec;
            for (const auto& element : j) {
                vec.push_back(json_to_mustache(element));
            }
            // Assign the sequence matrix back
            ctx = std::move(vec);
        }

        return ctx;
    }

    static void template_setting(WebServer& app, const crow::request& req, crow::mustache::context& ctx) {
        ctx["current_server_address"] = "ws://127.0.0.1/ws/client";
        ctx["current_maximum_execution"] = 20;
    }

    static void template_log(WebServer& app, const crow::request& req, crow::mustache::context& ctx, Session::context& session_ctx) {

        json res = json::object();
        get_latest_log_table(Init_log_amount, res);

        crow::mustache::context log_rows = json_to_mustache(res);

        session_ctx.set("rows", log_rows["data"].dump());
        ctx["log_rows"] = std::move(log_rows["data"]);
        ctx["updating"] = session_ctx.contains("update") && session_ctx.get<bool>("update");
    }

    static void register_template(WebServer& app) {
        CROW_ROUTE(app, "/template/<path>")
        .methods(crow::HTTPMethod::GET)
        ([&app](const crow::request& req, const std::string& path) {
            crow::mustache::context ctx;
            std::string filename = path;
            Session::context& session_ctx = app.get_context<Session>(req);
            crow::CookieParser::context& cookie_ctx = app.get_context<crow::CookieParser>(req);

            if(cookie_ctx.get_cookie("key").empty()){
                cookie_ctx.set_cookie("key", generate_uuid()).path("/").httponly();
            }
            
            if(path.starts_with("setting")) {
                template_setting(app, req, ctx);
            }
            else if(path.starts_with("log")) {
                if(path == "log-clear") {
                    drop_log_table();
                }
                else if (path == "log-start-update") {
                    session_ctx.set<bool>("update", true);
                }
                else if (path == "log-stop-update") {
                    session_ctx.set<bool>("update", false);
                }
                filename = "log";
                template_log(app, req, ctx, session_ctx);
            }

            auto template_page = crow::mustache::load("template/" + filename + ".html");

            return template_page.render(ctx);
        });
    }

    void register_template_route(WebServer& app) {

        register_template(app);

    }

}