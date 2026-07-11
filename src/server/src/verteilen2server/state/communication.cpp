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
#include <verteilen2server/state/communication.h>
#include <spdlog/spdlog.h>
#include <verteilen2/env.h>
#include <verteilen2/network.h>
#include <verteilen2/proto_gen/struct_header.pb.h>
#include <verteilen2server/data/appdata.h>
#include <verteilen2server/state/fs/filesystem.h>

namespace verteilen2::server {

    constexpr uint32_t KCP_CONV_ID = 0x11223344;

    void create_kcp_server(App_data& app_data) {
        fs_init_filesystem(app_data);

        int32_t p = network_get_port_available(server_kcp_port);
        spdlog::info("[KCP Create] KCP port: {}", p);
        app_data.server.socket_fd = app_data.server.kcp_server.createsocket(p);
        
        if(app_data.server.socket_fd < 0) {
            spdlog::error("app_data.server.socket_fd create failed");
            return;
        }

        app_data.server.kcp_server.onMessage = [&](const hv::SocketChannelPtr& channel, hv::Buffer* buf) {
            std::string message((char*)buf->data(), buf->size());
            spdlog::debug("[KCP Message] Raw Data: {}", message);
            if(message == "success") {
                bool f = false;
                for(auto& i : app_data.client_targets) {
                    if(i == channel) {
                        f = true;
                        break;
                    }
                }
                if(!f){
                    spdlog::info("[KCP Message] Successfully connect to a client: {}", channel->localaddr());
                    app_data.client_targets.push_back(channel);
                }
            } else if(message == "disconnect") {
                std::string w = channel->peeraddr();
                for(int32_t i = 0; i < app_data.client_targets.size(); i++) {
                    if(app_data.client_targets.at(i) == channel) {
                        app_data.client_targets.erase(app_data.client_targets.begin() + i);
                        break;
                    }
                }
                spdlog::info("[KCP Message] Recevied disconnect from client: {}", w);
            } else {
                if(app_data.master_target == channel){
                    google::protobuf::Arena arena;
                    RawData* r = google::protobuf::Arena::CreateMessage<RawData>(&arena);
                    if(r->ParseFromArray(buf->data(), buf->len)) {
                        //analysis(app_data, r);
                    }
                }
            }
        };

        app_data.server.kcp_server.start();
    }

    void shutdown_kcp_server(App_data& app_data) {
        for(auto& channel : app_data.client_targets) {
            if(channel && channel->isConnected()) {
                channel->write("disconnect");
                channel->close();
            }
        }
        app_data.client_targets.clear();
        app_data.server.kcp_server.stop();
    }

    bool connect_client_kcp_server(App_data& app_data, std::string address, std::string port) {
        std::string msg = "connect";
        int32_t _port = server_kcp_port;

        try{
            _port = std::stoi(port);
        }
        catch (const std::invalid_argument& e) {
            spdlog::error("[KCP Create] Error: Not a valid number!");
            return false;
        } 
        catch (const std::out_of_range& e) {
            spdlog::error("[KCP Create] Error: Number is too big for a 32-bit int!");
            return false;
        }

        sockaddr_in add = sockaddr_in();
        add.sin_family = AF_INET;
        add.sin_port = htons(_port);

        if (inet_pton(AF_INET, address.c_str(), &add.sin_addr) <= 0) {
            spdlog::error("[KCP Create] Invalid IP address format");
            return false;
        }

        app_data.server.kcp_server.sendto(msg, (sockaddr*)&add);
        return true;
    }
}
