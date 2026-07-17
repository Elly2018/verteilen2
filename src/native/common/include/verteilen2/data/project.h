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
#ifndef COMMON_DATA_PROJECT_H
#define COMMON_DATA_PROJECT_H
#include <vector>
#include <verteilen2/proto_gen/struct_project.pb.h>
#include <verteilen2/proto_gen/struct_task.pb.h>
#include <verteilen2/proto_gen/struct_job.pb.h>

namespace verteilen2 {
    
    int32_t project_data_get_task_count(verteilen2::Project& project);
    int32_t project_data_get_task_count(verteilen2::Project& project, std::vector<verteilen2::Task>& tasks);
    int32_t project_data_get_job_count(verteilen2::Project& project, std::vector<verteilen2::Task>& tasks);
    int32_t project_data_get_job_count(verteilen2::Project& project, std::vector<verteilen2::Task>& tasks, std::vector<verteilen2::Job>& jobs);
    
}

#endif