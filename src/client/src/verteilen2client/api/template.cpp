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
#include <verteilen2client/api/template.h>
#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>
#include <verteilen2/uuid.h>
#include <verteilen2client/config.h>
#include <verteilen2client/db/local_record.h>
#include <verteilen2client/state/analyzer.h>

using json = nlohmann::json;

namespace verteilen2::client {

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

    static void template_setting(App_data& app_data, const crow::request& req, crow::mustache::context& ctx) {
        ctx["current_server_address"] = "ws://127.0.0.1/ws/client";
        ctx["current_maximum_execution"] = 20;
    }

    static void template_viewer(App_data& app_data, const crow::request& req, crow::mustache::context& ctx) {

    }

    static void template_log(App_data& app_data, const crow::request& req, crow::mustache::context& ctx, Session::context& session_ctx) {

        json res = json::object();
        get_latest_log_table(app_data.db_getter(), Init_log_amount, res);

        crow::mustache::context log_rows = json_to_mustache(res);

        session_ctx.set("rows", log_rows["data"].dump());
        ctx["log_rows"] = std::move(log_rows["data"]);
        ctx["updating"] = session_ctx.contains("update") && session_ctx.get<bool>("update");
    }

    static void register_template(App_data& app_data) {
        CROW_ROUTE(app_data.app, "/template/<path>")
        .methods(crow::HTTPMethod::GET)
        ([&app_data](const crow::request& req, const std::string& path) {
            crow::mustache::context ctx;
            std::string filename = path;
            Session::context& session_ctx = app_data.app.get_context<Session>(req);
            crow::CookieParser::context& cookie_ctx = app_data.app.get_context<crow::CookieParser>(req);

            if(cookie_ctx.get_cookie("key").empty()){
                cookie_ctx.set_cookie("key", generate_uuid()).path("/").httponly();
            }
            
            if(path.starts_with("setting")) {
                template_setting(app_data, req, ctx);
            }
            if(path.starts_with("viewer")) {
                template_viewer(app_data, req, ctx);
            }
            else if(path.starts_with("log")) {
                if(path == "log-clear") {
                    drop_log_table(app_data.db_getter());
                }
                else if (path == "log-start-update") {
                    session_ctx.set<bool>("update", true);
                }
                else if (path == "log-stop-update") {
                    session_ctx.set<bool>("update", false);
                }
                filename = "log";
                template_log(app_data, req, ctx, session_ctx);
            }

            auto template_page = crow::mustache::load("template/" + filename + ".html");

            return template_page.render(ctx);
        });
    }

    void register_template_route(App_data& app_data) {

        register_template(app_data);

    }

}