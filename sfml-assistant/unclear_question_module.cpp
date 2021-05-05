#include "unclear_question_module.hpp"
#include "ai.hpp"


bool UnclearQuestionModule::call() {
	ai.sendMessage("Sorry, I can't understand what do you mean");

	return true;
}

bool UnclearQuestionModule::isSuitable() {
	return true;
}