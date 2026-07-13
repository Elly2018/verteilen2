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
#ifndef COMMON_DB_NODE_PRIVATE_H
#define COMMON_DB_NODE_PRIVATE_H
#include <cinttypes>
#include <SQLiteCpp/SQLiteCpp.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace verteilen2 {

    int32_t create_node_table(SQLite::Database db);
    int32_t insert_node_table(SQLite::Database db, const std::string title, const std::string description, const std::string ip, const int32_t port);
    int32_t drop_node_table(SQLite::Database db);
    int32_t get_latest_node_table(SQLite::Database db, const int32_t amount, json& result);
    int32_t get_latest_node_table(SQLite::Database db, const std::string last_timestamp, json& result);
    int32_t get_history_node_table(SQLite::Database db, const int32_t amount, const std::string top_timestamp, json& result);
    int32_t get_page_node_table(SQLite::Database db, const int32_t amount, const int32_t page, json& result);
    int32_t get_total_node_table(SQLite::Database db);
    
}

#endif