#pragma once
#ifndef AI_HPP
#define AI_HPP

#include <memory>
#include <string>
#include <vector>

#include "module.hpp"


class GUI;

class AI {
public:
				AI();

	void		init(std::shared_ptr<GUI> gui);
	void		start();

	void		sendMessage(const std::string& text);

	void		processMessage(const std::string& text);

	std::vector<std::vector<std::string>>&
				getMessages();

	void		sendButtonToPanel(const std::string& text);
	void		clearPanel();

	void		finish();
	bool		isFinished() const;


private:
	void		saveMessage(const std::string& text);
	void		applyModule();
	void		selectModule();


private:
	std::shared_ptr<GUI>						gui;
	std::unique_ptr<Module>						currentModule;

	std::vector<std::vector<std::string>>		messages;

	bool										finished;
};

#endif // !AI_HPP
