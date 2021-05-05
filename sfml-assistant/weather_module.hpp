#pragma once
#ifndef WEATHER_MODULE_HPP
#define WEATHER_MODULE_HPP

#include <vector>
#include <string>

#include "module.hpp"


class WeatherModule : public Module {
public:
	WeatherModule(AI& ai) : Module(ai) {};

	virtual bool		call();
	static bool			isSuitable(const std::vector<std::string>& lastMessage);
};

#endif // !WEATHER_MODULE_HPP
