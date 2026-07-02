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
#include "ws.h"
#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>
#include "../db/local_record.h"

using json = nlohmann::json;

namespace verteilen2::client {

    static void register_realtime_handle_request(WebServer& app) {
        CROW_WEBSOCKET_ROUTE(app, "/ws")
        .onopen([&](crow::websocket::connection& conn){
            spdlog::info("[web] websocket connection successfully established.");
            
        })
        .onclose([&](crow::websocket::connection& conn, const std::string& reason, uint16_t){
            spdlog::info("[web] websocket connection successfully closed.");
        })
        .onmessage([&](crow::websocket::connection&, const std::string& data, bool is_binary){
            if(!json::accept(data) || is_binary) return;
        });
    }

    void register_ws_route(WebServer& app) {
        
        register_realtime_handle_request(app);

    }

}
