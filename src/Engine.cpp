#include "Engine.h"

//namespace toyEngine {
	Engine::Engine() {
	graphics = new GraphicsManager();
	input = new InputManager(this);
	sound = new SoundManager();

	}

	Engine::~Engine() {
		delete graphics;
		delete input;
		delete sound;
	}

	void Engine::PlaySound(const string name) {
		sound->play(name);
	}
	void Engine::Startup() {
		sound->Startup();
		graphics->Startup();
		//GLFWwindow* window = graphics.getWindowPointer();
		input->Startup(this);
	}
	void Engine::Shutdown() {
		//input.Shutdown();
		graphics->Shutdown();
		sound->Shutdown();
	}

	void Engine::RunGameLoop(UpdateCallback ucb) {
		float targetFps = 60;
		intervals t(1. / targetFps);
		int numberOfTimes = 1;
		int counterFrame = 0;
		
		std::chrono::steady_clock::time_point t0 = std::chrono::steady_clock::now();
		bool running = true;
		while (running) {
			counterFrame++;
			if (counterFrame % int(targetFps * numberOfTimes) == 0) {
				intervals t1 = (std::chrono::steady_clock::now()) - t0;
				float trackFps = counterFrame / t1.count() / (targetFps * numberOfTimes);
				std::cout << trackFps * (targetFps*numberOfTimes) << "\n";
				t0 = std::chrono::steady_clock::now();
				counterFrame = 0;
				t = t * trackFps;
				
			}

			running = (input->Update() == 1);

			ucb();
			graphics->Draw();
			std::this_thread::sleep_for(t);
		}

	}
	void InputManager::Startup(Engine* e) {
		engine = e;
		window = e->graphics->getWindowPointer();
	}

	bool InputManager::KeyIsPressed() {
		int r;
		for (int i = A; i != undefined; i++) {
			switch (i) {
			case A:
				r = glfwGetKey(window, GLFW_KEY_A);
				if (r) {
					std::cout << "A" << "\n";


				}
				break;
			case S:
				r = glfwGetKey(window, GLFW_KEY_S);
				if (r) {
					std::cout << "S" << "\n";
					engine->PlaySound("complete");

				}
				break;
			case Q:
				r = glfwGetKey(window, GLFW_KEY_Q);
				if (r) {
					std::cout << "Quit" << "\n";
					glfwSetWindowShouldClose(window, true);
				}
				break;
			}
		}
		return false;
	}
//}