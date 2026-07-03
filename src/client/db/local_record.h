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
#ifndef CLIENT_DB_LOCAL_RECORD_H
#define CLIENT_DB_LOCAL_RECORD_H
#include <cinttypes>
#include <string>
#include <SQLiteCpp/SQLiteCpp.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace verteilen2::client {

    void init_database();
    SQLite::Database get_database();

    int32_t create_log_table();
    int32_t insert_log_table(const char job[36], const std::string title, const std::string content);
    int32_t drop_log_table();
    int32_t get_latest_log_table(const int32_t amount, json& result);
    void get_latest_log_table(const std::string last_timestamp);
    void get_history_log_table(const int32_t amount, const std::string top_timestamp);

    int32_t create_job_table();
    int32_t insert_job_detail_table(const char job[36], const std::string title, const std::string description);
    int32_t drop_job_table();
    int32_t get_latest_job_table(const int32_t amount, json& result);
    void get_latest_job_table(const std::string last_timestamp);
    void get_history_job_table(const int32_t amount, const std::string top_timestamp);

    int32_t create_job_detail_table();
    int32_t insert_job_detail_table(const char job[36], const int32_t level, const std::string title, const std::string content);
    int32_t drop_job_detail_table();
    int32_t get_latest_job_detail_table(const char job[36], const int32_t amount, json& result);
    void get_latest_job_detail_table(const char job[36], const std::string last_timestamp);
    void get_history_job_detail_table(const char job[36], const int32_t amount, const std::string top_timestamp);
}

#endif