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
#include <verteilen2client/state/communication.h>
#include <spdlog/spdlog.h>
#include <hv/WebSocketClient.h>
#include <hv/WebSocketServer.h>
#include <verteilen2/proto_gen/header.pb-c.h>
#include <verteilen2client/data/appdata.h>
#include <verteilen2client/state/analyzer.h>
#include <verteilen2client/state/execute.h>

namespace verteilen2::client {

    void create_websocket_server(App_data& app_data) {
        app_data.ws_server = hv::WebSocketServer();
        app_data.ws_server.run("12808", false);
    }

    void create_websocket_connection(App_data& app_data, const std::string address) {
        reconn_setting_t reconn;
        reconn.min_delay = 1000;
        reconn.max_delay = 10000;
        reconn.delay_policy = 2;
        reconn.max_retry_cnt = 5;

        app_data.ws_client.setReconnect(&reconn);
        
        app_data.ws_client.onopen = [&app_data]() {
            app_data.server_alive = true;
        };
        app_data.ws_client.onmessage = [&app_data](const std::string& msg) {
            const uint8_t* raw_data = reinterpret_cast<const uint8_t*>(msg.data());
            uint64_t data_len = msg.size();
            Verteilen2__RawData* raw_msg = verteilen2__raw_data__unpack(NULL, msg.size(), raw_data);

            if (raw_msg == NULL) {
                spdlog::error("Failed to unpack raw network frame via Protobuf-C");
                return;
            }

            analysis(app_data, *raw_msg);
            verteilen2__raw_data__free_unpacked(raw_msg, NULL);
        };  
        app_data.ws_client.onclose = [&app_data]() {
            app_data.server_alive = false;
        };

        app_data.ws_client.open(address.c_str());
        app_data.ws_client.start();
    }

}
