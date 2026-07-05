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
#pragma once
#ifndef MASTER_LOGGER_H
#define MASTER_LOGGER_H
#include <crow.h>
#include <verteilen2master/config.h>
#include <spdlog/spdlog.h>

class CrowSpdlogBridge : public crow::ILogHandler {
public:
    void log(const std::string& message, crow::LogLevel level) override {
        // Map Crow's LogLevels to spdlog formats
        // Note: Crow's incoming message string does not end with a newline \n
        switch (level) {
            case crow::LogLevel::Debug:
                spdlog::debug("[Crow] {}", message);
                break;
            case crow::LogLevel::Info:
                spdlog::info("[Crow] {}", message);
                break;
            case crow::LogLevel::Warning:
                spdlog::warn("[Crow] {}", message);
                break;
            case crow::LogLevel::Error:
                spdlog::error("[Crow] {}", message);
                break;
            case crow::LogLevel::Critical:
                spdlog::critical("[Crow] {}", message);
                break;
        }
    }
};

#endif