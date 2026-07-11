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
#include <verteilen2server/api/api.h>
#include <verteilen2server/state/fs/filesystem.h>
#include <verteilen2server/state/communication.h>
#include <verteilen2/uuid.h>

namespace verteilen2::server {

    static void register_connect_request(App_data& app_data) {
        CROW_ROUTE(app_data.app, "/api/connect_ws_client")
        .methods(crow::HTTPMethod::POST)
        ([&app_data](const crow::request& req) {
            crow::json::rvalue json_data = crow::json::load(req.body);

            if (!json_data) {
                return crow::response(400, "Invalid JSON payload");
            }

            if (!json_data.has("client-address")) {
                return crow::response(400, "Missing required key: client-address");
            }

            const auto& client_address = json_data["client-address"];

            return crow::response(200, "YES");
        });
    }

    static void register_fs_create_request(App_data& app_data) {
        CROW_ROUTE(app_data.app, "/api/create_filesystem")
        .methods(crow::HTTPMethod::POST)
        ([&app_data](const crow::request& req) {
            std::string uuid = generate_uuid();
            
            if(fs_create_filesystem(app_data, uuid)) {
                return crow::response(200, uuid);
            }else{
                return crow::response(500, "Create filesystem failed");
            }
        });
    }

    static void register_fs_delete_request(App_data& app_data) {
        CROW_ROUTE(app_data.app, "/api/delete_filesystem")
        .methods(crow::HTTPMethod::POST)
        ([&app_data](const crow::request& req) {
            std::string uuid = generate_uuid();
            
            if(fs_delete_filesystem(app_data, uuid)) {
                return crow::response(200, uuid);
            }else{
                return crow::response(500, "Delete filesystem failed");
            }
        });
    }

    static void register_fs_delete_request(App_data& app_data) {
        CROW_ROUTE(app_data.app, "/api/connect_client")
        .methods(crow::HTTPMethod::POST)
        ([&app_data](const crow::request& req) {
            crow::json::rvalue json_data = crow::json::load(req.body);

            if (!json_data) {
                return crow::response(400, "Invalid JSON payload");
            }

            if (!json_data.has("client-address")) {
                return crow::response(400, "Missing required key: client-address");
            }

            if (!json_data.has("client-port")) {
                return crow::response(400, "Missing required key: client-port");
            }

            const auto& client_address = json_data["client-address"];
            const auto& client_port = json_data["client-port"];

            if(connect_client_kcp_server(app_data, client_address.s(), client_port.s())) {
                return crow::response(200, "Successfully send out message");
            }else{
                return crow::response(400, "Something wrong with your input value");
            }
        });
    }

    void register_api_route(App_data& app_data) {
        
        register_connect_request(app_data);
        register_fs_create_request(app_data);

    }

}
