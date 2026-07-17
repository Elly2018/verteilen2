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
#include <verteilen2/uuid.h>

namespace verteilen2 {

    static void get_job_data(SQLite::Statement& query, json& result) {
        json buff = json::object();

        int32_t id = query.getColumn(0).getInt();
        std::string uuid = query.getColumn(1).getText();
        std::string task = query.getColumn(2).getText();
        std::string title = query.getColumn(3).getText();
        std::string description = query.getColumn(4).getText();
        std::string created_at = query.getColumn(5).getText();

        buff["id"] = id;
        buff["uuid"] = uuid;
        buff["task"] = task;
        buff["title"] = title;
        buff["description"] = description;
        buff["created_at"] = created_at;

        result["data"].push_back(buff);
    }

    int32_t create_job_table(SQLite::Database db) {
        return db.exec(R"SQL(
            CREATE TABLE IF NOT EXISTS job (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                uuid CHAR(36) NOT NULL,
                task CHAR(36) NOT NULL,
                title TEXT NOT NULL,
                description TEXT,
                created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,

                FOREIGN KEY (task) REFERENCES task(uuid)
                    ON DELETE CASCADE
                    ON UPDATE CASCADE
            );
        )SQL");
    }

    int32_t insert_job_table(SQLite::Database db, const std::string task, const int32_t weight, const std::string title, const std::string description) {
        SQLite::Statement query(db, "INSERT INTO job (uuid, task, title, description) VALUES(?, ?, ?, ?);");
        query.bind(1, generate_uuid());
        query.bind(2, task);
        query.bind(3, title);
        query.bind(4, description);
        return query.exec();
    }

    int32_t update_job_table(SQLite::Database db, const std::string uuid, const int32_t weight, const std::string title, const std::string description) {
        SQLite::Statement query(db, "UPDATE job SET weight = ?, title = ?, description = ? WHERE uuid = ?;");
        query.bind(1, weight);
        query.bind(2, title);
        query.bind(3, description);
        query.bind(4, uuid);
        return query.exec();
    }

    int32_t drop_job_table(SQLite::Database db) {
        return db.exec(R"SQL(
            DELETE FROM job;
        )SQL");
    }

    bool check_exists_job_table(SQLite::Database db, std::string job) {
        SQLite::Statement query(db, "SELECT COUNT(*) FROM job WHERE uuid = ?;");
        query.bind(1, job);

        if (query.executeStep()) {
            int count = query.getColumn(0).getInt();
            return count > 0;
        }
        
        return false;
    }

    int32_t get_page_job_table(SQLite::Database db, const std::string task, const int32_t amount, const int32_t page, json& result) {
        SQLite::Statement query(db, "SELECT id, uuid, task, title, description, created_at FROM job ORDER BY weight WHERE task = ? LIMIT ? OFFSET ?;");
        query.bind(1, task);
        query.bind(2, amount);
        query.bind(3, page * amount);

        result.clear();
        result["data"] = json::array();

        while(query.executeStep()) {
            get_job_data(query, result);
        }

        return result["data"].size();
    }

    int32_t get_total_job_table(SQLite::Database db) {
        SQLite::Statement query(db, "SELECT COUNT(*) FROM job;");
        return query.getColumn(0).getInt();
    }

    int32_t get_total_job_table(SQLite::Database db, const std::string task) {
        SQLite::Statement query(db, "SELECT COUNT(*) FROM job WHERE task = ?;");
        query.bind(1, task);

        return query.getColumn(0).getInt();
    }

}