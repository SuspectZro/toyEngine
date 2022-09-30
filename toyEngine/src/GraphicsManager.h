#pragma once
//#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "Types.h"
#include <iostream>
#include <ostream>
//#define SOKOL_GLCORE33
#include "sokol_gfx.h"
#include "glm/glm.hpp"
//#include "InputManager.h"

#include "glm/gtc/matrix_transform.hpp"

using namespace data;

class GraphicsManager {
	friend class InputManager;
	public:
		
		struct Sprite {
			string name;
			real x;
			real y;
			real z;
			vec3 scale;

		};

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
		bool loadImage( const string& name, const string& path );
		void Draw(const std::vector<Sprite>& allSprites);
		
		


	private:
		GLFWwindow* window;
		sg_pipeline pipe;
		sg_bindings binds;
		sg_pass_action pa;
		sg_buffer vertex_buffer;
		std::unordered_map< string, sg_image > images;
		std::vector<Sprite> sprites;

};