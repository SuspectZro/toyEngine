#include "Engine.h"
namespace toyEngine {
	void Engine::Startup() {
		graphics.Startup();
		//input.Startup();
	}
	void Engine::Shutdown() {
		//input.Shutdown();
		graphics.Shutdown();
	}

	void Engine::RunGameLoop(UpdateCallback ucb) {
		intervals t(1. / 60.);
		while (true) {
			//input.Update();
			ucb();
			graphics.Draw();
			std::this_thread::sleep_for(t);
		}

	}
}