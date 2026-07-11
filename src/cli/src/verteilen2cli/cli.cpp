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
#include <verteilen2cli/cli.h>
#include <argh.h>

namespace verteilen2::cli {

    Cli_data parse(int argc, char* argv[]) {
        Cli_data data = Cli_data();
        data.help_module = -1;

        argh::parser cmdl;
        cmdl.parse(argc, argv, argh::parser::PREFER_PARAM_FOR_UNREG_OPTION);

        for(auto& flag : cmdl.flags()){
            if(flag == "help" || flag == "h") {
                data.help_call = true;
            }
        }

        for(auto& param : cmdl.params()){
            if(param.first == "help") {
                if(param.second == "client") {
                    data.help_call = true;
                    data.help_module = 0;
                }
                else if(param.second == "server") {
                    data.help_call = true;
                    data.help_module = 1;
                }
                else if(param.second == "master") {
                    data.help_call = true;
                    data.help_module = 2;
                }else {
                    data.help_call = true;
                    data.help_module = -2;
                }
            }
        }

        return data;
    }

}