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
#include <fcntl.h>
#include <ikcp.h>
#include <spdlog/spdlog.h>
#include <verteilen2/env.h>
#include <verteilen2/proto_gen/struct_header.pb.h>
#include <verteilen2client/data/appdata.h>
#include <verteilen2client/state/analyzer.h>
#include <verteilen2client/state/execute.h>
#include <verteilen2client/state/fs/filesystem.h>

namespace verteilen2::client {

    constexpr uint32_t KCP_CONV_ID = 0x11223344;

    static int32_t udp_output(const char *buf, int32_t len, ikcpcb *kcp, void *user) {
        App_data& app_data = *(App_data*)user;
        if (app_data.server.socket_fd < 0) {
            spdlog::error("[KCP Output] Cannot send data, invalid socket descriptor!");
            return -1;
        }

        ssize_t bytes_sent = ::sendto(
            app_data.server.socket_fd,
            buf,
            len,
            0,
            (struct sockaddr*)&app_data.server.server_addr,
            sizeof(app_data.server.server_addr)
        );

        if (bytes_sent < 0) {
            spdlog::error("[KCP Output] sendto failed: {}", strerror(errno));
            return -2;
        }

        spdlog::debug("[KCP Output] Successfully sent {} wire bytes over UDP.", bytes_sent);
        return 0;
    }

    static int32_t udp_input(const char *buf, int32_t len, ikcpcb *kcp, void *user) {
        App_data& app_data = *(App_data*)user;
        google::protobuf::Arena arena;
        RawData* r = google::protobuf::Arena::CreateMessage<RawData>(&arena);
        if(r->ParseFromArray(buf, len)) {
            analysis(app_data, r);
        }
        return 0;
    }

    void create_kcp_server(App_data& app_data) {
        fs_init_filesystem();

        app_data.server.socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
        if (app_data.server.socket_fd < 0) {
            spdlog::critical("Failed to create UDP socket!");
            return;
        }

        int32_t flags = fcntl(app_data.server.socket_fd, F_GETFL, 0);
        fcntl(app_data.server.socket_fd, F_SETFL, flags | O_NONBLOCK);

        std::memset(&app_data.server.server_addr, 0, sizeof(app_data.server.server_addr));
        app_data.server.server_addr.sin_family = AF_INET;
        app_data.server.server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        app_data.server.server_addr.sin_port = htons(kcp_port);

        if (bind(app_data.server.socket_fd, (struct sockaddr*)&app_data.server.server_addr, sizeof(app_data.server.server_addr)) < 0) {
            spdlog::critical("Failed to bind UDP socket to port {}", kcp_port);
            return;
        }

        app_data.server.kcp_session = KcpSession(KCP_CONV_ID, &app_data, udp_input, udp_output);
        app_data.server.kcp_worker.state = ThreadState::Running;
        app_data.server.kcp_worker.worker = std::thread(update_kcp_server, std::ref(app_data));
    }

    void update_kcp_server(App_data& app_data) {
        char packet_buffer[2048];
        struct sockaddr_in remote_addr;
        socklen_t addr_len = sizeof(remote_addr);

        while (!app_data.shutdown.load()) {

            while (true && !app_data.shutdown.load()) {

                ssize_t bytes_recv = recvfrom(
                    app_data.server.socket_fd, packet_buffer, sizeof(packet_buffer), 
                    0, (struct sockaddr*)&remote_addr, &addr_len
                );

                if (bytes_recv < 0) break;
                if (bytes_recv < 24) continue;

                app_data.server.server_addr = remote_addr;
                app_data.server.kcp_session.handle_udp_receive(packet_buffer, bytes_recv);
            }

            app_data.server.kcp_session.update();
            app_data.server.kcp_session.check_and_recv();

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

    void shutdown_kcp_server(App_data& app_data) {
        if(app_data.server.kcp_worker.worker.joinable()){
            app_data.server.kcp_worker.worker.join();
        }
    }

}
