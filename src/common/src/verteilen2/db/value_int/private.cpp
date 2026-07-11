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
#include <verteilen2/db/vault/private.h>

namespace verteilen2 {

    int32_t create_vault_int_table(SQLite::Database db) {
        return db.exec(R"SQL(
            CREATE TABLE IF NOT EXISTS vault_int (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                vault_id INTEGER NOT NULL,
                order INTEGER,
                label TEXT NOT NULL,
                type INTEGER,
                value TEXT,
                created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP

                FOREIGN KEY (vault_id) REFERENCES vault(id)
                    ON DELETE CASCADE
                    ON UPDATE CASCADE
            );
        )SQL");
    }

    int32_t drop_vault_int_table(SQLite::Database db) {
        return db.exec(R"SQL(
            DELETE FROM vault_int;
        )SQL");
    }
    
}