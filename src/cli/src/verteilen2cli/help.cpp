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

    bool handle_help(argh::parser& cmdl){

        std::string help_sub_text = "";
        bool has_help_primary = cmdl.flags().count("h") || cmdl.flags().count("help");
        bool has_help_params = cmdl.params().count("help") || cmdl.params().count("h");
        
        if (has_help_primary){
            print_help();
            return true;
        }

        if(has_help_params){
            help_sub_text = cmdl.params().at("help");
            if(help_sub_text.size() == 0) {
                help_sub_text = cmdl.params().at("h");
            }
        }

        std::transform(help_sub_text.begin(), help_sub_text.end(), help_sub_text.begin(), [](unsigned char c){ return std::tolower(c); });

        if(help_sub_text.size() > 0){
            if(help_sub_text == "master"){
                print_help_master();
            }
            else if(help_sub_text == "client"){
                print_help_client();
            }
            else if(help_sub_text == "proxy"){
                print_help_proxy();
            }
            else{
                printf("Cannot find the module: %s\n", help_sub_text.c_str());
                printf("Type --help to find the CLI usage\n");
            }
            return true;
        }

        return false;
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

    void print_help_proxy() {
        printf("Proxy\n");
    }

}