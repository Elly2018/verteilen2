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
#include <verteilen2client/state/analyzer.h>
#include <verteilen2/proto_gen/header.pb-c.h>
#include <verteilen2/proto_gen/debug_log.pb-c.h>
#include <verteilen2/proto_gen/job.pb-c.h>
#include <verteilen2client/db/local_record.h>
#include <verteilen2client/state/execute/job.h>

namespace verteilen2::client {

    static void print_log(Verteilen2__DebugLog& raw_debuglog) {
        insert_log_table(raw_debuglog.uuid, raw_debuglog.title, raw_debuglog.content);
    }

    void analysis(App_data& app_data, Verteilen2__RawData& raw_msg) {
        switch(raw_msg.type) {
            default:
            case Verteilen2__MsgType::VERTEILEN2__MSG_TYPE__UNKNOWN:
                {
                    break;
                }
            case Verteilen2__MsgType::VERTEILEN2__MSG_TYPE__EXECUTE_JOB:
                {
                    Verteilen2__Job* executejob = verteilen2__job__unpack(NULL, raw_msg.data.len, raw_msg.data.data);
                    execute_job_run(app_data, executejob);
                    verteilen2__job__free_unpacked(executejob, NULL);
                    break;
                }
            case Verteilen2__MsgType::VERTEILEN2__MSG_TYPE__DEBUG_LOG:
                {
                    Verteilen2__DebugLog* debuglog = verteilen2__debug_log__unpack(NULL, raw_msg.data.len, raw_msg.data.data);
                    print_log(*debuglog);
                    verteilen2__debug_log__free_unpacked(debuglog, NULL);
                    break;
                }
        }
    }

}