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
#include <verteilen2/path.h>

namespace verteilen2::client {

    int32_t create_job_detail_table(SQLite::Database& db) {
        db.exec("PRAGMA foreign_keys = ON;");
        return db.exec(R"SQL(
            CREATE TABLE IF NOT EXISTS job_detail (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                job CHAR(36) NOT NULL,
                title TEXT NOT NULL,
                content TEXT,
                created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,

                FOREIGN KEY (job) REFERENCES job(job_id)
                    ON DELETE CASCADE
                    ON UPDATE CASCADE
            );
        )SQL");
    }

    int32_t drop_job_detail_table(SQLite::Database& db) {
        return db.exec(R"SQL(
            DROP TABLE IF EXISTS job_detail;
        )SQL");
    }

}