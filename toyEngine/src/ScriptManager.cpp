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

bool ScriptManager::LoadScript(const std::string& relativePathToScript) {
    // Get the directory of the executable.
    std::string executableDir = std::filesystem::path(__argv[0]).parent_path().string();

    // Move up four directories to get to the "src" directory.
    for (int i = 0; i < 4; ++i) {
        executableDir = std::filesystem::path(executableDir).parent_path().string();
    }

    // Construct the full path to the script based on the "src" directory.
    std::string fullScriptPath = executableDir + "\\" + "src\\" + relativePathToScript;

    scripts.insert({ relativePathToScript, lua.load_file(fullScriptPath) });

    if (scripts[relativePathToScript].valid()) {
        std::cout << relativePathToScript << " loaded successfully\n";
        return true;
    }

    scripts.erase(relativePathToScript);
    std::cout << "Loading script " << relativePathToScript << " failed\n";
    return false;
}





