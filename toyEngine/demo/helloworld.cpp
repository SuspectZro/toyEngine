#include <iostream>
#include "Engine.h"

//using namespace toyEngine;

int main(int argc, const char* argv[]) {
    //std::cout << "Hello, World!\n";
    std::function<void()> game([] {});
    Engine* e = new Engine();
    //std::cout << "before startup\n";
    e->Startup();
    //std::cout << "before loop\n";
    e->RunGameLoop(game);

    delete e;
    
    return 0;
}