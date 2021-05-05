#pragma once
#ifndef MODULE_HPP
#define MODULE_HPP


class AI;

class Module {
public:
						Module(AI& ai) : ai(ai) {};

	virtual bool		call() = 0;


protected:
	AI& ai;
};

#endif // !MODULE_HPP
