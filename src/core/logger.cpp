#include "logger.h"
#include <stdarg.h>

namespace LongDay {
	Logger& Logger::get_instance() {
		static Logger instance;
		return instance;
	}

	void Logger::log(LogStatus status, std::string format, ...) {
		char buffer[3200];

		va_list args;
		va_start(args, format);
		vsnprintf(buffer, sizeof(buffer), format.c_str(), args);
		va_end(args);

		LogEntry entry;
		entry.message = std::string(buffer);
		entry.status  = status;

		get_instance().logs.push_back(entry);
	}

	void Logger::clear() {
		get_instance().logs.clear();
	}

	const std::vector<LogEntry>& Logger::get_logs() {
        return get_instance().logs;
    } 
}
