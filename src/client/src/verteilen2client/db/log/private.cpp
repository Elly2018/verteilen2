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
#include <verteilen2client/db/log/private.h>
#include <verteilen2/path.h>

namespace verteilen2::client {

    int32_t create_log_table(SQLite::Database& db) {
        return db.exec(R"SQL(
            CREATE TABLE IF NOT EXISTS log (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                job CHAR(36) NOT NULL,
                title TEXT NOT NULL,
                content TEXT,
                created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
            );
        )SQL");
    }

    int32_t insert_log_table(SQLite::Database& db, const char job[36], const std::string title, const std::string content) {
        SQLite::Statement query(db, "INSERT INTO log (job, title, content) VALUES(?, ?, ?);");
        query.bind(1, job);
        query.bind(2, title);
        query.bind(3, content);
        return query.exec();
    }

    int32_t drop_log_table(SQLite::Database& db) {
        db.exec("PRAGMA foreign_keys = ON;");
        return db.exec(R"SQL(
            DELETE FROM log;
        )SQL");
    }

    std::string get_latest_datetime_log_table(SQLite::Database& db) {
        SQLite::Statement query(db, "SELECT id, job, title, content, created_at FROM log ORDER BY created_at LIMIT ? ;");

        if (query.executeStep()) {
            SQLite::Column col = query.getColumn(0);
            if (!col.isNull()) {
                return col.getText();
            }
        }

        return "1970-01-01 00:00:00";
    }

    int32_t get_latest_log_table(SQLite::Database& db, const int32_t amount, json& result) {
        SQLite::Statement query(db, "SELECT id, job, title, content, created_at FROM log ORDER BY created_at LIMIT ? ;");
        query.bind(1, amount);

        result.clear();
        result["data"] = json::array();

        while(query.executeStep()) {
            json buff = json::object();

            int32_t id = query.getColumn(0).getInt();
            std::string job = query.getColumn(1).getText();
            std::string title = query.getColumn(2).getText();
            std::string content = query.getColumn(3).getText();
            std::string created_at = query.getColumn(4).getText();

            buff["id"] = id;
            buff["job"] = job;
            buff["title"] = title;
            buff["content"] = content;
            buff["created_at"] = created_at;

            result["data"].push_back(buff);
        }

        return result["data"].size();
    }

    int32_t get_latest_log_table(SQLite::Database& db, const std::string last_timestamp, json& result) {

        SQLite::Statement query(db, "SELECT id, job, title, content, created_at FROM log ORDER BY created_at WHERE created_at > ?;");
        query.bind(1, last_timestamp);

        while(query.executeStep()) {
            json buff = json::object();

            int32_t id = query.getColumn(0).getInt();
            std::string job = query.getColumn(1).getText();
            std::string title = query.getColumn(2).getText();
            std::string content = query.getColumn(3).getText();
            std::string created_at = query.getColumn(4).getText();

            buff["id"] = id;
            buff["job"] = job;
            buff["title"] = title;
            buff["content"] = content;
            buff["created_at"] = created_at;

            result["data"].push_back(buff);
        }

        return result["data"].size();
    }

    int32_t get_history_log_table(SQLite::Database& db, const int32_t amount, const std::string top_timestamp, json& result) {

        SQLite::Statement query(db, "SELECT id, job, title, content, created_at FROM log LIMIT ? ORDER BY created_at DESC WHERE created_at < ?;");
        query.bind(1, amount);
        query.bind(2, top_timestamp);

        while(query.executeStep()) {
            json buff = json::object();

            int32_t id = query.getColumn(0).getInt();
            std::string job = query.getColumn(1).getText();
            std::string title = query.getColumn(2).getText();
            std::string content = query.getColumn(3).getText();
            std::string created_at = query.getColumn(4).getText();

            buff["id"] = id;
            buff["job"] = job;
            buff["title"] = title;
            buff["content"] = content;
            buff["created_at"] = created_at;

            result["data"].insert(result["data"].begin(), buff);
        }

        return result["data"].size();
    }

}