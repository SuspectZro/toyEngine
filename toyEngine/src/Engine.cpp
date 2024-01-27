#include "Engine.h"

//namespace toyEngine {
	Engine::Engine() {
	graphics = new GraphicsManager();
	input = new InputManager(this);
	sound = new SoundManager();
	ecs = new EntityManager();
	script = new ScriptManager(this);
	}

	Engine::~Engine() {
		delete graphics;
		delete input;
		delete sound;
		delete ecs;
		delete script;
	}

	void Engine::PlaySound(const string name) {
		sound->play(name);
	}
	void Engine::Startup() {
		sound->Startup();
		graphics->Startup();
		//GLFWwindow* window = graphics.getWindowPointer();
		input->Startup(this);
		ecs->StartUp();
#if graph
		script->StartUp(graphics, ecs );
#elif ECS
		script->StartUp(ecs, graphics);
#else
		script->StartUp(this);
#endif

	}
	void Engine::Shutdown() {
		//input.Shutdown();
		graphics->Shutdown();
		sound->Shutdown();
		ecs->ShutDown();
		script->ShutDown();
	}

	void Engine::RunGameLoop(UpdateCallback ucb) {
		const double targetFps = 60.0;
		const double targetFrameDuration = 1.0 / targetFps;
		auto lastFrameTime = std::chrono::high_resolution_clock::now();
		bool running = true;
		std::vector<GraphicsManager::Sprite> sprites;
		std::vector<GraphicsManager::Shape> allShapes;
		//std::vector<GraphicsManager::PushBox> pushBoxes;

		int frameCount = 0;
		double totalTime = 0.0;
		double yAxisCushion;

		while (running) {
			// Calculate elapsed time since the last frame
			auto currentTime = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> frameDuration = currentTime - lastFrameTime;
			lastFrameTime = currentTime;

			// Calculate sleep time to achieve the target frame rate
			double sleepTime = targetFrameDuration - frameDuration.count();
			if (sleepTime > 0) {
				std::this_thread::sleep_for(std::chrono::duration<double>(sleepTime));
			}

			// Your update and rendering code here
			running = (input->Update() == 1);
			ucb();

			ecs->ForEach<Sprite, Position,isFlipped>([&](EntityID id) {
				GraphicsManager::Sprite s;
				Position p = ecs->Get<Position>(id);
				Sprite sp = ecs->Get<Sprite>(id);
				isFlipped sf = ecs->Get<isFlipped>(id);
				s.x = p.x;
				s.y = p.y;
				s.z = 0;
				s.isFlipped = sf.isFlipped;
				s.name = sp.image;
				real scale = ecs->Get<Sprite>(id).size;
				s.scale = vec3(scale, scale, scale);
				sprites.push_back(s);
				});
			//rendering logic such as facing each other while not preforming an action
			// entities with IDs 3 and 4 are the ones I want to compare
			EntityID id1 = 3;
			EntityID id2 = 4;

			// Get components for the first entity
			Position p1 = ecs->Get<Position>(id1);
			State playerState1 = ecs->Get<State>(id1);
			isFlipped& flipped1 = ecs->Get<isFlipped>(id1);

			// Get components for the second entity
			Position p2 = ecs->Get<Position>(id2);
			State playerState2 = ecs->Get<State>(id2);
			isFlipped& flipped2 = ecs->Get<isFlipped>(id2);

			// Check if the first player is on the opposite side
			if ((p1.x > p2.x) && (playerState1.name != "Jumping" && flipped1.isFlipped == false) ) {
				// Player 1 is on the opposite side,flip
				flipped1.isFlipped = true;  
				//std::cout << "Player " << id1 << " is flipped" << std::endl;
			}
			if ((p1.x < p2.x) && (playerState1.name != "Jumping" && flipped1.isFlipped == true)){
				// Player 1 is on the same side,  don't flip
				flipped1.isFlipped = false; 
				//std::cout << "Player " << id1 << " is not flipped" << std::endl;
			}

			// Check if the second player is on the opposite side
			if (p2.x > p1.x && playerState2.name != "Jumping") {
				
				flipped2.isFlipped = false; 
				//std::cout << "Player " << id2 << " is flipped" << std::endl;
			}
			else if(playerState2.name != "Jumping") {
				
				flipped2.isFlipped = true;  
				//std::cout << "Player " << id2 << " is not flipped" << std::endl;
			}



			ecs->ForEach<Script>([&](EntityID id) {

				script->execute(ecs->Get<Script>(id).name, id);

				});
			double deltaTime = frameDuration.count();
			// Physics System
			ecs->ForEach<Physics, Position, Collision>([&](EntityID id) {
				Physics& physics = ecs->Get<Physics>(id);
				Position& position = ecs->Get<Position>(id);
				Collision& collision = ecs->Get<Collision>(id);

				real previousY = position.y;
				real previousX = position.x;
				const double maxVelocity = 3.0; // Set your desired maximum velocity
				
				// Inside your physics update loop
				if (physics.x > maxVelocity) {
					physics.x = maxVelocity;
				}
				else if (physics.x < -maxVelocity) {
					physics.x = -maxVelocity;
				}
				// Update position based on physics in bounds of the stage
				position.x += physics.x;
				
				position.y += physics.y;

				// Gradually apply gravity up to maxGravity

				physics.y += min(physics.gravity * deltaTime,physics.maxGravity );

				// Check for collisions with other entities
				ecs->ForEach<Collision, Position, Physics>([&](EntityID otherID) {
					if (id != otherID) {
						Collision& otherCollision = ecs->Get<Collision>(otherID);
						Position& otherPosition = ecs->Get<Position>(otherID);
						Physics& otherPhysics = ecs->Get<Physics>(otherID);

						real spacing = (collision.width + otherCollision.width);

						
						if (!collision.isStatic && otherCollision.isStatic) {
							yAxisCushion = 30.0;
						}
						else {
							yAxisCushion = 10;
						}
						CollisionResult resultY = CheckCollisionY(collision, position, otherCollision, otherPosition, yAxisCushion);
						CollisionResult resultX = CheckCollisionX(collision, position, otherCollision, otherPosition);
						
						if ((resultX.collisionX && !collision.isStatic) || (resultY.collisionY && !resultX.collisionX && !collision.isStatic)) {

							if (resultY.collisionY && !resultX.collisionX && otherCollision.isStatic) {
								// Handle logic when on the ground (Y collision)
								physics.y = 0.0;
								position.y = previousY + min(resultY.penetrationY, 0.0);
							}

							if (resultX.collisionX && resultY.collisionY && (!collision.isStatic && otherCollision.isStatic)) {
								// Handle logic when in the air (X collision)
								std::cout << "Collision Detected in the air " << std::endl;
								physics.x = 0.0;
								position.x = previousX + min(resultX.penetrationX, 0.0);
								
								
							}
					
							// Player-to-player collision logic
							if (!collision.isStatic && !otherCollision.isStatic) {
								std::cout << "Collision Detected with player " << std::endl;

								// Calculate velocity difference
								real velocityDifference = physics.x - otherPhysics.x;
								real horizontalCenterDistance = std::abs(position.x - otherPosition.x);
								real pushStrengthX = 0.2;
								real pushFractionX = 0.5;
								real pushAmountX = velocityDifference * pushFractionX;
								real adjustedPushAmountX = (spacing - horizontalCenterDistance) * pushStrengthX;
								
						
									
								if (resultY.collisionY && !otherCollision.isStatic) {
									// Handle logic when jumping on players (Y collision)
									
								}
										// Only apply the pushing effect if the pushing player has a higher velocity
								if (velocityDifference != 0.0) {
									real pushFraction = 0.5;  // Adjust this value to control the pushing effect
									real pushAmount = std::abs(velocityDifference) * pushFraction;

									if (velocityDifference > 0.0) {
												// Pushing from the right side
										if (otherPosition.x < 115) {
													//std::cout << "Pushing from the right" << std::endl;
											otherPosition.x += pushAmount;
										}
										else {
											std::cout << "Stop pushing" << std::endl;
											position.x = previousX + min(resultX.penetrationX, 0.0);
										}
									}
									else {
												// Pushing from the left side
										if (otherPosition.x > -115) {
													//std::cout << "Pushing from the left" << std::endl;
													otherPosition.x -= pushAmount;
										}
										else {
											std::cout << "Stop pushing" << std::endl;
											position.x = previousX + min(resultX.penetrationX, 0.0);
										}
									}
									
								}
								std::cout << "hcD: " << horizontalCenterDistance << std::endl;
									std::cout << "spacing: " << spacing << std::endl;
								if (horizontalCenterDistance < spacing) {
									if (position.x < otherPosition.x) {
												// Player is to the right of the other player
										std::cout << "Adjusted Push Amount X: " << adjustedPushAmountX << std::endl;

										if (otherPosition.x <= 115) {
											otherPosition.x += adjustedPushAmountX;
										}
										else {
											std::cout << "Stop pushing" << std::endl;
											position.x = previousX + min(resultX.penetrationX, 0.0);
										}
									}
									else {
												// Player is to the left of the other player
										std::cout << "ELSE Adjusted Push Amount X: " << adjustedPushAmountX << std::endl;
										if (otherPosition.x >= -115) {
											otherPosition.x -= adjustedPushAmountX;
										}
										else {
											std::cout << "Stop pushing" << std::endl;
											position.x = previousX + min(resultX.penetrationX, 0.0);
										}
												//position.x -= adjustedPushAmountX;
									}
								}
								
							}
						}
								




						
						
					}
				});


			});


			
			// Draw after populating the sprites vector.
			graphics->RenderFrame(sprites,allShapes);
			//graphics->Draw(sprites);
			//graphics->DrawShapes(allShapes);
			//graphics->Draw(pushBoxes);

			// Clear after drawing.
			
			sprites.clear();
			allShapes.clear();
			//pushBoxes.clear();

			// Update FPS counter
			frameCount++;
			totalTime += frameDuration.count();

			if (totalTime >= 1.0) {
				double currentFps = frameCount / totalTime;
				std::cout << "FPS: " << currentFps << std::endl;
				frameCount = 0;
				totalTime = 0.0;
			}
		}
	}


	void InputManager::Startup(Engine* e) {
		engine = e;
		window = e->graphics->getWindowPointer();
	}
	void ScriptManager::StartUp(Engine* e) {
		LoadScript("MasterScript.lua");

		engine = e;
		lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::table, sol::lib::string, sol::lib::os, sol::lib::io, sol::lib::package);
		lua.script("math.randomseed(0)");
		//lua.new_usertype<glm::vec3>("vector",
		//	sol::constructors<glm::vec3(),glm::vec3(float,float,float)>(),"x",&glm::vec3::x, "y", &glm::vec3::y, "z", &glm::vec3::z);
		lua.new_usertype<glm::vec3>("vec3",
			sol::constructors<glm::vec3(), glm::vec3(float), glm::vec3(float, float, float)>(),
			"x", &glm::vec3::x,
			"y", &glm::vec3::y,
			"z", &glm::vec3::z,
			// optional and fancy: operator overloading. see: https://github.com/ThePhD/sol2/issues/547
			sol::meta_function::addition, sol::overload([](const glm::vec3& v1, const glm::vec3& v2) -> glm::vec3 { return v1 + v2; }),
			sol::meta_function::subtraction, sol::overload([](const glm::vec3& v1, const glm::vec3& v2) -> glm::vec3 { return v1 - v2; }),
			sol::meta_function::multiplication, sol::overload(
				[](const glm::vec3& v1, const glm::vec3& v2) -> glm::vec3 { return v1 * v2; },
				[](const glm::vec3& v1, float f) -> glm::vec3 { return v1 * f; },
				[](float f, const glm::vec3& v1) -> glm::vec3 { return f * v1; }
			)
			);
		//lua.new_enum("Stance",
		//	"Idle", 0,
		//	"Punch", 1,
		//	"Straight", 2
		//);

		//this is for lua to use these keys
		lua.new_enum("KEYBOARD",
			//"SPACE", KEY_SPACE,
			"A", GLFW_KEY_A,
			"S", GLFW_KEY_S,
			"D", GLFW_KEY_D,
			"W", GLFW_KEY_W,
			"E", GLFW_KEY_E,
			"R", GLFW_KEY_R,
			"I", GLFW_KEY_I,
			"P", GLFW_KEY_P,
			"UP", GLFW_KEY_UP,
			"LEFT", GLFW_KEY_LEFT,
			"RIGHT", GLFW_KEY_RIGHT,
			"DOWN", GLFW_KEY_DOWN,
			"RSHIFT", GLFW_KEY_RIGHT_SHIFT,
			"SLASH", GLFW_KEY_SLASH

		);
		lua.set_function("Play", [&](string s) {
			engine->PlaySound(s);
			});
		lua.set_function("KeyIsDown", [&](const int keycode) -> bool {
			return(glfwGetKey(engine->graphics->getWindowPointer(), keycode) == 0 ? false : true);
			//return input->KeyIsDown(keycode);
			});
		//lua.set_function("LoadScript", [&](const string name, const string path) {
		//	LoadScript(name, path);
		//	});




		lua.new_usertype<Position>("Position",
			sol::constructors<Position()>(),
			"px", &Position::x,
			"py", &Position::y
			);

		lua.new_usertype<Collision>("Collision",
			sol::constructors<Collision()>(),
			"width", &Collision::width,
			"height", &Collision::height,
			"isStatic", &Collision::isStatic
			);
		lua.new_usertype<Physics>("Physics",
			sol::constructors<Position()>(),
			"velocityX", &Physics::x,
			"velocityY", &Physics::y,
			"gravity", &Physics::gravity,
			"maxGravity", &Physics::maxGravity,
			"friction", &Physics::friction
			);

		lua.new_usertype<Flag>("Flag",
			sol::constructors<Flag()>(),
			"f", &Flag::flag,
			"charge", &Flag::charge
			);
		lua.new_usertype<isFlipped>("isFlipped",
			sol::constructors<isFlipped()>(),
			"isFlipped", &isFlipped::isFlipped
			);
		lua.new_usertype<Sprite>("Sprite",
			sol::constructors<Sprite()>(),
			"name", &Sprite::image,
			"size", &Sprite::size
			);
		lua.new_usertype<Script>("Script",
			sol::constructors<Script()>(),
			"name", &Script::name
			);

		//trying to pass a string to trigger the animation
		lua.new_usertype<State>("State",
			sol::constructors<State()>(),
			"state", &State::name,
			"counter", &State::counter,
			"charge", &State::charge
			);
		/*
		lua.new_usertype<PushBox>("PushBox",
			sol::constructors<PushBox()>(),
			
			"pushW", &PushBox::width,
			"pushH", &PushBox::height,
			"pushX", &PushBox::x,
			"pushY", &PushBox::y,
			"color", &PushBox::color
			);
			*/
		lua.new_usertype<Shapes>("Shape",
			sol::constructors<Shapes()>(),
			"color", &Shapes::color,
			"scale", &Shapes::scale
			);
		lua.new_usertype<HitBox>("HitBox",
			sol::constructors<HitBox()>(),
			//"p", &PushBox::p,
			//"angle", &PushBox::angle,
			//"width", &HitBox::x,
			//"height", &HitBox::y,
			"hit", &HitBox::hit
			//"from", &HitBox::from
			//"hit", &PushBox::hit
			);
		lua.set_function("GetState", [&](EntityID id) -> State& {
			return engine->ecs->Get<State>(id);
			});
		lua.set_function("GetCollision", [&](EntityID id) -> Collision& {
			return engine->ecs->Get<Collision>(id);
			});
		lua.set_function("GetPosition", [&](EntityID id) -> Position& {
			return engine->ecs->Get<Position>(id);

			});
		lua.set_function("GetPhysics", [&](EntityID id) -> Physics& {
			return engine->ecs->Get<Physics>(id);
			});
		lua.set_function("GetHealth", [&](EntityID id) -> Health& {
			return engine->ecs->Get<Health>(id);

			});
		
		lua.set_function("GetSprite", [&](EntityID id) -> Sprite& {
			return engine->ecs->Get<Sprite>(id);

			});
		lua.set_function("GetShape", [&](EntityID id) -> Shapes& {
			return engine->ecs->Get<Shapes>(id);

			});
		lua.set_function("GetUnusedId", [&]() ->EntityID{
			return engine->ecs->GetUnusedID();

			});
		lua.set_function("GetScript", [&](EntityID id) -> Script& {
			return engine->ecs->Get<Script>(id);

			});
		lua.set_function("GetFlag", [&](EntityID id) -> Flag& {
			return engine->ecs->Get<Flag>(id);

			});
		lua.set_function("GetIsFlipped", [&](EntityID id) -> isFlipped& {
			return engine->ecs->Get<isFlipped>(id);

			});
		/*lua.set_function("GetPushBox", [&](EntityID id) -> PushBox& {
			return engine->ecs->Get<PushBox>(id);

			});
			*/
		lua.set_function("GetHitBox", [&](EntityID id) -> HitBox& {
			return engine->ecs->Get<HitBox>(id);

			});
		LoadScript("player1.lua");
		LoadScript("player2.lua");
		LoadScript("aiRbow.lua");
		LoadScript("fireBall.lua");
		LoadScript("ai1.lua");
		

        //scripts["test1"](10, 5,1);
		scripts["MasterScript.lua"]();

	}
	
	bool InputManager::KeyIsPressed() {
		//KeyIsDown(65);
		//int width, height;
		//glfwGetFramebufferSize(window, &(width), &(height));

		//std::cout << width << " " << height << "\n";
		int r;
		for (int i = A; i != undefined; i++) {
			switch (i) {
			case A:
				r = glfwGetKey(window, GLFW_KEY_A);
				//std::cout << "Egnine " << r << "\n";
				if (r) {
					std::cout << "A" << "\n";


				}
				break;
			case I:
				r = glfwGetKey(window, GLFW_KEY_I);
				//std::cout << "Egnine " << r << "\n";
				if (r) {
					std::cout << "I" << "\n";


				}
				break;
			case P:
				r = glfwGetKey(window, GLFW_KEY_P);
				//std::cout << "Egnine " << r << "\n";
				if (r) {
					std::cout << "P" << "\n";


				}
				break;
			case S:
				r = glfwGetKey(window, GLFW_KEY_S);
				if (r) {
					std::cout << "S" << "\n";
					//engine->PlaySound("complete");

				}
				break;
			case D:
				r = glfwGetKey(window, GLFW_KEY_D);
				if (r) {
					std::cout << "D" << "\n";
					//engine->PlaySound("complete");

				}
				break;
			case W:
				r = glfwGetKey(window, GLFW_KEY_W);
				if (r) {
					std::cout << "W" << "\n";
					//engine->PlaySound("complete");

				}
				break;
			case E:
				r = glfwGetKey(window, GLFW_KEY_E);
				if (r) {
					std::cout << "E" << "\n";
					//engine->PlaySound("complete");

				}
				break;
			case R:
				r = glfwGetKey(window, GLFW_KEY_R);
				if (r) {
					std::cout << "R" << "\n";
					//engine->PlaySound("complete");

				}
				break;
			case UP:
				r = glfwGetKey(window, GLFW_KEY_UP);
				if (r) {
					std::cout << "UP" << "\n";
					//engine->PlaySound("complete");

				}
				break;
			case LEFT:
				r = glfwGetKey(window, GLFW_KEY_LEFT);
				if (r) {
					std::cout << "LEFT" << "\n";
					//engine->PlaySound("complete");

				}
				break;
			case RIGHT:
				r = glfwGetKey(window, GLFW_KEY_RIGHT);
				if (r) {
					std::cout << "RIGHT" << "\n";
					//engine->PlaySound("complete");

				}
				break;
			case DOWN:
				r = glfwGetKey(window, GLFW_KEY_DOWN);
				if (r) {
					std::cout << "DOWN" << "\n";
					//engine->PlaySound("complete");

				}
				break;
			case RSHIFT:
				r = glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT);
				if (r) {
					std::cout << "RSHIFT" << "\n";
					//engine->PlaySound("complete");

				}
				break;
			case SLASH:
				r = glfwGetKey(window, GLFW_KEY_SLASH);
				if (r) {
					std::cout << "SLASH" << "\n";
					//engine->PlaySound("complete");

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
