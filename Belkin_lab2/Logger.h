#pragma once
#include <string>

class Logger {
public:
    static void log(const std::string& message);
    static void logAction(const std::string& action, int id = -1);
    static void logError(const std::string& error);
};