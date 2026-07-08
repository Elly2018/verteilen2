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
#include <thread>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <ikcp.h>
#include <spdlog/spdlog.h>
#include <verteilen2/proto_gen/header.pb-c.h>
#include <verteilen2client/data/appdata.h>
#include <verteilen2client/state/analyzer.h>
#include <verteilen2client/state/execute.h>

namespace verteilen2::client {

    static int32_t udp_output(const char *buf, int len, ikcpcb *kcp, void *user) {

    }

    void create_kcp_server(App_data& app_data) {
        int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        struct sockaddr_in local_addr;
        memset(&local_addr, 0, sizeof(local_addr));
        local_addr.sin_family = AF_INET;
        local_addr.sin_addr.s_addr = INADDR_ANY;
        local_addr.sin_port = htons(12808); // Local bound port
        bind(sockfd, (struct sockaddr*)&local_addr, sizeof(local_addr));

        ikcpcb *kcp = ikcp_create(0x11223344, &sockfd);
        kcp->output = udp_output;

        ikcp_nodelay(kcp, 1, 10, 2, 1);
        ikcp_wndsize(kcp, 128, 128);
        ikcp_setmtu(kcp, 1400);

        std::string proto_bytes;
        event.SerializeToString(&proto_bytes);

        app_data.kcp_worker.state = ThreadState::Running;
        app_data.kcp_worker.worker = std::thread(update_kcp_server, std::ref(app_data));
    }

    void create_kcp_connection(App_data& app_data, const std::string address) {
        reconn_setting_t reconn;
        reconn.min_delay = 1000;
        reconn.max_delay = 10000;
        reconn.delay_policy = 2;
        reconn.max_retry_cnt = 5;

        app_data.ws_client.setReconnect(&reconn);
        
        app_data.ws_client.onopen = [&app_data]() {
            spdlog::info("Websocket to server connection has been established");
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
            spdlog::info("Websocket to server connection has been closed");
        };

        app_data.ws_client.open(address.c_str());
        app_data.ws_client.start();
    }

    void update_kcp_server(App_data& app_data) {

    }

}
