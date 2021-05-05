#include "chatbox.hpp"

#include <iostream>


Chatbox::Chatbox()
	: optionsPanelPtr(nullptr)
{}


void Chatbox::init(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Font> font) {
	this->window = window;
	view = this->window->getDefaultView();
	this->font = font;
}

void Chatbox::setOffsetWidgetPtr(tgui::ScrollablePanel::Ptr ptr) {
	optionsPanelPtr = ptr;
}

void Chatbox::pushBack(Chatbox::Sender sender, const std::string& text) {
	float_t lastMessageBottom = 0;
	if (messages.size()) {
		sf::FloatRect messageBounds = messages[messages.size() - 1].getGlobalBounds();
		lastMessageBottom = messageBounds.top + messageBounds.height;
	}
	Message::Side side = sender == Sender::Assistant ? Message::Side::Left : Message::Side::Right;
	Message message;
	message.create(window, font, text, 0.6f, 10.f,
					17u, sf::Color::Black, sf::Color(220, 220, 220),
					lastMessageBottom, 10.f, side, 10.f);

	messages.push_back(message);
}

void Chatbox::draw() {
	if (window != nullptr && font != nullptr &&  messages.size()) {
		float_t bottomOffset = optionsPanelPtr == nullptr ? 
			0.f : 
			window->getSize().y - (optionsPanelPtr->getAbsolutePosition().y + optionsPanelPtr->getContentOffset().y);

		auto defaultView = window->getView();

		auto lastMessageBounds = messages[messages.size() - 1].getGlobalBounds();
		auto viewBottom = lastMessageBounds.top + lastMessageBounds.height + 20 + bottomOffset;
		sf::Vector2f viewCenter(view.getCenter().x, viewBottom - (view.getSize().y / 2));

		if (view.getCenter().y > viewCenter.y && messages.size() <= 1)
			view.setCenter(viewCenter);
		else if (view.getCenter().y > viewCenter.y)
			view.move(0, -15.f);

		if (view.getCenter().y < viewCenter.y)
			view.move(0, 15.f);

		window->setView(view);
		for (auto& message : messages) {
			message.draw();
		}

		window->setView(defaultView);

		sf::RectangleShape offsetShape;
		offsetShape.setSize(sf::Vector2f(static_cast<float>(window->getSize().x), bottomOffset));
		offsetShape.setOrigin(0, bottomOffset);
		offsetShape.setFillColor(sf::Color::White);
		offsetShape.setPosition(0.f, static_cast<float>(window->getSize().y));
		window->draw(offsetShape);
	}
}