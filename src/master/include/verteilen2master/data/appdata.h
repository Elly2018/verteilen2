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
#ifndef MASTER_DATA_APPDATA_H
#define MASTER_DATA_APPDATA_H
#include <vector>
#include <string>
#include <cstdint>
#include <hv/WebSocketClient.h>
#include <hv/WebSocketServer.h>
#include "../config.h"
#include "worker.h"
#include <verteilen2/data/all.h>
#include <verteilen2/db/local_record.h>

namespace verteilen2::master {

    struct App_data {
        WebServer app;
        database_getter db_getter;
        hv::WebSocketClient ws_client;
        hv::WebSocketServer ws_server;
        std::vector<Verteilen2__Project*> projects;
        std::vector<Verteilen2__Task*> tasks;
        std::vector<Verteilen2__Job*> jobs;
        std::vector<Verteilen2__Vault*> vaults;
        Worker workers[60];
    };

}

#endif