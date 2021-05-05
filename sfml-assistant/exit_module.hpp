#pragma once
#ifndef EXIT_MODULE_HPP
#define EXIT_MODULE_HPP

#include <vector>
#include <string>

#include "module.hpp"


class ExitModule : public Module {
public:
	ExitModule(AI& ai) : Module(ai) {};

	virtual bool		call();
	static bool			isSuitable(const std::vector<std::string>& lastMessage);
};

#endif // !EXIT_MODULE_HPP
