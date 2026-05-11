#include "logger.h"

namespace LongDay {
  Logger::Logger(const std::string& fileName) {
    file.open(fileName);
  }

  Logger::~Logger() {

  }
}
