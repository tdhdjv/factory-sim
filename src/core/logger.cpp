#include "logger.h"
#include <stdarg.h>
#include <iostream>

namespace LongDay {
	Logger& Logger::get_instance() {
		static Logger instance;
		return instance;
	}

	void Logger::log(LogStatus status, std::string format, ...) {
		char buffer[3200];
		const char* levelStrings[3] = {"INFO", "WARN", "ERROR"};

		va_list args;
		va_start(args, format);
		vsnprintf(buffer, sizeof(buffer), format.c_str(), args);
		va_end(args);
		char buffer2[3200];
		snprintf(buffer2, sizeof(buffer2), "[%s] %s\n", levelStrings[status], buffer);

		LogEntry entry;
		entry.message = std::string(buffer2);
		entry.status  = status;

		get_instance().logs.push_back(entry);


		const char* color[3] = {"1;32", "1;33", "1;31"};
		std::cout << "\033[" << color[status] << "m"<< buffer2;
	}

	void Logger::clear() {
		get_instance().logs.clear();
	}

	const std::vector<LogEntry>& Logger::get_logs() {
        return get_instance().logs;
    } 
}
