
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "window.h"

namespace LongDay {
	static void glfw_error_callback(int error, const char* description)
	{
		fprintf(stderr, "GLFW Error %d: %s\n", error, description);
	}

	Window::Window(u32 width, u32 height, std::string name) 
		:width(width), height(height), name(name) {
		 glfwSetErrorCallback(glfw_error_callback);
		 if (!glfwInit())
			 return;

		 // GL 3.0 + GLSL 130
		 const char* glsl_version = "#version 130";
		 glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		 glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

		 // Create window with graphics context
		 float main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor()); // Valid on GLFW 3.3+ only
		 internal = glfwCreateWindow((int)(width * main_scale), (int)(height * main_scale), name.c_str(), nullptr, nullptr);
		 if (internal == nullptr)
			 return;
		 glfwMakeContextCurrent(internal);
		 glfwSwapInterval(1); // Enable vsync

		 // Setup Dear ImGui context
		 IMGUI_CHECKVERSION();
		 ImGui::CreateContext();
		 // Setup Dear ImGui style
		 ImGui::StyleColorsDark();
		 //ImGui::StyleColorsLight();

		 // Setup scaling
		 ImGuiStyle& style = ImGui::GetStyle();
		 style.ScaleAllSizes(main_scale);        // Bake a fixed style scale. (until we have a solution for dynamic style scaling, changing this requires resetting Style + calling this again)
		 style.FontScaleDpi = main_scale;        // Set initial font scale. (in docking branch: using io.ConfigDpiScaleFonts=true automatically overrides this for every window depending on the current monitor)

		 // Setup Platform/Renderer backends
		 ImGui_ImplGlfw_InitForOpenGL(internal, true);
		 ImGui_ImplOpenGL3_Init(glsl_version);
	}
	
	void Window::update() {
		glfwPollEvents();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void Window::render() {
		ImGui::Render();

		int display_w, display_h;
		glfwGetFramebufferSize(internal, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(0,0,0,1);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(internal);
	}

	b8 Window::is_running() {
		return !glfwWindowShouldClose(internal);
	}

	Window::~Window() {
		 // Cleanup
		 ImGui_ImplOpenGL3_Shutdown();
		 ImGui_ImplGlfw_Shutdown();
		 ImGui::DestroyContext();
		 glfwDestroyWindow(internal);
		 glfwTerminate();
	}
}

