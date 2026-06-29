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
#ifndef COMMON_STRUCT_DATA_JOB_H
#define COMMON_STRUCT_DATA_JOB_H
#include <unordered_map>
#include <vector>
#include <string>
#include "vault.h"
#include "../vconst.h"
#include "../enum/job_type.h"

namespace verteilen2 {

    struct Job_data {
        char uuid[UUID_LENGTH];
        char name[NAME_LENGTH];
        Job_type type;
        std::string script;
        /**
         * The key character length limit should be 64
         */
        std::unordered_map<std::string, Vault_element> local_datas;
        char inputs_0[JOB_FIELD_LENGTH];
        char inputs_1[JOB_FIELD_LENGTH];
        char inputs_2[JOB_FIELD_LENGTH];
        char inputs_3[JOB_FIELD_LENGTH];
        char inputs_4[JOB_FIELD_LENGTH];
    };

}

#endif