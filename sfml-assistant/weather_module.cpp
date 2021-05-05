#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <algorithm>
#include <cstdlib>
#include <Windows.h>
#include <shellapi.h>
#include <iomanip>
#include <sstream>

#include "weather_module.hpp"
#include "ai.hpp"


bool WeatherModule::call() {
	std::vector<std::string> lastMessage = ai.getMessages()[ai.getMessages().size() - 1];
	std::string messageText;
	for (const auto& word : lastMessage)
		messageText += word;

	std::wstring url = L"www.weather.com/weather/today";

	ai.sendMessage("Weather for today...");

	ShellExecute(nullptr, nullptr, url.c_str(), nullptr, nullptr, SW_RESTORE);

	return true;
}

bool WeatherModule::isSuitable(const std::vector<std::string>& lastMessage) {
	if (lastMessage.size() >= 1) {
		std::string command;
		for (const auto& word : lastMessage)
			command += word + ' ';
		std::transform(command.begin(), command.end(), command.begin(),
					   [] (unsigned char c) { return std::tolower(c); });

		if (command.find("weather") != std::string::npos)
			return true;
	}

	return false;
}