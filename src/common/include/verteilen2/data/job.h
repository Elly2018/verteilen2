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
#ifndef COMMON_DATA_JOB_H
#define COMMON_DATA_JOB_H
#include <verteilen2/proto_gen/job.pb-c.h>
#include <unordered_map>
#include <string>

namespace verteilen2 {

    struct job_env
    {
        std::unordered_map<std::string, bool> datas_bool;
        std::unordered_map<std::string, int32_t> datas_int32;
        std::unordered_map<std::string, int64_t> datas_int64;
        std::unordered_map<std::string, float> datas_float;
        std::unordered_map<std::string, double> datas_double;
        std::unordered_map<std::string, std::string> datas_string;
    };
    
    job_env job_data_get_env(Verteilen2__Job& job);
    void job_data_set_env(Verteilen2__Job& job, job_env& env);

}

#endif