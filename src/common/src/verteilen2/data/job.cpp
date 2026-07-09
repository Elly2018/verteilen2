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
#include <verteilen2/data/job.h>
#include <cstring>

namespace verteilen2 {

    job_env job_data_get_env(verteilen2::Job& job) {
        job_env a = job_env();

        for (const auto& [key, value] : job.d_map().map_boolean()) {
            a.datas_bool.insert({key, value});
        }

        for (const auto& [key, value] : job.d_map().map_int32()) {
            a.datas_int32.insert({key, value});
        }

        for (const auto& [key, value] : job.d_map().map_int64()) {
            a.datas_int64.insert({key, value});
        }

        for (const auto& [key, value] : job.d_map().map_float()) {
            a.datas_float.insert({key, value});
        }

        for (const auto& [key, value] : job.d_map().map_double()) {
            a.datas_double.insert({key, value});
        }

        for (const auto& [key, value] : job.d_map().map_string()) {
            a.datas_string.insert({key, value});
        }

        return a;
    }

    void job_data_set_env(verteilen2::Job& job, job_env& env) {
        verteilen2::DynamicMap& map = *job.mutable_d_map();

        google::protobuf::Map<std::string, bool>& map_bool = *map.mutable_map_boolean();
        map_bool.clear();
        if (env.datas_bool.size() > 0) {
            for (const auto& [key, value] : env.datas_bool) {
                map_bool.insert({key, value});
            }
        }
        
        google::protobuf::Map<std::string, int32_t>& map_int32 = *map.mutable_map_int32();
        map_int32.clear();
        if (env.datas_int32.size() > 0) {
            for (const auto& [key, value] : env.datas_int32) {
                map_int32.insert({key, value});
            }
        }

        google::protobuf::Map<std::string, int64_t>& map_int64 = *map.mutable_map_int64();
        map_int64.clear();
        if (env.datas_int64.size() > 0) {
            for (const auto& [key, value] : env.datas_int64) {
                map_int64.insert({key, value});
            }
        }

        google::protobuf::Map<std::string, float>& map_float = *map.mutable_map_float();
        map_float.clear();
        if (env.datas_float.size() > 0) {
            for (const auto& [key, value] : env.datas_float) {
                map_float.insert({key, value});
            }
        }

        google::protobuf::Map<std::string, double>& map_double = *map.mutable_map_double();
        map_double.clear();
        if (env.datas_double.size() > 0) {
            for (const auto& [key, value] : env.datas_double) {
                map_double.insert({key, value});
            }
        }

        google::protobuf::Map<std::string, std::string>& map_string = *map.mutable_map_string();
        map_string.clear();
        if (env.datas_string.size() > 0) {
            for (const auto& [key, value] : env.datas_string) {
                map_string.insert({key, value});
            }
        }
    }

}