#pragma once
//#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "Types.h"
#include <iostream>
#include <ostream>

using namespace data;

class GraphicsManager {
	public:
		

		struct windowProperty {
			int window_width;
			int window_height;
			string window_name;
			bool window_fullscreen;
		};

		windowProperty Default;
		void Startup();
		void Shutdown();
		void Draw();
		
		GraphicsManager() {
			Default.window_width = 600;
			Default.window_height = 300;
			Default.window_name = "default";
			Default.window_fullscreen = false;
		};
	private:
		GLFWwindow* window;
		

};