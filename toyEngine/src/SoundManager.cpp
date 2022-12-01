#include "SoundManager.h"


//SoundManager::SoundManager() {};

void SoundManager::Startup() {
	soloud.init();
string path = "assets/audio/goStraight.mp3";
std::cout << path;
string complete = "complete";
LoadSound(complete, path);
}
void SoundManager::Shutdown() {
	soloud.deinit();
}

void SoundManager::LoadSound(const string& name, const string& path) {
	SoLoud::Wav w;

	sounds.insert({ {name,w} });
	sounds[name].load(path.c_str());
}
void SoundManager::play(const string name) {
	soloud.play(sounds[name]);
}