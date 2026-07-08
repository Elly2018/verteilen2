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

    job_env job_data_get_env(Verteilen2__Job& job) {
        job_env a = job_env();

        for (size_t i = 0; i < job.d_map->n_map_boolean; i++) {
            if (job.d_map->map_boolean[i] && job.d_map->map_boolean[i]->key) {
                a.datas_bool[job.d_map->map_boolean[i]->key] = job.d_map->map_boolean[i]->value;
            }
        }

        for (size_t i = 0; i < job.d_map->n_map_int32; i++) {
            if (job.d_map->map_int32[i] && job.d_map->map_int32[i]->key) {
                a.datas_int32[job.d_map->map_int32[i]->key] = job.d_map->map_int32[i]->value;
            }
        }

        for (size_t i = 0; i < job.d_map->n_map_int64; i++) {
            if (job.d_map->map_int64[i] && job.d_map->map_int64[i]->key) {
                a.datas_int64[job.d_map->map_int64[i]->key] = job.d_map->map_int64[i]->value;
            }
        }

        for (size_t i = 0; i < job.d_map->n_map_float; i++) {
            if (job.d_map->map_float[i] && job.d_map->map_float[i]->key) {
                a.datas_float[job.d_map->map_float[i]->key] = job.d_map->map_float[i]->value;
            }
        }

        for (size_t i = 0; i < job.d_map->n_map_double; i++) {
            if (job.d_map->map_double[i] && job.d_map->map_double[i]->key) {
                a.datas_double[job.d_map->map_double[i]->key] = job.d_map->map_double[i]->value;
            }
        }

        for (size_t i = 0; i < job.d_map->n_map_string; i++) {
            if (job.d_map->map_string[i] && job.d_map->map_string[i]->key && job.d_map->map_string[i]->value) {
                a.datas_string[job.d_map->map_string[i]->key] = job.d_map->map_string[i]->value;
            }
        }

        return a;
    }

    void job_data_set_env(Verteilen2__Job& job, job_env& env) {
        job.d_map->n_map_boolean = env.datas_bool.size();
        if (job.d_map->n_map_boolean > 0) {
            // Allocate an array of entry pointers
            job.d_map->map_boolean = new Verteilen2__Job__MapBooleanEntry*[job.d_map->n_map_boolean];
            
            size_t idx = 0;
            for (const auto& [key, value] : env.datas_bool) {
                job.d_map->map_boolean[idx] = new Verteilen2__Job__MapBooleanEntry();
                verteilen2__job__map_boolean_entry__init(job.d_map->map_boolean[idx]);
                
                job.d_map->map_boolean[idx]->key = strdup(key.c_str());
                job.d_map->map_boolean[idx]->value = value;
                idx++;
            }
        } else {
            job.d_map->map_boolean = nullptr;
        }

        job.d_map->n_map_int32 = env.datas_int32.size();
        if (job.d_map->n_map_int32 > 0) {
            // Allocate an array of entry pointers
            job.d_map->map_int32 = new Verteilen2__Job__MapInt32Entry*[job.d_map->n_map_int32];
            
            size_t idx = 0;
            for (const auto& [key, value] : env.datas_int32) {
                job.d_map->map_int32[idx] = new Verteilen2__Job__MapInt32Entry();
                verteilen2__job__map_int32_entry__init(job.d_map->map_int32[idx]);
                
                job.d_map->map_int32[idx]->key = strdup(key.c_str());
                job.d_map->map_int32[idx]->value = value;
                idx++;
            }
        } else {
            job.d_map->map_int32 = nullptr;
        }

        job.d_map->n_map_int64 = env.datas_int64.size();
        if (job.d_map->n_map_int64 > 0) {
            // Allocate an array of entry pointers
            job.d_map->map_int64 = new Verteilen2__Job__MapInt64Entry*[job.d_map->n_map_int64];
            
            size_t idx = 0;
            for (const auto& [key, value] : env.datas_int64) {
                job.d_map->map_int64[idx] = new Verteilen2__Job__MapInt64Entry();
                verteilen2__job__map_int64_entry__init(job.d_map->map_int64[idx]);
                
                job.d_map->map_int64[idx]->key = strdup(key.c_str());
                job.d_map->map_int64[idx]->value = value;
                idx++;
            }
        } else {
            job.d_map->map_int64 = nullptr;
        }

        job.d_map->n_map_float = env.datas_float.size();
        if (job.d_map->n_map_float > 0) {
            // Allocate an array of entry pointers
            job.d_map->map_float = new Verteilen2__Job__MapFloatEntry*[job.d_map->n_map_float];
            
            size_t idx = 0;
            for (const auto& [key, value] : env.datas_float) {
                job.d_map->map_float[idx] = new Verteilen2__Job__MapFloatEntry();
                verteilen2__job__map_float_entry__init(job.d_map->map_float[idx]);
                
                job.d_map->map_float[idx]->key = strdup(key.c_str());
                job.d_map->map_float[idx]->value = value;
                idx++;
            }
        } else {
            job.d_map->map_float = nullptr;
        }


        job.d_map->n_map_double = env.datas_double.size();
        if (job.d_map->n_map_double > 0) {
            // Allocate an array of entry pointers
            job.d_map->map_double = new Verteilen2__Job__MapDoubleEntry*[job.d_map->n_map_double];
            
            size_t idx = 0;
            for (const auto& [key, value] : env.datas_double) {
                job.d_map->map_double[idx] = new Verteilen2__Job__MapDoubleEntry();
                verteilen2__job__map_double_entry__init(job.d_map->map_double[idx]);
                
                job.d_map->map_double[idx]->key = strdup(key.c_str());
                job.d_map->map_double[idx]->value = value;
                idx++;
            }
        } else {
            job.d_map->map_double = nullptr;
        }

        job.d_map->n_map_string = env.datas_string.size();
        if (job.d_map->n_map_string > 0) {
            // Allocate an array of entry pointers
            job.d_map->map_string = new Verteilen2__Job__MapStringEntry*[job.d_map->n_map_string];
            
            size_t idx = 0;
            for (const auto& [key, value] : env.datas_string) {
                job.d_map->map_string[idx] = new Verteilen2__Job__MapStringEntry();
                verteilen2__job__map_string_entry__init(job.d_map->map_string[idx]);
                
                job.d_map->map_string[idx]->key = strdup(key.c_str());
                job.d_map->map_string[idx]->value = strdup(value.c_str());
                idx++;
            }
        } else {
            job.d_map->map_string = nullptr;
        }
    }

}