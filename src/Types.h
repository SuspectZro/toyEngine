#pragma once

#include<string>
#include <functional>
#include<chrono>
#include<thread>
#include<cmath>

namespace data {
	typedef double real;
	typedef std::string string;
	typedef std::function<void()> UpdateCallback;
	typedef std::chrono::duration<real> intervals;
	//typedef std::vector ;

}