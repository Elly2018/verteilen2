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
#include <verteilen2/db/job_detail/private.h>
#include <verteilen2/path.h>
#include <verteilen2/uuid.h>

namespace verteilen2 {

    static void get_job_detail_data(SQLite::Statement& query, json& result) {
        json buff = json::object();

        int32_t id = query.getColumn(0).getInt();
        std::string uuid = query.getColumn(1).getText();
        std::string job = query.getColumn(2).getText();
        std::string title = query.getColumn(3).getText();
        int32_t weight = query.getColumn(4).getInt();
        int32_t type = query.getColumn(5).getInt();
        int32_t subtype = query.getColumn(6).getInt();
        std::string data = query.getColumn(7).getText();
        std::string created_at = query.getColumn(8).getText();

        buff["id"] = id;
        buff["uuid"] = uuid;
        buff["job"] = job;
        buff["weight"] = weight;
        buff["type"] = type;
        buff["subtype"] = subtype;
        buff["data"] = data;
        buff["created_at"] = created_at;

        result["data"].push_back(buff);
    }

    int32_t create_job_detail_table(SQLite::Database db) {
        db.exec("PRAGMA foreign_keys = ON;");
        return db.exec(R"SQL(
            CREATE TABLE IF NOT EXISTS job_detail (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                uuid CHAR(36) NOT NULL,
                job CHAR(36) NOT NULL,
                weight INTEGER NOT NULL,
                type INTEGER NOT NULL,
                subtype INTEGER NOT NULL,
                data BLOB NOT NULL,
                created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,

                FOREIGN KEY (job) REFERENCES job(uuid)
                    ON DELETE CASCADE
                    ON UPDATE CASCADE
            );
        )SQL");
    }

    int32_t insert_job_detail_table(SQLite::Database db, std::string job, const int32_t weight, const int32_t type, const int32_t subtype, std::string data) {
        SQLite::Statement query(db, "INSERT INTO job_detail (uuid, job, weight, type, subtype, data) VALUES(?, ?, ?, ?, ?, ?);");
        query.bind(1, generate_uuid());
        query.bind(2, job);
        query.bind(3, weight);
        query.bind(4, type);
        query.bind(5, subtype);
        query.bind(6, data);
        return query.exec();
    }

    int32_t update_job_detail_table(SQLite::Database db, std::string uuid, const int32_t weight, const int32_t type, const int32_t subtype, std::string data) {
        SQLite::Statement query(db, "UPDATE job SET weight = ?, type = ?, subtype = ?, data = ? WHERE uuid = ?;");
        query.bind(1, weight);
        query.bind(2, type);
        query.bind(3, subtype);
        query.bind(4, data);
        query.bind(5, uuid);
        return query.exec();
    }

    int32_t drop_job_detail_table(SQLite::Database db) {
        return db.exec(R"SQL(
            DELETE FROM job_detail;
        )SQL");
    }

    int32_t get_page_job_detail_table(SQLite::Database db, const std::string job, const int32_t amount, const int32_t page, json& result) {
        SQLite::Statement query(db, "SELECT id, uuid, job, weight, type, subtype, data, created_at FROM job_detail ORDER BY weight WHERE job = ? LIMIT ? OFFSET ?;");
        query.bind(1, job);
        query.bind(2, amount);
        query.bind(3, page * amount);

        result.clear();
        result["data"] = json::array();

        while(query.executeStep()) {
            get_job_detail_data(query, result);
        }

        return result["data"].size();
    }

    int32_t get_total_job_detail_table(SQLite::Database db) {
        SQLite::Statement query(db, "SELECT COUNT(*) FROM job_detail;");
        return query.getColumn(0).getInt();
    }

    int32_t get_total_job_detail_table(SQLite::Database db, const std::string job) {
        SQLite::Statement query(db, "SELECT COUNT(*) FROM job_detail WHERE job = ?;");
        query.bind(1, job);

        return query.getColumn(0).getInt();
    }
    
}