#include <algorithm>
#include <cstdlib>

#include "exit_module.hpp"
#include "ai.hpp"


bool ExitModule::call() {
	ai.sendMessage("Bye!");
	ai.finish();

	return true;
}

bool ExitModule::isSuitable(const std::vector<std::string>& lastMessage) {
	if (lastMessage.size() >= 1) {
		std::string command;
		for (const auto& word : lastMessage)
			command += word;
		std::transform(command.begin(), command.end(), command.begin(),
					   [] (unsigned char c) { return std::tolower(c); });

		if (command == "bye" 
			|| command == "goodbye" 
			|| command == "quit" 
			|| command == "exit" 
			|| command == "i'mdone" 
			|| command == "that'sall"
		)
			return true;
	}

	return false;
}