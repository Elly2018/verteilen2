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
#include <verteilen2server/data/appdata.h>
#include <spdlog/spdlog.h>
#include <argh.h>

namespace verteilen2::server {

    bool app_data_cli_init(App_data& app_data, int argc, char* argv[]) {
        app_data.cli.level = spdlog::level::info;
        app_data.cli.web_port = server_web_port;
        app_data.cli.udp_port = client_kcp_port;
        
        argh::parser cmdl;
        cmdl.parse(argc, argv, argh::parser::PREFER_PARAM_FOR_UNREG_OPTION);

        if (cmdl.flags().contains("h") || cmdl.flags().contains("help")) {
            return false;
        }

        for (auto& flag : cmdl.flags()) {
            if(flag == "debug") {
                app_data.cli.level = spdlog::level::debug;
            }
            if(flag == "trace") {
                app_data.cli.level = spdlog::level::trace;
            }
        }

        for (auto& param : cmdl.params()) {
            if(param.first == "l" || param.first == "level") {
                try{
                    int32_t num = std::stoi(param.second);
                    if(num == 0) app_data.cli.level = spdlog::level::trace;
                    if(num == 1) app_data.cli.level = spdlog::level::info;
                    if(num == 2) app_data.cli.level = spdlog::level::info;
                    if(num == 3) app_data.cli.level = spdlog::level::warn;
                    if(num == 4) app_data.cli.level = spdlog::level::err;
                    if(num == 5) app_data.cli.level = spdlog::level::critical;
                    else app_data.cli.level = spdlog::level::off;
                }
                catch (const std::invalid_argument& e) {
                    spdlog::error("[CLI] \"level\" Error: Not a valid number: {}", param.second);
                } 
                catch (const std::out_of_range& e) {
                    spdlog::error("[CLI] \"level\" Error: Number is too big for a 32-bit int: {}", param.second);
                }
            }
            else if(param.first == "wp" || param.first == "web_port") {
                try {
                    app_data.cli.web_port = std::stoi(param.second);
                }
                catch (const std::invalid_argument& e) {
                    spdlog::error("[CLI] \"web_port\" Error: Not a valid number: {}", param.second);
                } 
                catch (const std::out_of_range& e) {
                    spdlog::error("[CLI] \"web_port\" Error: Number is too big for a 32-bit int: {}", param.second);
                }
            }
            else if(param.first == "kp" || param.first == "kcp_port") {
                try {
                    app_data.cli.udp_port = std::stoi(param.second);
                }
                catch (const std::invalid_argument& e) {
                    spdlog::error("[CLI] \"kcp_port\" Error: Not a valid number: {}", param.second);
                } 
                catch (const std::out_of_range& e) {
                    spdlog::error("[CLI] \"kcp_port\" Error: Number is too big for a 32-bit int: {}", param.second);
                }
            }
        }

        spdlog::set_level(app_data.cli.level);
        return true;
    }

    void app_data_release_all(App_data& app_data) {
        spdlog::info("Shuwdown app_data...");
        fs_work_release_all(app_data.fsworker);
        work_release_all(app_data.workers);
    }

}