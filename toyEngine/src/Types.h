#pragma once

#include<string>
#include <functional>
#include<chrono>
#include<thread>
#include<cmath>
#include "glm/glm.hpp"
#include <algorithm>

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
	struct Sprite { string image; real size; };
	struct Health { real percent; };
	struct Script { string name; };
	struct Flag { real flag; real charge;};
	struct isFlipped { bool isFlipped; };
	struct State { string name; int counter; bool charge; };
	struct Physics : public vec2 { real gravity; real friction; real maxGravity; };
	struct Shapes { vec3 scale; vec3 color; float alpha; };
	struct Collision { real width; real height; bool isStatic; };
	//box struct
	//struct PushBox: public vec4{ real x; real y; real width; real height; };
	//struct PushBox { real x; real y; real width; real height; vec4 color; };
	struct HitBoxData { bool hit; real width; real height; real offsetX; real offsetY; };
	struct HitBox { std::vector<HitBoxData> hitboxes; };
	
	
}