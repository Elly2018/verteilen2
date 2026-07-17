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
#include <verteilen2/data/project.h>
#include <unordered_map>
#include <string>
#include <verteilen2/data/task.h>

namespace verteilen2 {

    int32_t project_data_get_task_count(verteilen2::Project& project) {
        int32_t c = 0;
        for(int32_t i = 0; i < project.tasks_size(); i++){
            if (!project.tasks().at(i).vaild()) continue;
            c++;
        }
        return c;
    }

    int32_t project_data_get_task_count(verteilen2::Project& project, std::vector<verteilen2::Task>& tasks) {
        int32_t c = 0;
        std::unordered_map<std::string, bool> exists;
        for(int32_t i = 0; i < tasks.size(); i++){
            exists.insert({ std::string(tasks.at(i).uuid()), true });
        }
        for(int32_t i = 0; i < project.tasks_size(); i++){
            if (!project.tasks().at(i).vaild()) continue;
            if(exists.count(std::string(project.tasks().at(i).uuid())) == 0) continue;
            c++;
        }
        return c;
    }

    int32_t project_data_get_job_count(verteilen2::Project& project, std::vector<verteilen2::Task>& tasks) {
        int32_t c = 0;
        std::unordered_map<std::string, verteilen2::Task&> exists;
        for(int32_t i = 0; i < tasks.size(); i++){
            exists.insert({ std::string(tasks.at(i).uuid()), tasks.at(i) });
        }
        for(int32_t i = 0; i < project.tasks_size(); i++){
            std::string buff = std::string(project.tasks().at(i).uuid());
            if (!project.tasks().at(i).vaild()) continue;
            if (exists.count(buff) == 0) continue;
            c += task_data_get_job_count(exists.at(buff));
        }
        return c;
    }

    int32_t project_data_get_job_count(verteilen2::Project& project, std::vector<verteilen2::Task>& tasks, std::vector<verteilen2::Job>& jobs) {
        int32_t c = 0;
        std::unordered_map<std::string, verteilen2::Task&> exists;
        for(int32_t i = 0; i < tasks.size(); i++){
            exists.insert({ std::string(tasks.at(i).uuid()), tasks.at(i) });
        }
        for(int32_t i = 0; i < project.tasks_size(); i++){
            std::string buff = std::string(project.tasks().at(i).uuid());
            if (!project.tasks().at(i).vaild()) continue;
            if (exists.count(buff) == 0) continue;
            c += task_data_get_job_count(exists.at(buff), jobs);
        }
        return c;
    }

}