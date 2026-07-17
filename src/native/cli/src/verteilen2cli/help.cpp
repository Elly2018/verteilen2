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
#include <stdio.h>
#include <verteilen2cli/category.h>

namespace verteilen2::cli {

    bool handle_help(Cli_data& data){
        if(data.help_call){
            if(data.help_module == 0){
                print_help_client();
            }
            else if(data.help_module == 1){
                print_help_server();
            }
            else if(data.help_module == 2){
                print_help_master();
            }
            else if(data.help_module == -1){
                print_help();
            }
            else {
                print_help_options();
            }
        }

        return data.help_call;
    }

    void print_help() {
        printf("YES\n");
    }

    void print_help_master() {
        printf("Master\n");
    }

    void print_help_client() {
        printf("Client\n");
    }

    void print_help_server() {
        printf("Proxy\n");
    }

    void print_help_options() {

    }

}