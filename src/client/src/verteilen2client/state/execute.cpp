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
#include <verteilen2client/state/execute/job.h>
#include <verteilen2/enum/job_type.h>

namespace verteilen2::client {

    int32_t execute_worker_idle(App_data& app_data) {
        for(int32_t i = 0; i < 60; i++){
            if(app_data.workers[i].state.load() != ThreadState::Running){
                return i;
            }
        }
        return -1;
    }

    int32_t execute_total_idle(App_data& app_data) {
        int32_t c;
        for(int32_t i = 0; i < 60; i++){
            if(app_data.workers[i].state.load() != ThreadState::Running){
                c++;
            }
        }
        return c;
    }

    int32_t execute_total_running(App_data& app_data) {
        int32_t c;
        for(int32_t i = 0; i < 60; i++){
            if(app_data.workers[i].state.load() == ThreadState::Running){
                c++;
            }
        }
        return c;
    }

    std::array<bool, 60> execute_total_running_array(App_data& app_data) {
        std::array<bool, 60> a;
        for(int32_t i = 0; i < 60; i++){
            a[i] = app_data.workers[i].state.load() == ThreadState::Running;
        }
        return a;
    }

}