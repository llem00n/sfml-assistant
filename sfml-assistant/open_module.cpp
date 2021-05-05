#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "open_module.hpp"
#include "ai.hpp"

#include <Windows.h>
#include <shellapi.h>
#include <algorithm>
#include <filesystem>


bool OpenModule::call() {
	std::vector<std::string> lastMessage = ai.getMessages()[ai.getMessages().size() - 1];

	if (state == State::FirstCall) {
		std::string command = lastMessage[0];
		std::transform(command.begin(), command.end(), command.begin(),
					   [] (unsigned char c) { return std::tolower(c); });

		if (command == "launch" || command == "start")
			launchCommand(lastMessage);
		if (command == "open")
			openCommand(lastMessage);
	} else if (state == State::WaitingForChoice) {
		applyChoice(lastMessage);
	}

	return state == State::Finished;
}

bool OpenModule::isSuitable(const std::vector<std::string>& lastMessage) {
	std::string command = lastMessage[0];
	std::transform(command.begin(), command.end(), command.begin(),
				   [] (unsigned char c) { return std::tolower(c); });

	if ((command == "open" || command == "launch" || command == "start") && lastMessage.size() > 1)
		return true;

	return false;
}

std::vector<std::filesystem::directory_entry> OpenModule::searchForAppPath(const std::string& orderedApp) {
	std::string appName = orderedApp + ' ';
	std::transform(appName.begin(), appName.end(), appName.begin(),
		[] (unsigned char c) { return std::tolower(c); });
	std::vector<std::string> splitted;
	std::string tempStr;
	for (int x = 0; x < appName.size(); x++)
		if (std::isspace(appName[x]) && tempStr.size() > 0) {
			splitted.push_back(tempStr);
			tempStr.clear();
		} else {
			tempStr.push_back(appName[x]);
		}


	char* var = std::getenv("PROGRAMDATA");
	std::string programData = var == nullptr ? "" : std::string(var);
	char* _var = std::getenv("APPDATA");
	std::string appData = _var == nullptr ? "" : std::string(_var);

	std::string startMenuPath1 = programData + "\\Microsoft\\Windows\\Start Menu\\Programs\\";
	std::string startMenuPath2 = appData	 + "\\Microsoft\\Windows\\Start Menu\\Programs\\";
	std::string startMenuPath3 = "C:\\Windows\\";


	std::vector<std::filesystem::directory_entry> files;
	for (auto& file : std::filesystem::recursive_directory_iterator(startMenuPath1)) {
		if (!file.is_directory()) {
			files.push_back(file);
		}
	}

	for (auto& file : std::filesystem::recursive_directory_iterator(startMenuPath2)) {
		if (!file.is_directory()) {
			files.push_back(file);
		}
	}

	for (auto& file : std::filesystem::directory_iterator(startMenuPath3)) {
		if (!file.is_directory()) {
			files.push_back(file);
		}
	}

	for (const auto& word : splitted) {
		auto newEnd = std::remove_if(files.begin(), files.end(),
			[=] (std::filesystem::directory_entry& file) {
				std::string fileName = file.path().stem().string();
				std::transform(fileName.begin(), fileName.end(), fileName.begin(), 
					[] (unsigned char c) {return std::tolower(c); });
				return (searchForWord(fileName, word) == std::string::npos);
			});

		files.erase(newEnd, files.end());
	}

	std::vector<std::string> alreadyIncluded;
	auto newEnd = std::remove_if(files.begin(), files.end(),
		[&] (std::filesystem::directory_entry& file) {
			auto found = std::find(alreadyIncluded.begin(), alreadyIncluded.end(), file.path().stem().string());
			if (found == alreadyIncluded.end()) {
				alreadyIncluded.push_back(file.path().stem().string());
				return false;
			} else {
				return true;
			}
		});
	files.erase(newEnd, files.end());

	return files;
}

