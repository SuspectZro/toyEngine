#pragma once
#include <iostream>
#include <ostream>
#include "Types.h"
#include "soloud.h"
#include "soloud_wav.h"

#include <unordered_map>

using namespace data;

class SoundManager {
public:
	void play(string);
	void Shutdown();
	void Startup();
	void LoadSound(const string& name, const string& path);
	SoundManager() {};
	SoLoud::Soloud soloud;
	std::unordered_map< string, SoLoud::Wav > sounds;


};