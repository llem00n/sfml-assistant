#pragma once
#ifndef ASSISTANT_HPP
#define ASSISTANT_HPP

#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window/Event.hpp>

#include "gui.hpp"
#include "ai.hpp"


class Assistant {
public:
					Assistant();

	void			init(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Font> font);
	void			start();

	void			handleEvent(const sf::Event& event);

	void			draw();

	bool			isFinished() const;

private:
	std::shared_ptr<GUI>		gui;
	std::shared_ptr<AI>			ai;
};

#endif // !ASSISTANT_HPP
