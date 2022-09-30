#include "InputManager.h"
//#include "Engine.h";
//class Engine;



void InputManager::ShutDown() {

}

int InputManager::Update() {
	if (glfwWindowShouldClose(window)) {
		return 0;
	}
	KeyIsPressed();
	glfwPollEvents();
	return 1;
}



