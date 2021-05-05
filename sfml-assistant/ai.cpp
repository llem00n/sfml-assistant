#include "ai.hpp"
#include "gui.hpp"

#include "start_module.hpp"
#include "unclear_question_module.hpp"
#include "open_module.hpp"
#include "hello_module.hpp"
#include "exit_module.hpp"
#include "search_module.hpp"
#include "weather_module.hpp"

#include <algorithm>


AI::AI() 
	: currentModule(nullptr)
	, finished(false)
{}

void AI::init(std::shared_ptr<GUI> gui) {
	this->gui = gui;
}

void AI::start() {
	currentModule = std::unique_ptr<StartModule>(new StartModule(*this));
	applyModule();
}

void AI::sendMessage(const std::string& text) {
	gui->newMessage(Chatbox::Sender::Assistant, text);
}

void AI::processMessage(const std::string& text) {
	saveMessage(text);
	applyModule();
}

void AI::saveMessage(const std::string& text) {
	std::vector<std::string> words;
	std::string str = text + ' ';
	while (str.find(" ") != std::string::npos) {
		auto pos = str.find(" ");
		auto substr = str.substr(0, pos);
		if (substr.size() > 0)
			words.push_back(substr);
		str.erase(0, pos + 1);
	}

	messages.push_back(words);
}

void AI::applyModule() {
	if (currentModule == nullptr) {
		selectModule();
		gui->clearPanel();
	}

	if (currentModule->call()) {
		currentModule = nullptr;
		messages.clear();
	}
}

void AI::selectModule() {
	currentModule = std::unique_ptr<UnclearQuestionModule>(new UnclearQuestionModule(*this));

	std::vector<std::string> lastMessage = messages[messages.size() - 1];
	if (OpenModule::isSuitable(lastMessage))
		currentModule = std::unique_ptr<OpenModule>(new OpenModule(*this));

	if (HelloModule::isSuitable(lastMessage))
		currentModule = std::unique_ptr<HelloModule>(new HelloModule(*this));

	if (ExitModule::isSuitable(lastMessage))
		currentModule = std::unique_ptr<ExitModule>(new ExitModule(*this));

	if (SearchModule::isSuitable(lastMessage))
		currentModule = std::unique_ptr<SearchModule>(new SearchModule(*this));

	if (WeatherModule::isSuitable(lastMessage))
		currentModule = std::unique_ptr<WeatherModule>(new WeatherModule(*this));
}

std::vector<std::vector<std::string>>& AI::getMessages() {
	return messages;
}

void AI::sendButtonToPanel(const std::string& text) {
	gui->addButtonToPanel(text);
}

void AI::clearPanel() {
	gui->clearPanel();
}

void AI::finish() {
	finished = true;
}

bool AI::isFinished() const {
	return finished;
}