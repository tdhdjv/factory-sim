#include "define.h"
#include <GLFW/glfw3.h> // Will drag system OpenGL headers
#include <string>

namespace LongDay {
	class Window {
	private:
		u32 width;
		u32 height;
		std::string name;
		GLFWwindow* internal;
	public:
		explicit Window(u32 width, u32 height, std::string name);
		~Window();
		b8 is_running();
		void update();
		void render();
	};
}
