#pragma once
#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>

#include "assistant.hpp"


class Application {
public:
						Application();

	void				run();

	
private:
	void				init();


private:
	std::shared_ptr<sf::RenderWindow>	window;
	std::shared_ptr<sf::Font>			font;

	Assistant							assistant;
};

#endif // !APPLICATION_HPP
