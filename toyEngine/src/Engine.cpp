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
		float targetFps = 60;
		intervals t(1. / targetFps);
		int numberOfTimes = 1;
		int counterFrame = 0;
		//int delay = 60
		std::chrono::steady_clock::time_point t0 = std::chrono::steady_clock::now();
		bool running = true;
		std::vector<GraphicsManager::Sprite> sprites;
		while (running) {
			counterFrame++;
			//delay--;
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
			
			
			//std::cout << "here" << "\n";
			

			ecs->ForEach<Sprite, Position>([&](EntityID id) {
				
				GraphicsManager::Sprite s;
				Position p = ecs->Get<Position>(id);
				Sprite   sp = ecs->Get<Sprite>(id);
				s.x = p.x;
				s.y = p.y;
				s.z = 0;
				//s.width = 50;
				//s.height = 50;
				s.name = sp.image;
				real scale = ecs->Get<Sprite>(id).size;
				s.scale = vec3(scale,scale, scale);
				sprites.push_back(s);
				});
			ecs->ForEach<Script>([&](EntityID id) {

				script->execute(ecs->Get<Script>(id).name, id);

				});


			ecs->ForEach<Gravity, Velocity>([&](EntityID id) {
				
				Gravity g = ecs->Get<Gravity>(id);

				ecs->Get<Velocity>(id).y += g.meters_per_second;
				
				});

			ecs->ForEach<Position, Velocity, PushBox>([&](EntityID id1) {
				
				ecs->ForEach<Position, Velocity, PushBox>([&](EntityID id2) {
					if (id2 <= id1) {
						return;
					}
					//center
					Position p1 = ecs->Get<Position>(id1);
					Position p2 = ecs->Get<Position>(id2);
					//scale
					vec2 s1 = ecs->Get<PushBox>(id1);
					vec2 s2 = ecs->Get<PushBox>(id2);
					real px = p1.x - p2.x;
					real py = p1.y - p2.y;
					//check x collision
					if (abs(px) < ((s1.x + s2.x)/2)) {
						ecs->Get<Velocity>(id1).x -= signbit(px);
						ecs->Get<Velocity>(id2).x += signbit(px);
						if (ecs->Get<Sprite>(id2).image == "fireBall") {
							//ecs->Get<HitBox>(id2).hit = true;
							//ecs->Get<HitBox>(id2).hit = 1;
							///ecs->Get<Position>(id2).x = ecs->Get<Position>(id1).x;
							std::cout << "id2" << "\n";
						}
						std::cout << "collision X " << "\n";
					}
					//check y collision
				//	if (abs(py) < ((s1.y + s2.y) / 2)) {
				//		ecs->Get<Velocity>(id1).y -= signbit(py);
				//		ecs->Get<Velocity>(id2).y += signbit(py);
				//		std::cout << "collision Y " << "\n";
				//	}
					});
				});
			ecs->ForEach<Position, Velocity>([&](EntityID id) {
				Velocity v = ecs->Get<Velocity>(id);
				//Position p = ecs->Get<Position>(id);

				ecs->Get<Position>(id).x += v.x;
				//std::cout << "v.x: " << v.x << "\n";
				//p.y += v.y;
				ecs->Get<Position>(id).y += v.y;
				});
			ecs->ForEach<State>([&](EntityID id) {
				ecs->ForEach<Sprite>([&](EntityID id2) {

					if (ecs->Get<State>(id).name == "FireBall") {
						//std::cout << "counter " << counter << "\n";
						//EntityID id3 = ecs->GetUnusedID();
						//ecs->Get<Sprite>(id3) = Sprite({ "fireBall",30.0 });
						//ecs->Get<Flag>(id3).flag = 0.0;
						//ecs->Get<Position>(id3).x = ecs->Get<Position>(id).x + 28;
						//ecs->Get<Position>(id3).y = ecs->Get<Position>(id).y;

						if (ecs->Get<Sprite>(id2).image == "fireBall" && ecs->Get<HitBox>(id2).hit == false) {

							if (ecs->Get<State>(id).counter < 20) {
								//EntityID id3 = ecs->GetUnusedID();
							//	ecs->Get<Sprite>(id3) = Sprite({ "fireBall",30.0 });
								//EntityID ID = id;
								//ecs->Get<Flag>(id3).flag = 0.0;
								ecs->Get<Position>(id2).x = ecs->Get<Position>(id).x + 28;
								ecs->Get<Position>(id2).y = ecs->Get<Position>(id).y;
								//ecs->Get<Velocity>(id2).x = 1;
								//ecs->Get<HitBox>(id2).from = id;
								//ecs->Get<Sprite>(id3) = ecs->Get<Sprite>(id2);
								//if (ecs->Get<HitBox>(id2).hit == "False") {
								//ecs->Get<Script>(id2).name = "fireBall";
								//}
							}
						
						}
					}

					});
				});
			ecs->ForEach<Script>([&](EntityID id) {
				ecs->ForEach<Script>([&](EntityID id2) {
					if (ecs->Get<Script>(id).name == "player1") {
						std::cout << "1\n";
						if (ecs->Get<Script>(id2).name == "ai1") {
							std::cout << "2\n";
							if (ecs->Get<State>(id).name == "Punch") {
								std::cout << "3\n";
								ecs->Get<State>(id2).name = "Crouching";
							}
							else{
								ecs->Get<State>(id2).name = "Idle";
							}
						}
					}
					});
				});

			graphics->Draw(sprites);

			//std::cout << sprites.size() << "\n";
			sprites.clear();
			//graphics->Draw();
			std::this_thread::sleep_for(t);
		}

	}
	void InputManager::Startup(Engine* e) {
		engine = e;
		window = e->graphics->getWindowPointer();
	}
	void ScriptManager::StartUp(Engine* e) {
        if (LoadScript("Master", "C:\\Users\\ruiz_\\toyEngine\\GitHub\\toyEngine\\toyEngine\\src\\MasterScript.lua")) {}
        else
            LoadScript("Master", "C:\\Users\\Alex\\CLionProjects\\toyEngine\\toyEngine\\src\\MasterScript.lua");



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
		lua.new_usertype<Velocity>("Velocity",
			sol::constructors<Velocity()>(),
			"vx", &Velocity::x,
			"vy", &Velocity::y
			);
		lua.new_usertype<Flag>("Flag",
			sol::constructors<Flag()>(),
			"f", &Flag::flag,
			"charge", &Flag::charge
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
		lua.new_usertype<Gravity>("Gravity",
			sol::constructors<Gravity()>(),
			"mps", &Gravity::meters_per_second
			);
		//trying to pass a string to trigger the animation
		lua.new_usertype<State>("State",
			sol::constructors<State()>(),
			"state", &State::name,
			"counter", &State::counter,
			"charge", &State::charge
			);
		lua.new_usertype<PushBox>("PushBox",
			sol::constructors<PushBox()>(),
				//"p", &PushBox::p,
				//"angle", &PushBox::angle,
				"width", &PushBox::x,
				"height", &PushBox::y
				//"hit", &PushBox::hit
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
		lua.set_function("GetPosition", [&](EntityID id) -> Position& {
			return engine->ecs->Get<Position>(id);

			});
		lua.set_function("GetVelocity", [&](EntityID id) -> Velocity& {
			return engine->ecs->Get<Velocity>(id);

			});
		lua.set_function("GetHealth", [&](EntityID id) -> Health& {
			return engine->ecs->Get<Health>(id);

			});
		lua.set_function("GetGravity", [&](EntityID id) -> Gravity& {
			return engine->ecs->Get<Gravity>(id);

			});
		lua.set_function("GetSprite", [&](EntityID id) -> Sprite& {
			return engine->ecs->Get<Sprite>(id);

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
		lua.set_function("GetPushBox", [&](EntityID id) -> PushBox& {
			return engine->ecs->Get<PushBox>(id);

			});
		lua.set_function("GetHitBox", [&](EntityID id) -> HitBox& {
			return engine->ecs->Get<HitBox>(id);

			});
        if (LoadScript("player1", "C:\\Users\\ruiz_\\toyEngine\\GitHub\\toyEngine\\toyEngine\\src\\player1.lua")){}
        else
            LoadScript("player1", "C:\\Users\\Alex\\CLionProjects\\toyEngine\\toyEngine\\src\\player1.lua");

        if (LoadScript("player2", "C:\\Users\\ruiz_\\toyEngine\\GitHub\\toyEngine\\toyEngine\\src\\player2.lua")){}
        else
            LoadScript("player2", "C:\\Users\\Alex\\CLionProjects\\toyEngine\\toyEngine\\src\\player2.lua");

        if (LoadScript("test1", "C:\\Users\\ruiz_\\toyEngine\\GitHub\\toyEngine\\toyEngine\\src\\aiRbow.lua")){}
        else
            LoadScript("test1", "C:\\Users\\Alex\\CLionProjects\\toyEngine\\toyEngine\\src\\aiRbow.lua");
		if (LoadScript("fireBall", "C:\\Users\\ruiz_\\toyEngine\\GitHub\\toyEngine\\toyEngine\\src\\fireBall.lua")) {}
		else
			LoadScript("fireBall", "C:\\Users\\Alex\\CLionProjects\\toyEngine\\toyEngine\\src\\fireBall.lua");
		if (LoadScript("ai1", "C:\\Users\\ruiz_\\toyEngine\\GitHub\\toyEngine\\toyEngine\\src\\ai1.lua")) {}
		else
			LoadScript("ai1", "C:\\Users\\Alex\\CLionProjects\\toyEngine\\toyEngine\\src\\ai1.lua");


        //scripts["test1"](10, 5,1);
		scripts["Master"]();

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
