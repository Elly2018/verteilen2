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
#include <verteilen2client/api/api.h>
#include <verteilen2client/db/local_record.h>

namespace verteilen2::client {

    static void register_connect_request(App_data& app_data) {
        CROW_ROUTE(app_data.app, "/api/connect_ws_server")
        .methods(crow::HTTPMethod::POST)
        ([&app_data](const crow::request& req) {
            crow::json::rvalue json_data = crow::json::load(req.body);

            if (!json_data) {
                return crow::response(400, "Invalid JSON payload");
            }

            if (!json_data.has("server-address")) {
                return crow::response(400, "Missing required key: server-address");
            }

            const auto& server_address = json_data["server-address"];

            return crow::response(200, "YES");
        });
    }

    static void register_job_message_getter(App_data& app_data) {
        CROW_ROUTE(app_data.app, "/api/get_job_detail/<path>/<path>")
        .methods(crow::HTTPMethod::GET)
        ([&app_data](const crow::request& req, const std::string& path1, const std::string& path2) {
            std::string job_uuid = path1;
            std::string datetime = path2;
            return crow::response(200, "YES");
        });
    }

    void register_connect_server_ws_route(App_data& app_data) {
        
        register_connect_request(app_data);
        register_job_message_getter(app_data);

    }

}
