#include "assistant.hpp"


Assistant::Assistant() 
	: gui(new GUI())
	, ai(new AI())
{}

void Assistant::init(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Font> font) {
	gui->init(window, font);

	ai->init(gui);

	gui->build(*ai);
}

void Assistant::handleEvent(const sf::Event& event) {
	gui->handleEvent(event);
}

void Assistant::draw() {
	gui->draw();
}

void Assistant::start() {
	ai->start();
}

bool Assistant::isFinished() const {
	return ai->isFinished();
}