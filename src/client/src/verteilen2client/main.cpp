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
#include <verteilen2/web.h>
#include <verteilen2client/logger.h>
#include <verteilen2client/db/local_record.h>
#include <verteilen2client/data/appdata.h>
#include <verteilen2client/api/all.h>
#include <verteilen2client/state/communication.h>

using namespace verteilen2;
using namespace verteilen2::client;

static void db_run(App_data& app_data){
    spdlog::info("Initializing database...");
    init_database(app_data);
}

static void mDNS_run(App_data& app_data){
    spdlog::info("Initializing mDNS service...");
    std::vector<std::string> ipv4s = network_get_all_ipv4();
    std::string v = "";
    for(const auto& ip : ipv4s){
        v += ip;
        v += ",";
    }
    if(v.size() > 0) {
        v.pop_back();
    }
    spdlog::info("Define mDNS message: {}", v);
    app_data.mdns.setServiceTxtRecord(v);
    app_data.mdns.setServiceName("verteilen-2-client");
    app_data.mdns.startService();
    mdns_cpp::Logger::setLoggerSink([](const std::string& msg) {
        spdlog::debug("mDNS: {}", msg);
    });
}

static void network_run(App_data& app_data) {
    spdlog::info("Initializing kcp service...");
    create_kcp_server(app_data);
}

static void network_shutdown(App_data& app_data) {
    spdlog::info("Shutdown kcp service...");
    shutdown_kcp_server(app_data);
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
    app_data.cli.web_port = network_get_port_available(app_data.cli.web_port);
    WebServer& buf = app_data.app.bindaddr("127.0.0.1").port(app_data.cli.web_port);
    if(web_have_ssl()){
        std::pair<std::string, std::string> ssl = web_get_ssl_files();
        buf.ssl_file(ssl.first, ssl.second).multithreaded().run();
    } else {
        buf.multithreaded().run();
    }
}

int main(int argc, char* argv[]){
    App_data app_data = App_data();
    if(!app_data_cli_init(app_data, argc, argv)) return 0;

    db_run(app_data);
    mDNS_run(app_data);
    network_run(app_data);
    web_run(app_data);

    app_data.shutdown.store(true);

    network_shutdown(app_data);
    app_data_release_all(app_data);

    spdlog::info("Successfully exit");
    exit(0);
}