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
#include <spdlog/spdlog.h>
#include <verteilen2/network.h>
#include <verteilen2master/logger.h>
//#include <verteilen2master/db/local_record.h>
#include <verteilen2master/data/appdata.h>
#include <verteilen2master/api/all.h>
//#include <verteilen2master/state/communication.h>

using namespace verteilen2;
using namespace verteilen2::master;

static void db_run(App_data& app_data){
    spdlog::info("Initializing database...");
    //init_database(app_data);
}

static void websocket_run(App_data& app_data) {
    spdlog::info("Initializing websocket service...");
    //create_websocket_server(app_data);
}

static void web_run(App_data& app_data){
    static CrowSpdlogBridge custom_bridge;
    crow::logger::setHandler(&custom_bridge);
    
    spdlog::info("Initializing web service...");
    crow::mustache::set_global_base(VERTEILEN2_STATIC_DIRECTORY);
    register_static_route(app_data);
    register_template_route(app_data);
    register_connect_server_ws_route(app_data);
    register_ws_route(app_data);
    app_data.app.bindaddr("127.0.0.1").port(network_get_port_available(8080)).multithreaded().run();
}

int main(){
    App_data app_data = App_data();
    db_run(app_data);
    websocket_run(app_data);
    web_run(app_data);
}