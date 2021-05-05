#pragma once
#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <memory>
#include <string>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>


class Message {
public:
	enum class Side { Right, Left };


public:
					Message();

	void			create(
						std::shared_ptr<sf::RenderWindow> window,
						std::shared_ptr<sf::Font> font,
						const std::string& str, 
						float_t maxWidth, 
						float_t padding,
						uint32_t characterSize, 
						sf::Color textColor, 
						sf::Color bgColor,
						float_t lastMessageBottom,
						float_t marginTop,
						Side alignmentSide,
						float_t marginX
					);

	void			draw();

	sf::FloatRect	getGlobalBounds() const;


private:
	std::shared_ptr<sf::RenderWindow>		window;
	std::shared_ptr<sf::Font>				font;

	sf::Text								text;
	sf::RectangleShape						bgShape;
};

#endif // !MESSAGE_HPP