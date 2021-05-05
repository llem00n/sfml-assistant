#include <algorithm>
#include <cstdlib>

#include "hello_module.hpp"
#include "ai.hpp"


bool HelloModule::call() {
	std::vector<std::string> messages = {
		"Hey!",
		"Hello!",
		"Nice to meet you!",
	};

	ai.sendMessage(messages[rand() % messages.size()]);

	return true;
}

bool HelloModule::isSuitable(const std::vector<std::string>& lastMessage) {
	if (lastMessage.size() >= 1) {
		std::string command = lastMessage[0];
		std::transform(command.begin(), command.end(), command.begin(),
					   [] (unsigned char c) { return std::tolower(c); });

		if (command == "hello" || command == "hey" || command == "hi")
			return true;
	}

	return false;
}