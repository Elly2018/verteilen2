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
#include <spdlog/spdlog.h>
#include <verteilen2/proto_gen/struct_header.pb.h>
#include <verteilen2/proto_gen/struct_debug_log.pb.h>
#include <verteilen2/proto_gen/struct_job.pb.h>
#include <verteilen2client/db/local_record.h>
#include <verteilen2client/state/execute/job.h>

namespace verteilen2::client {

    static void print_log(App_data& app_data, verteilen2::DebugLog* raw_data) {
        insert_log_table(app_data.db_getter(), raw_data->uuid(), raw_data->title(), raw_data->content());
    }

    void analysis(App_data& app_data, verteilen2::RawData& raw_msg) {
        switch(raw_msg.type()) {
            default:
            case verteilen2::MsgType_UNKNOWN:
                {
                    break;
                }
            case verteilen2::MsgType_EXECUTE_JOB:
                {
                    google::protobuf::Arena arena;
                    verteilen2::Job* executejob = google::protobuf::Arena::CreateMessage<verteilen2::Job>(&arena);
                    if(executejob->ParseFromArray(raw_msg.data().c_str(), raw_msg.data().size())) {
                        execute_job_run(app_data, executejob);
                    }
                    break;
                }
            case verteilen2::MsgType_DEBUG_LOG:
                {
                    google::protobuf::Arena arena;
                    verteilen2::DebugLog* debuglog = google::protobuf::Arena::CreateMessage<verteilen2::DebugLog>(&arena);
                    if(debuglog->ParseFromArray(raw_msg.data().c_str(), raw_msg.data().size())) {
                        print_log(app_data, debuglog);
                    }
                    break;
                }
        }
    }

}