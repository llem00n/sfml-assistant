#pragma once
#ifndef HELLO_MODULE_HPP
#define HELLO_MODULE_HPP

#include <vector>
#include <string>

#include "module.hpp"


class HelloModule : public Module {
public:
	HelloModule(AI& ai) : Module(ai) {};

	virtual bool		call();
	static bool			isSuitable(const std::vector<std::string>& lastMessage);
};

#endif // !HELLO_MODULE_HPP
