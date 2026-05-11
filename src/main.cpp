#include <iostream>
#include "imgui.h"
#include "core/logger.h"

int main(void) {
  std::cout << IMGUI_CHECKVERSION() << std::endl;
  std::cout << "Hello World\n" << std::endl;
  LongDay::Logger logger = {0};
}
