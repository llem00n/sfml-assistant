#pragma once
#ifndef UNCLEAR_QUESTION_MODULE_HPP
#define UNCLEAR_QUESTION_MODULE_HPP

#include "module.hpp"


class UnclearQuestionModule : public Module {
public:
						UnclearQuestionModule(AI& ai) : Module(ai) {};

	virtual bool		call();
	static bool			isSuitable();
};

#endif // !UNCLEAR_QUESTION_MODULE_HPP
