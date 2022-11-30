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
	//hit boxes
	
	//typedef std::vector ;
	//struct Position { real x, y; }; // or: 
	struct Position : public vec2 {};

	//struct Velocity { real x, y; }; // or: 
	struct Velocity : public vec2 {};
	struct Gravity { real meters_per_second; };
	struct Sprite { string image; real size; };
	struct Health { real percent; };
	struct Script { string name; };
	struct Flag { real flag; real charge;};
	struct State { string name; int counter; bool charge; };
	//box struct
	struct PushBox : public vec2{};
	struct HitBox { bool hit; };
		//Position p;
		//Position p.y;
		//real angle;
		// scale;
		//bool hit;

	//};
	
	//typedef std::vector<Box> hitBoxes;
}