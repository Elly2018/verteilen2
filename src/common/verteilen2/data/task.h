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
#ifndef COMMON_STRUCT_DATA_TASK_H
#define COMMON_STRUCT_DATA_TASK_H
#include <vector>
#include "../vconst.h"
#include "../data_field.h"
#include "../task_config.h"
#include "../enum/task_type.h"

namespace verteilen2 {

    struct Job_data;

    struct Task_data {
        char uuid[UUID_LENGTH];
        char name[NAME_LENGTH];
        char description[DESCRIPTION_LENGTH];
        Task_type type;
        char cluster_field_key[NAME_LENGTH];
        char multicore_field_key[NAME_LENGTH];
        Data_field jobs[ELEMENT_LENGTH];
    };

    int32_t task_data_get_job_count(Task_data task);
    int32_t task_data_get_job_count(Task_data task, std::vector<Job_data>& jobs);

}

#endif