#pragma once
//#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "Types.h"
#include <iostream>
#include <ostream>
//#include "Engine.h"
//#include "GraphicsManager.h"
using namespace data;

enum keyboard {
	A,
	S,
	D,
	W,
	Q,
	E,
	R,
	UP,
	LEFT,
	RIGHT,
	DOWN,
	RSHIFT,
	SLASH,
	undefined,
};
//namespace toyEngine { };
class Engine;

class InputManager {
	GLFWwindow* window;
	Engine* engine;
public:
	InputManager(Engine* e) : engine() {}
	void Startup(Engine*);
	void ShutDown();
	int Update();
	bool KeyIsPressed();
	//bool KeyIsDown(int key);
	//InputManager() {};

};