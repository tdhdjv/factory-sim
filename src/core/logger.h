#include <string>
#include <fstream>

namespace LongDay {
  enum LogLevel {
    LOG_LEVEL_ERROR = 0,
    LOG_LEVEL_INFO = 1,
  };

  class Logger {
  private:
    std::fstream file;
  public:
    Logger(const std::string& fileName);
    ~Logger();
    void log(LogLevel level, const char* format, ...);
  };
}
