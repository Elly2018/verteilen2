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
#include <verteilen2/env.h>
#include <fstream>
#include <string>

namespace verteilen2 {

    bool is_running_in_k8s() {
        if (std::filesystem::exists("/var/run/secrets/kubernetes.io")) {
            return true;
        }
        
        if (std::getenv("KUBERNETES_SERVICE_HOST") != nullptr) {
            return true;
        }
        return false;
    }

    bool is_running_in_docker() {
        if (std::filesystem::exists("/.dockerenv")) {
            return true;
        }

        std::ifstream cgroup_file("/proc/1/cgroup");
        if (cgroup_file.is_open()) {
            std::string line;
            while (std::getline(cgroup_file, line)) {
                if (line.find("docker") != std::string::npos || 
                    line.find("kubepods") != std::string::npos || 
                    line.find("overlay") != std::string::npos) {
                    return true;
                }
            }
        }
        return false;
    }

    AppEnvironment detect_environment() {
        if (is_running_in_k8s()) {
            return AppEnvironment::KUBERNETES;
        } else if (is_running_in_docker()) {
            return AppEnvironment::DOCKER;
        }
        return AppEnvironment::NATIVE;
    }

}
