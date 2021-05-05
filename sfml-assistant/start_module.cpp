#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <ctime>
#include <cstdlib>
#include <iostream>
#include <string>

#include "start_module.hpp"
#include "ai.hpp"


bool StartModule::call() {
	// Getting current time
	time_t currentTime;
	tm* localTime;
	time(&currentTime);
	localTime = localtime(&currentTime);
	int hours = localTime == nullptr ? 0 : localTime->tm_hour;

	// Getting username
	char* var = std::getenv("USERNAME");
	std::string username = var == nullptr ? "" : std::string(var);

	if (hours <= 4 || hours >= 21)
		ai.sendMessage("Good night, " + username + '!');
	else if (hours <= 12)
		ai.sendMessage("Good morning, " + username + '!');
	else if (hours <= 17)
		ai.sendMessage("Good afternoon, " + username + '!');
	else if (hours < 21)
		ai.sendMessage("Good evening, " + username + '!');

	return true;
}

bool StartModule::isSuitable() {
	return false;
}