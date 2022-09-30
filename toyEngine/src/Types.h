#pragma once

#include<string>
#include <functional>
#include<chrono>
#include<thread>
#include<cmath>
#include "glm/glm.hpp"

namespace data {
	typedef double real;
	typedef std::string string;
	typedef std::function<void()> UpdateCallback;
	typedef std::chrono::duration<real> intervals;
	typedef glm::vec2 vec2;
	typedef glm::vec3 vec3;
	typedef glm::vec4 vec4;
	//typedef std::vector ;

}