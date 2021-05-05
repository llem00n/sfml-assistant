#pragma once
#ifndef ASSISTANT_GUI_HPP
#define ASSISTANT_GUI_HPP

#include <memory>
#include <functional>

#include <TGUI/Core.hpp>
#include <TGUI/Backends/SFML.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>

#include "chatbox.hpp"


class AI;

class GUI {
public:
							GUI();
							~GUI();

	void					init(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Font> font);
	void					build(AI& ai);

	void					draw();
	void					handleEvent(const sf::Event& event);

	void					newMessage(Chatbox::Sender sender, const std::string& text);

	tgui::GuiSFML&			getTgUI();

	void					addButtonToPanel(const std::string& text);
	void					clearPanel();

private:
	tgui::GuiSFML			tgUI;
	Chatbox					chatbox;

	std::function<void(tgui::GuiSFML& tgUI, Chatbox& chatbox, AI& ai)>
							onEnterPressed;
	AI*						aiPtr;

	unsigned				buttonsCounter;
};

#endif // !ASSISTANT_GUI
