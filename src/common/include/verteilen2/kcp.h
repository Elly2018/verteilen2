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
#pragma once
#ifndef COMMON_KCP_H
#define COMMON_KCP_H
#include <inttypes.h>
#include <chrono>
#include <vector>
#include <string>
#include <ikcp.h>

namespace verteilen2 {

    typedef int32_t (*udp_put_callback_func)(const char *buf, int32_t len, ikcpcb *kcp, void *user);

    static uint32_t get_current_ms() {
        auto now = std::chrono::steady_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    }

    class KcpSession {
    private:
        void* m_user;
        ikcpcb* m_kcp;
        uint32_t m_conv;
        udp_put_callback_func i_call;
        udp_put_callback_func o_call;

    public:
        KcpSession() {
            
        }
        KcpSession(uint32_t conv, void* user_socket_ptr, udp_put_callback_func input_callback, udp_put_callback_func output_callback) : m_user(user_socket_ptr), m_conv(conv), i_call(input_callback), o_call(output_callback) {
            m_kcp = ikcp_create(m_conv, m_user);
            if(o_call != nullptr) m_kcp->output = o_call;
            
            ikcp_nodelay(m_kcp, 1, 10, 2, 1);
            ikcp_wndsize(m_kcp, 128, 128);
        }

        ~KcpSession() {
            if (m_kcp) {
                ikcp_release(m_kcp);
            }
        }

        void handle_udp_receive(const char* raw_udp_data, long size) {
            ikcp_input(m_kcp, raw_udp_data, size);
        }

        int32_t send_data(const std::string& message) {
            return ikcp_send(m_kcp, message.c_str(), message.size());
        }

        void check_and_recv() {
            int32_t peek_size = ikcp_peeksize(m_kcp);
            if (peek_size > 0) {
                std::vector<char> buffer(peek_size);
                int32_t bytes_read = ikcp_recv(m_kcp, buffer.data(), buffer.size());

                if (bytes_read > 0) {
                    if(i_call != nullptr) {
                        i_call(buffer.data(), bytes_read, m_kcp, m_user);
                    }
                }
            }
        }

        void update() {
            uint32_t current_time = get_current_ms();
            ikcp_update(m_kcp, current_time);
        }
    };
}

#endif