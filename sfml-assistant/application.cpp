#include <iostream>
#include <cstdlib>
#include <ctime>

#include <SFML/Window/Event.hpp>

#include "application.hpp"


Application::Application() 
	: window(new sf::RenderWindow())
	, font(new sf::Font())
{}

void Application::init() {
	window->create(sf::VideoMode(325u, 550u), "SF::ASSISTANT", sf::Style::Titlebar | sf::Style::Close);
	window->setFramerateLimit(60);
	if (!font->loadFromFile("C:/Windows/Fonts/arial.ttf"))
		std::cout << "Error loading font: arial.ttf\n";

	assistant.init(window, font);

	srand(static_cast<uint32_t>(time(nullptr)));
}

void Application::run() {
	init();
	assistant.start();

	while (window->isOpen() && !assistant.isFinished()) {
		sf::Event event;
		while (window->pollEvent(event)) {
			assistant.handleEvent(event);

			if (event.type == sf::Event::Closed)
				window->close();
		}

		window->clear(sf::Color::White);
		assistant.draw();
		window->display();
	}
}