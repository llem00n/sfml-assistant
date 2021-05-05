#pragma once
#ifndef OPEN_MODULE_HPP
#define OPEN_MODULE_HPP

#include <vector>
#include <string>
#include <filesystem>

#include "module.hpp"


class OpenModule : public Module {
public:
						OpenModule(AI& ai) : Module(ai), state(State::FirstCall) {};

	virtual bool		call();
	static bool			isSuitable(const std::vector<std::string>& lastMessage);


private:
	std::vector<std::filesystem::directory_entry>
						searchForAppPath(const std::string& appName);
	size_t				searchForWord(const std::string& src, const std::string& substr);

	void				launchCommand(const std::vector<std::string>& lastMessage);
	void				openCommand(const std::vector<std::string>& string);
	void				openUrl(const std::string& url);
	void				applyChoice(const std::vector<std::string>& lastMessage);

	void				launchApp(const std::string& path);


private:
	enum class State { FirstCall, Finished, WaitingForChoice };
	
private:
	State state;

	std::vector<std::filesystem::directory_entry> appsList;
};

#endif // !OPEN_MODULE_HPP
