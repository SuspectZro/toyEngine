#pragma once
#include "GraphicsManager.h"
//#include "InputManager.h"
#include <functional>
#include<chrono>
#include<thread>

typedef std::function<void()> UpdateCallback;
typedef std::chrono::duration<real> intervals;

namespace toyEngine{
	class Engine {
		public:
			
			GraphicsManager graphics;
			//InputManager input;

			void Startup();
			void Shutdown();
			void RunGameLoop(UpdateCallback ucb);

			Engine() {};
	};








}