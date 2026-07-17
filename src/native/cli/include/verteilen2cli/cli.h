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
#ifndef CLI_CLI_H
#define CLI_CLI_H
#include <cinttypes>
#include <string>
#include <vector>

namespace verteilen2::cli {

    /**
     * @brief The cli arguments
     */
    struct Cli_data {
        /**
         * @brief Show help information for the cli tools
         */
        bool help_call;
        /**
         * @brief Helper module
         * 
         * - -2: Incorrect, this means user enter the wrong module name
         * 
         * - -1: Default
         * 
         * - 0: Client module helper display
         * 
         * - 1: Server module helper display
         * 
         * - 2: Master module helper display
         */
        int32_t help_module;
        /**
         * @brief Handle module action
         * 
         * - -2: Incorrect, this means user enter the wrong module name
         * 
         * - -1: No handle module select
         * 
         * - 0: Client module handle action
         * 
         * - 1: Server module handle action
         * 
         * - 2: Master module handle action
         */
        int32_t handle_target;
        /**
         * @brief The first command label, Primary category for command group
         */
        std::string command;
        /**
         * @brief The second command label, Secondary category for command group
         */
        std::string sub_command;
        /**
         * @brief The rest of arguments, index > 2
         */
        std::vector<std::string> arguments;
    };

    Cli_data parse(int argc, char* argv[]);

}

#endif