#include "Logger.h"
#include <iostream>
#include <fstream>

void Logger::log(const std::string& message) {
    std::ofstream file("app_log.txt", std::ios::app);
    if (file.is_open()) {
        file << message << std::endl;
    }
}

void Logger::logAction(const std::string& action, int id) {
    std::string message = action;
    if (id != -1) {
        message += " (ID:" + std::to_string(id) + ")";
    }
    log(message);
}

void Logger::logError(const std::string& error) {
    log("ÎØÈÁÊÀ: " + error);
}