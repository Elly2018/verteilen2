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
#include <verteilen2/db/job/private.h>
#include <verteilen2/path.h>

namespace verteilen2 {

    int32_t create_job_table(SQLite::Database db) {
        return db.exec(R"SQL(
            CREATE TABLE IF NOT EXISTS job (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                job_id CHAR(36) NOT NULL,
                title TEXT NOT NULL,
                description TEXT,
                created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
            );
        )SQL");
    }

    int32_t insert_job_detail_table(SQLite::Database db, const char job[36], const std::string title, const std::string description) {
        SQLite::Statement query(db, "INSERT INTO job (job_id, title, description) VALUES(?, ?, ?);");
        query.bind(1, job);
        query.bind(2, title);
        query.bind(3, description);
        return query.exec();
    }

    int32_t drop_job_table(SQLite::Database db) {
        return db.exec(R"SQL(
            DELETE FROM job;
        )SQL");
    }

    bool check_exists_job_table(SQLite::Database db, const char job[36]) {
        SQLite::Statement query(db, "SELECT COUNT(*) FROM job WHERE job_id = ?;");
        query.bind(1, job);

        if (query.executeStep()) {
            int count = query.getColumn(0).getInt();
            return count > 0;
        }
        
        return false;
    }

    int32_t get_latest_job_table(SQLite::Database db, const int32_t amount, json& result) {
        SQLite::Statement query(db, "SELECT id, job_id, title, description, created_at FROM job ORDER BY created_at LIMIT ? ;");
        query.bind(1, amount);

        result.clear();
        result["data"] = json::array();

        while(query.executeStep()) {
            json buff = json::object();

            int32_t id = query.getColumn(0).getInt();
            std::string job_id = query.getColumn(1).getText();
            std::string title = query.getColumn(2).getText();
            std::string description = query.getColumn(3).getText();
            std::string created_at = query.getColumn(4).getText();

            buff["id"] = id;
            buff["job_id"] = job_id;
            buff["title"] = title;
            buff["description"] = description;
            buff["created_at"] = created_at;

            result["data"].push_back(buff);
        }

        return result["data"].size();
    }

    int32_t get_latest_job_table(SQLite::Database db, const std::string last_timestamp, json& result) {
        SQLite::Statement query(db, "SELECT id, job_id, title, description, created_at FROM job ORDER BY created_at WHERE created_at > ? ;");
        query.bind(1, last_timestamp);

        result.clear();
        result["data"] = json::array();

        while(query.executeStep()) {
            json buff = json::object();

            int32_t id = query.getColumn(0).getInt();
            std::string job_id = query.getColumn(1).getText();
            std::string title = query.getColumn(2).getText();
            std::string description = query.getColumn(3).getText();
            std::string created_at = query.getColumn(4).getText();

            buff["id"] = id;
            buff["job_id"] = job_id;
            buff["title"] = title;
            buff["description"] = description;
            buff["created_at"] = created_at;

            result["data"].push_back(buff);
        }

        return result["data"].size();
    }

    int32_t get_history_job_table(SQLite::Database db, const int32_t amount, const std::string top_timestamp, json& result) {
        SQLite::Statement query(db, "SELECT id, job_id, title, description, created_at FROM job LIMIT ? ORDER BY created_at DESC WHERE created_at < ?;");
        query.bind(1, amount);
        query.bind(2, top_timestamp);

        result.clear();
        result["data"] = json::array();

        while(query.executeStep()) {
            json buff = json::object();

            int32_t id = query.getColumn(0).getInt();
            std::string job_id = query.getColumn(1).getText();
            std::string title = query.getColumn(2).getText();
            std::string description = query.getColumn(3).getText();
            std::string created_at = query.getColumn(4).getText();

            buff["id"] = id;
            buff["job_id"] = job_id;
            buff["title"] = title;
            buff["description"] = description;
            buff["created_at"] = created_at;

            result["data"].insert(result["data"].begin(), buff);
        }

        return result["data"].size();
    }

}