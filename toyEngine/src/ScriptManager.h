#pragma once
#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>
#include <unordered_map>
#include <string>
#include "Types.h"
#include "glm/glm.hpp"
#include "EntityManager.h"
#include "InputManager.h"
#include "GraphicsManager.h"
#define graph 0
#define ECS 0
class Engine;
class ScriptManager {
	sol::state lua;
	std::unordered_map< std::string, sol::load_result> scripts;
	Engine* engine;
	
public:
	ScriptManager(Engine* e) : engine() {}
#if graph

 

	void StartUp( GraphicsManager* graphics, EntityManager* ecs);
#elif ECS

	void StartUp(EntityManager* ecs, GraphicsManager* graphics);
#else
	void StartUp(Engine* e);
#endif
	void ShutDown();
	bool LoadScript(const std::string& name, const std::string& path);
	void execute(const std::string name, const EntityID id);
};

