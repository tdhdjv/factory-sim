#include <string>
#include <fstream>

namespace LongDay {
  enum LogLevel {
    LOG_LEVEL_ERROR = 0,
    LOG_LEVEL_INFO = 1,
  };

  class Logger {
  private:
    std::ifstream file;
  public:
    Logger(const std::string& fileName);
    ~Logger();
    void log(LogLevel level, const std::string& format, ...);
  };
}
