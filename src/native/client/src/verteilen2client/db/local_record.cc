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
#include <verteilen2client/db/local_record.h>
#include <filesystem>
#include <SQLiteCpp/SQLiteCpp.h>
#include <verteilen2/path.h>
#include <verteilen2/db/local_record.h>
#include <verteilen2/db/log/private.h>
#include <verteilen2/db/job/private.h>
#include <verteilen2/db/job_detail/private.h>

namespace fs = std::filesystem;

namespace verteilen2::client {

    SQLite::Database get_database() {
        return get_database(App_type::Client);
    }

    void init_database(App_data& appdata) {
        appdata.db_getter = get_database;
        create_log_table(appdata.db_getter());
        create_job_table(appdata.db_getter());
        create_job_detail_table(appdata.db_getter());
        insert_log_table(appdata.db_getter(), "Initialization", "Client has been activate.");
    }
}