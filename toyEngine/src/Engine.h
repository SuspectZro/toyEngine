#pragma once
#include "GraphicsManager.h"
#include "InputManager.h"
#include "SoundManager.h"
//#include "Types.h"

//using namespace data;

//namespace toyEngine{
//#pragma once
//#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "Types.h"
#include <iostream>
#include <ostream>


class Engine {
public:

	SoundManager* sound;
	GraphicsManager* graphics;
	InputManager* input;

	void Startup();
	void Shutdown();
	void RunGameLoop(UpdateCallback ucb);
	void PlaySound(const string);
	Engine();
	~Engine();

};








//}