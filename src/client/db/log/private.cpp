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
#include "private.h"
#include <filesystem>
#include <verteilen2/path.h>

namespace fs = std::filesystem;

namespace verteilen2::client {

    SQLite::Database get_database() {
        fs::path t = path_get_workpath(App_type::Client);

        t /= "record.db";

        SQLite::Database db = SQLite::Database(t.string(), SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);

        return db;
    }

    void create_log_table(SQLite::Database& db) {
        db.exec(R"SQL(
            CREATE TABLE IF NOT EXISTS log (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                -- Automatically generates a valid RFC-4122 UUIDv4 string if not provided
                job CHAR(36) NOT NULL DEFAULT (
                    lower(hex(randomblob(4))) || '-' ||
                    lower(hex(randomblob(2))) || '-4' ||
                    substr(lower(hex(randomblob(2))), 2) || '-' ||
                    substr('89ab', abs(random()) % 4 + 1, 1) || 
                    substr(lower(hex(randomblob(2))), 2) || '-' ||
                    lower(hex(randomblob(6)))
                ),
                title TEXT NOT NULL,
                content TEXT,
                updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
            );
        )SQL");
    }

    void drop_log_table(SQLite::Database& db) {
        db.exec(R"SQL(
            DROP TABLE IF EXISTS log;
        )SQL");
    }

    void insert_log_table(SQLite::Database& db, const char job[36], const std::string title, const std::string content) {
        SQLite::Statement query(db, "INSERT INTO log (job, title, content) VALUES(?, ?, ?);");
        query.bind(1, job);
        query.bind(2, title);
        query.bind(3, content);
        query.exec();
    }
}