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
			real width;
			real height;
			vec3 scale;
			bool isFlipped;

		};
		struct Shape {
			vec3 scale;
			real x;
			real y;
			//real z;
			vec3 color;
			float alpha;
			//int numVertices;
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
		void RenderFrame(std::vector<Sprite>& allSprites, std::vector<Shape>& allShapes);
		void CreateColoredSquareVertexBuffer();
		GraphicsManager() {
			Default.window_width = 800;
			Default.window_height = 600;
			Default.window_name = "ToyEngine";
			Default.window_fullscreen = false;
		};

		GLFWwindow* getWindowPointer();
		bool loadImage( const string& name, const string& path );
		void Draw(const std::vector<Sprite>& allSprites, int width, int height);
		//void Draw(const std::vector<PushBox>& allPushBoxes);
		void DrawShapes(const std::vector<Shape>& allShapes, int width, int height);
		glm::mat4 calculateTransformationMatrix(const Shape& shape);
		struct Image{
			sg_image image;
			real width;
			real height;
		};
/*
		void AddPushBox(real x, real y, real width, real height, vec4 color) {
			PushBox pushBox = { x, y, width, height, color };
			pushBoxes.push_back(pushBox);
		}
		*/
	private:
		
		GLFWwindow* window;
		sg_pipeline pipe;
		sg_bindings spriteBinds;
		sg_pipeline shapePipeline;
		sg_bindings shapeBinds;

		sg_pipeline pushBoxPipeline;
		sg_bindings pushBoxBinds;
		sg_pass_action pa{};
		sg_buffer vertex_buffer;
		sg_buffer colored_square_vertex_buffer;
		sg_shader coloredSquareShader;
		std::unordered_map< string, Image > images;
		std::vector<Sprite> sprites;
		std::vector<Shape> allShapes;
		//std::vector<PushBox> pushBoxes;

};