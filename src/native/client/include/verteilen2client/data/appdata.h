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
#ifndef CLIENT_DATA_APPDATA_H
#define CLIENT_DATA_APPDATA_H
#include <atomic>
#include <string>
#include <cstdint>
#include <mdns_cpp/mdns.hpp>
#include <mdns_cpp/logger.hpp>
#include "../config.h"
#include "cli.h"
#include <verteilen2/data/worker.h>
#include <verteilen2/data/fs.h>
#include <verteilen2/env.h>
#include <verteilen2/data/sock.h>
#include <verteilen2/db/local_record.h>

namespace verteilen2::client {

    struct App_data {
        Cli_data cli;
        WebServer app;
        KCPServer server;
        hv::SocketChannelPtr server_target;
        mdns_cpp::mDNS mdns;
        database_getter db_getter;
        Worker workers[worker_limit];
        FSWorker fsworker[worker_limit];
        std::atomic<bool> shutdown{false};
    };

    bool app_data_cli_init(App_data& app_data, int argc, char* argv[]);
    void app_data_release_all(App_data& app_data);

}

#endif