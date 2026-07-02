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
#include "network.h"
#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>

namespace net = boost::asio;

namespace verteilen2 {

    std::vector<std::string> network_get_all_ipv4() {
        std::vector<std::string> a = std::vector<std::string>();
        try {
            net::io_context io_ctx;
            net::ip::tcp::resolver resolver(io_ctx);

            std::string hostname = boost::asio::ip::host_name();
            net::ip::basic_resolver_results<net::ip::tcp> results = resolver.resolve(hostname, "");
            for (const auto& entry : results) {
            auto addr = entry.endpoint().address();
                if (addr.is_loopback()) continue; // Skip 127.0.0.1

                if (addr.is_v4()) {
                    a.push_back(addr.to_string());
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "IP Query Error: " << e.what() << std::endl;
        }

        return a;
    }

    std::vector<std::string> network_get_all_ipv6() {
        std::vector<std::string> a = std::vector<std::string>();
        try {
            net::io_context io_ctx;
            net::ip::tcp::resolver resolver(io_ctx);

            std::string hostname = boost::asio::ip::host_name();
            net::ip::basic_resolver_results<net::ip::tcp> results = resolver.resolve(hostname, "");
            for (const auto& entry : results) {
            auto addr = entry.endpoint().address();
                if (addr.is_loopback()) continue; // Skip 127.0.0.1

                if (addr.is_v6()) {
                    a.push_back(addr.to_string());
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "IP Query Error: " << e.what() << std::endl;
        }

        return a;
    }

}

