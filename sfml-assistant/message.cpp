#include <vector>
#include <iostream>

#include "message.hpp"


Message::Message()
	: text()
	, bgShape()
{}

void Message::create(
	std::shared_ptr<sf::RenderWindow> window,
	std::shared_ptr<sf::Font> font,
	const std::string& string,
	float_t maxWidth,
	float_t padding,
	uint32_t characterSize,
	sf::Color textColor,
	sf::Color bgColor,
	float_t lastMessageBottom,
	float_t marginTop,
	Side alignmentSide,
	float_t marginX

) {
	this->window = window;
	this->font = font;
	if (window != nullptr && font != nullptr) {
		text.setCharacterSize(characterSize);
		text.setFont(*font);

		// Splitting the string
		std::vector<std::string> words;
		std::string str = string + ' ';
		maxWidth = maxWidth * window->getSize().x;
		while (str.find(" ") != std::string::npos) {
			auto pos = str.find(" ");
			auto substr = str.substr(0, pos);
			if (substr.size() > 0)
				words.push_back(substr);
			str.erase(0, pos + 1);
		}

		// Creating the message sprite
		std::string textStr;
		for (auto& word : words) {
			text.setString(textStr + word);
			if (text.getGlobalBounds().width < maxWidth)
				textStr += word;
			else {
				text.setString(textStr + '\n' + word);
				if (text.getGlobalBounds().width > maxWidth) {
					std::string wordPart;
					for (auto& c : word) {
						text.setString(textStr + wordPart + c);
						if (text.getGlobalBounds().width > maxWidth) {
							wordPart += {'\n', c};
						} else
							wordPart += c;
					}
					textStr += wordPart;
				} else {
					textStr += '\n';
					textStr += word;
				}
			}
			text.setString(textStr + ' ');
			if (text.getGlobalBounds().width > maxWidth)
				textStr += '\n';
			else
				textStr += ' ';
		}
		textStr.pop_back();
		text.setString(textStr);

		text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
		text.setPosition(0.f, 0.f);

		bgShape.setSize({
			text.getLocalBounds().left + text.getLocalBounds().width + (padding * 2),
			text.getLocalBounds().top + text.getLocalBounds().height + (padding * 2)
						});
		bgShape.setOrigin(
			bgShape.getLocalBounds().width / 2 - text.getLocalBounds().left,
			bgShape.getLocalBounds().height / 2 - text.getLocalBounds().top
		);
		bgShape.setPosition(0.f, 0.f);

		text.setFillColor(textColor);
		bgShape.setFillColor(bgColor);

		// Calculating position
		sf::Vector2f pos;
		pos.y = lastMessageBottom + marginTop + (bgShape.getGlobalBounds().height / 2);
		if (alignmentSide == Side::Left) {
			pos.x = marginX + (bgShape.getGlobalBounds().width / 2);
		} else if (alignmentSide == Side::Right) {
			pos.x = window->getSize().x - marginX - (bgShape.getGlobalBounds().width / 2);
		}

		text.setPosition(pos);
		bgShape.setPosition(pos);
	}
}

void Message::draw() {
	if (window != nullptr && font != nullptr) {
		window->draw(bgShape);
		window->draw(text);
	}
}

sf::FloatRect Message::getGlobalBounds() const {
	return bgShape.getGlobalBounds();
}