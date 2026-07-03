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
#include <verteilen2/path.h>
#include <iostream>
#include <cstdlib>

#if defined(_WIN32)
    #include <windows.h>
    #include <shlobj.h>
#else
    #include <unistd.h>
    #include <pwd.h>
    #include <sys/types.h>
#endif

namespace verteilen2 {

    static fs::path path_get_home_cross() {
#if defined(_WIN32)
        // 1. Try secure native Windows API (handles Unicode usernames correctly)
        PWSTR path = nullptr;
        if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Profile, 0, nullptr, &path))) {
            fs::path home_path(path);
            CoTaskMemFree(path);
            return home_path;
        }
        
        // 2. Fallback to Windows environment variables if API fails
        const char* userprofile = std::getenv("USERPROFILE");
        if (userprofile) return fs::path(userprofile);
        
        const char* homedrive = std::getenv("HOMEDRIVE");
        const char* homepath = std::getenv("HOMEPATH");
        if (homedrive && homepath) return fs::path(homedrive) / homepath;
#else
        // 1. Try POSIX environment variable
        const char* home_env = std::getenv("HOME");
        if (home_env) return fs::path(home_env);

        // 2. Fallback to system password database (if environment is wiped/sudo)
        struct passwd* pw = getpwuid(getuid());
        if (pw && pw->pw_dir) return fs::path(pw->pw_dir);
#endif
        return fs::path();
    }

    fs::path path_get_home() {
        fs::path p = path_get_home_cross();
        if(!fs::exists(p)) {
            fs::create_directories(p);
        }
        return p;
    }

    fs::path path_get_workpath(const App_type type) {
        fs::path p = path_get_home() / ".verteilen2";
        if(!fs::exists(p)) {
            std::cout << "Create folder: " << p << std::endl;
            fs::create_directories(p);
        }

        switch(type) {
            case App_type::CLI:
                p /= "cli";
                break;
            case App_type::Master:
                p /= "master";
                break;
            case App_type::Server:
                p /= "server";
                break;
            default:
            case App_type::Client:
                p /= "client";
                break;
        }

        if(!fs::exists(p)) {
            std::cout << "Create folder: " << p << std::endl;
            fs::create_directories(p);
        }

        return p;
    }

}