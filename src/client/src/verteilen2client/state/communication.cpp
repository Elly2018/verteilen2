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
#include <verteilen2/proto_gen/struct_header.pb.h>
#include <verteilen2client/data/appdata.h>
#include <verteilen2client/state/analyzer.h>
#include <verteilen2client/state/execute.h>

namespace verteilen2::client {

    static int32_t udp_output(const char *buf, int len, ikcpcb *kcp, void *user) {
        return 0;
    }

    void create_kcp_server(App_data& app_data) {
        int32_t mock_socket_fd = 42;
        uint32_t session_id = 0x11223344;

        app_data.kcp_session = KcpSession(session_id, &mock_socket_fd, udp_output);
        app_data.kcp_worker.state = ThreadState::Running;
        app_data.kcp_worker.worker = std::thread(update_kcp_server, std::ref(app_data));
    }

    void create_kcp_connection(App_data& app_data, const std::string address) {
        
    }

    void update_kcp_server(App_data& app_data) {
        app_data.kcp_session.update();
    }

}
