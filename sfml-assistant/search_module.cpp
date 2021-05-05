#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <algorithm>
#include <cstdlib>
#include <Windows.h>
#include <shellapi.h>
#include <iomanip>
#include <sstream>

#include "search_module.hpp"
#include "ai.hpp"


bool SearchModule::call() {
	std::vector<std::string> lastMessage = ai.getMessages()[ai.getMessages().size() - 1];
	std::string searchQuery;

	auto word = lastMessage.begin() + 1;
	if (lastMessage[1] == "for")
		word++;
	for (; word != lastMessage.end(); word++)
		searchQuery += (*word + ' ');
	searchQuery.pop_back();
	searchQuery = to_url(searchQuery);
	searchQuery = "https://google.com/search?q=" + searchQuery;

	ai.sendMessage("Searching...");

	std::wstring wSearchQuery(searchQuery.begin(), searchQuery.end());
	ShellExecute(nullptr, nullptr, wSearchQuery.c_str(), nullptr, nullptr, SW_RESTORE);

	return true;
}

bool SearchModule::isSuitable(const std::vector<std::string>& lastMessage) {
	if (lastMessage.size() >= 1) {
		std::string command;
		for (const auto& word : lastMessage)
			command += word + ' ';
		std::transform(command.begin(), command.end(), command.begin(),
					   [] (unsigned char c) { return std::tolower(c); });

		if (!command.find("search for") || !command.find("look for"))
			return true;
	}

	return false;
}

std::string SearchModule::to_url(const std::string& str) {
	std::stringstream url;

	for (const auto& x : str)
		url << "%" << std::hex << static_cast<uint16_t>(x);

	return url.str();
}