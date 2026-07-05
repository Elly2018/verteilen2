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
#include <verteilen2server/db/local_record.h>
#include <filesystem>
#include <SQLiteCpp/SQLiteCpp.h>
#include <verteilen2/path.h>
#include <verteilen2/db/log/private.h>
#include <verteilen2/db/job/private.h>
#include <verteilen2/db/task/private.h>
#include <verteilen2/db/project/private.h>
#include <verteilen2/db/project_vault/private.h>
#include <verteilen2/db/vault/private.h>
#include <verteilen2/db/node/private.h>

namespace fs = std::filesystem;

namespace verteilen2::server {

    SQLite::Database get_database() {
        return get_database(App_type::Server);
    }

    void init_database(App_data& appdata) {
        appdata.db_getter = get_database;
        create_log_table(appdata.db_getter());
        create_job_table(appdata.db_getter());
        create_vault_table(appdata.db_getter());
        create_node_table(appdata.db_getter());
        create_task_table(appdata.db_getter());
        create_project_table(appdata.db_getter());
        create_project_vault_table(appdata.db_getter());
        insert_log_table(appdata.db_getter(), "none", "Initialization", "Server has been activate.");
    }

}