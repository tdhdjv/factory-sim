#include <string>
#include <vector>

namespace LongDay {
	enum LogStatus{
		INFO, 
		WARN,
		ERROR
	};

	struct LogEntry {
		std::string message;
		LogStatus status;
	};

	//Singleton cos why not
	class Logger {
	private:
		static Logger instance;
		std::vector<LogEntry> logs;
		Logger() = default;
		~Logger() = default;
		Logger(const Logger&) = delete;

		static Logger& get_instance();
	public:
		static void log(LogStatus status, std::string format, ...);
		static void clear();
		static const std::vector<LogEntry>& get_logs();
	};
}
