#pragma once
#ifndef CHATBOX_HPP
#define CHATBOX_HPP

#include <memory>
#include <vector>
#include <functional>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>

#include <TGUI/Widgets/ScrollablePanel.hpp>

#include "message.hpp"


class Chatbox {
public:
	enum class Sender { Assistant, User };

	
public:
					Chatbox();

	void			init(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Font> font);
	void			setOffsetWidgetPtr(tgui::ScrollablePanel::Ptr ptr);

	void			pushBack(Sender sender, const std::string& text);

	void			draw();

private:
	std::shared_ptr<sf::RenderWindow>		window;
	std::shared_ptr<sf::Font>				font;

	std::vector<Message>					messages;

	sf::View								view;
	tgui::ScrollablePanel::Ptr				optionsPanelPtr;
};

#endif // !CHATBOX_HPP