size_t OpenModule::searchForWord(const std::string& _src, const std::string& substr) {
	std::string src = _src;
	size_t erasedCounter = 0;
	bool found = false;

	if (src == substr)
		return 0;
	while (src.find(substr) != std::string::npos) {
		size_t searchResult = src.find(substr);

		if (searchResult != 0) {
			if (!std::isdigit(src[searchResult - 1]) && !std::isalpha(src[searchResult - 1]))
				found = true;
			else
				found = false;
		}

		size_t nextCharacter = searchResult + substr.size();
		if (nextCharacter < src.size()) {
			if (!std::isdigit(src[nextCharacter]) && !std::isalpha(src[nextCharacter]))
				found = true;
			else
				found = false;
		}

		if (found)
			return searchResult + erasedCounter;

		src.erase(src.begin(), src.begin() + nextCharacter);
		erasedCounter += nextCharacter;
	}

	return std::string::npos;
}

void OpenModule::launchCommand(const std::vector<std::string>& lastMessage) {
	std::string appName;
	for (auto word = lastMessage.begin() + 1; word != lastMessage.end(); word++)
		appName += *word + ' ';
	appName.pop_back();

	appsList = searchForAppPath(appName);
	if (appsList.size() == 0) {
		ai.sendMessage("Sorry, I can't find any applications that match your request");
	} else {

		if (appsList.size() == 1) {
			ai.sendMessage("Opening");

			launchApp(appsList[0].path().string());

			state = State::Finished;
		} else {
			ai.sendMessage("There are several apps that match your search query.\n\nPlease, select one of them from the panel below");

			for (const auto& file : appsList)
				ai.sendButtonToPanel(file.path().stem().string());

			state = State::WaitingForChoice;
		}
	}
}

void OpenModule::openCommand(const std::vector<std::string>& lastMessage) {
	std::string secondParameter = lastMessage[1];
	std::transform(secondParameter.begin(), secondParameter.end(), secondParameter.begin(),
				   [] (unsigned char c) { return std::tolower(c); });

	if (lastMessage.size() > 2 && secondParameter == "url") {
		std::string url;
		for (auto it = lastMessage.begin() + 2; it != lastMessage.end(); it++)
			url += *it;

		openUrl(url);

		ai.sendMessage("Sure");

	} else if (lastMessage.size() > 1) {
		std::string url;
		for (auto it = lastMessage.begin() + 1; it != lastMessage.end(); it++)
			url += *it;

		if (!url.find("https://") || !url.find("http://") || !url.find("www.")) {
			openUrl(url);

			ai.sendMessage("Sure");
		} else {
			launchCommand(lastMessage);
		}
	}
}

void OpenModule::openUrl(const std::string& _url) {
	std::string url = _url;
	if (url.find("http://") && url.find("https://") && url.find("www."))
		url = "www." + url;

	std::wstring wurl(url.begin(), url.end());

	ShellExecute(nullptr, nullptr, wurl.c_str(), nullptr, nullptr, SW_RESTORE);
}

void OpenModule::applyChoice(const std::vector<std::string>& lastMessage) {
	std::string appName;
	for (auto& word : lastMessage)
		appName += (word + ' ');
	appName.pop_back();

	if (appName == "cancel") {
		ai.sendMessage("Canceling");
		ai.clearPanel();

		state = State::Finished;
		return;
	}

	auto result = std::find_if(appsList.begin(), appsList.end(), 
		[=] (const std::filesystem::directory_entry& file) { 
			return !(searchForWord(file.path().stem().string(), appName) == std::string::npos);
		});

	if (result == appsList.end()) {
		ai.sendMessage("Please, select one option from the list below");
	} else {
		ai.clearPanel();
		ai.sendMessage("Opening");

		launchApp(result->path().string());

		state = State::Finished;
	}
}

void OpenModule::launchApp(const std::string& path) {
	std::wstring wFilePath(path.begin(), path.end());
	ShellExecute(nullptr, nullptr, wFilePath.c_str(), nullptr, nullptr, SW_RESTORE);
}