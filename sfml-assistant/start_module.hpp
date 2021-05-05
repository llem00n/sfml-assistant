#pragma once
#ifndef START_MODULE_HPP
#define START_MODULE_HPP

#include "module.hpp"


class StartModule : public Module {
public:
						StartModule(AI& ai) : Module(ai) {};

	virtual bool		call();
	static bool			isSuitable();
};

#endif // !START_MODULE_HPP
