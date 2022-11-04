#include "ScriptManager.h"
/*
#if graph
void ScriptManager::StartUp( GraphicsManager* graphics, EntityManager* ecs ) {
#elif ECS

void ScriptManager::StartUp(EntityManager* ecs, GraphicsManager* graphics) {
#else
void ScriptManager::StartUp(Engine* e){
#endif	
	*/

void ScriptManager::ShutDown() {

}

void ScriptManager::execute( const std::string name, EntityID id) {
	scripts[name](id);
	
}

bool ScriptManager::LoadScript(const std::string& name, const std::string& path) {

	scripts.insert({ name, lua.load_file(path) });
	if (scripts[name].valid() ) {
		std::cout << name << "\n";
		return true;
	}
	
	scripts.erase(name);
std::cout << "loading script " << path << " failed\n";
	return false;
	
	//return true;
}
