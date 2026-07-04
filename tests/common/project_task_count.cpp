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
#include <iostream>
#include <verteilen2/data/project.h>

int main() {

    {
        Verteilen2__Project project = Verteilen2__Project();

        int32_t c = verteilen2::project_data_get_task_count(project);
        if(c != 0){
            std::cerr << "[Common] The init project should have 0 tasks count, getting: " << c << "\n";
            return 1;
        }
    }

    {
        Verteilen2__Project project = Verteilen2__Project();

        project.n_tasks = 2;
        project.tasks = (Verteilen2__DataField **)malloc(project.n_tasks * sizeof(Verteilen2__DataField*));
        project.tasks[0]->vaild = true;
        project.tasks[1]->vaild = true;


        int32_t c = verteilen2::project_data_get_task_count(project);
        if(c != 2){
            std::cerr << "[Common] The project should have 2 tasks count, getting: " << c << "\n";
            return 1;
        }

        free(project.tasks);
    }
    

    {
        Verteilen2__Project project = Verteilen2__Project();

        project.n_tasks = 60;
        project.tasks = (Verteilen2__DataField **)malloc(project.n_tasks * sizeof(Verteilen2__DataField*));
        for(int32_t i = 0; i < 60; i++){
            project.tasks[i] = new Verteilen2__DataField();
            project.tasks[i]->vaild = true;
        }

        int32_t c = verteilen2::project_data_get_task_count(project);
        if(c != project.n_tasks){
            std::cerr << "[Common] The project should have " << project.n_tasks << " tasks count, getting: " << c << "\n";
            return 1;
        }

        free(project.tasks);
    }
}