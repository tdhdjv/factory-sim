#include "logger.h"
#include "define.h"
#include <sstream>
#include <stdarg.h>
#include <iostream>

namespace LongDay {
    Logger::Logger(const std::string& fileName) {
        file.open(fileName);
    }

    Logger::~Logger() {
        file.close();
    }

    void Logger::log(LogLevel level, const char* format, ...) {
        const char* levelStrings[2] = {"ERROR", "INFO"};
        const char* colour_strings[2] = {"1;31", "1;32"};

        __builtin_va_list arg_ptr;
        va_start(arg_ptr, format);
        int size = vsnprintf(nullptr, 0, format, arg_ptr);
        va_end(arg_ptr);

        std::string rawMessage(size + 1, '\0');
        va_start(arg_ptr, format);
        vsnprintf(rawMessage.data(), size + 1, format, arg_ptr);
        va_end(arg_ptr);

        std::ostringstream oss;
        oss << "[" << levelStrings[level] << "] " << rawMessage << "\n";
        std::string outMessage = oss.str();
        std::cout << "\033[" << colour_strings[level] << "m" << outMessage << std::endl;
        file << outMessage << '\n';
    }
}
