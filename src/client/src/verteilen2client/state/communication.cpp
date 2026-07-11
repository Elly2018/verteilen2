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
#include <verteilen2/env.h>
#include <verteilen2/network.h>
#include <verteilen2/proto_gen/struct_header.pb.h>
#include <verteilen2client/data/appdata.h>
#include <verteilen2client/state/analyzer.h>
#include <verteilen2client/state/execute.h>
#include <verteilen2client/state/fs/filesystem.h>

namespace verteilen2::client {

    constexpr uint32_t KCP_CONV_ID = 0x11223344;

    void create_kcp_server(App_data& app_data) {
        fs_init_filesystem();

        app_data.server.socket_fd = app_data.server.kcp_server.createsocket(network_get_port_available(kcp_port));
        if(app_data.server.socket_fd < 0) {
            spdlog::error("app_data.server.socket_fd create failed");
            return;
        }

        app_data.server.kcp_server.onMessage = [&](const hv::SocketChannelPtr& channel, hv::Buffer* buf) {
            std::string message = std::string(buf->size(), buf->len);
            if(message == "connect") {
                if(app_data.server_target && app_data.server_target->isConnected()){
                    spdlog::warn("[KCP Message] Recevied repeat connect packet from server");
                    app_data.server_target->write("already connected");
                }else{
                    spdlog::info("[KCP Message] Successfully connect to server !");
                    app_data.server_target = channel;
                    app_data.server_target->write("success");
                }
            } else if(message == "disconnect") {
                spdlog::info("[KCP Message] Recevied disconnect from server");
            } else {
                if(app_data.server_target == channel){
                    google::protobuf::Arena arena;
                    RawData* r = google::protobuf::Arena::CreateMessage<RawData>(&arena);
                    if(r->ParseFromArray(buf->data(), buf->len)) {
                        analysis(app_data, r);
                    }
                }
            }
        };

        app_data.server.kcp_server.start();
    }

    void shutdown_kcp_server(App_data& app_data) {
        app_data.server.kcp_server.stop();
    }

}
