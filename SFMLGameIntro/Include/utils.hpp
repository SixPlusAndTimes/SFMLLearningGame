#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include <string>
#include <source_location>

namespace TerminalColor {
    constexpr const char* RESET   = "\033[0m";
    constexpr const char* RED     = "\033[31m";
    constexpr const char* GREEN   = "\033[32m";
    constexpr const char* YELLOW  = "\033[33m";
    constexpr const char* BLUE    = "\033[34m";
    constexpr const char* MAGENTA = "\033[35m";
    constexpr const char* CYAN    = "\033[36m";
    constexpr const char* WHITE   = "\033[37m";
    constexpr const char* BOLD    = "\033[1m";
}

enum class LogLevel {
    DEBUG,
    INFO,
    WARN,
    ERROR
};

static LogLevel globalLogLevel = LogLevel::INFO;
void setLogLevel(LogLevel level);


template<typename... Args>
void Log(const std::string& levelColor,
         const LogLevel&    curLoglevel,
         const std::string& levelName,
         const std::source_location& location,
         const std::string& format,
         Args&&... args) {
    if (curLoglevel < globalLogLevel) return;
    std::string msg = std::vformat(format, std::make_format_args(args...));

    std::cout << levelColor << "[" << levelName << "]" << TerminalColor::RESET
              << " "
              << TerminalColor::CYAN << msg << TerminalColor::RESET
              << " (" << location.file_name() << ":" << location.line() << ")"
              << std::endl;
}

#define LOG_DEBUG(...)    Log(TerminalColor::CYAN,    LogLevel::DEBUG, "DEBUG",   std::source_location::current(), __VA_ARGS__)
#define LOG_INFO(...)     Log(TerminalColor::GREEN,   LogLevel::INFO, "INFO",    std::source_location::current(), __VA_ARGS__)
#define LOG_WARN(...)     Log(TerminalColor::YELLOW,  LogLevel::WARN,  "WARNING", std::source_location::current(), __VA_ARGS__)
#define LOG_ERROR(...)    Log(TerminalColor::RED,     LogLevel::ERROR,  "ERROR",   std::source_location::current(), __VA_ARGS__)

#endif // UTILS_H