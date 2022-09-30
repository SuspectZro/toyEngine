#pragma once
//#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "Types.h"
#include <iostream>
#include <ostream>
//#include "InputManager.h"


using namespace data;

class GraphicsManager {
	friend class InputManager;
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
			Default.window_name = "ToyEngine";
			Default.window_fullscreen = false;
		};

		GLFWwindow* getWindowPointer();
		
	private:
		GLFWwindow* window;
		

};