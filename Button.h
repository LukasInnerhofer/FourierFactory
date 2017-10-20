#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#include "vectorMath.h"

class Button
{
private:
	sf::Vector2i position, size;
	sf::Color fillColor, borderColor;
	sf::Color fillColorMouseOver;
	sf::Font font;
	sf::Text text;
	sf::Vector2i textPadding;
	bool mouseOver;

public:
	sf::Vector2i getPosition();

	void setBackgroundColor(const sf::Color &fillColor);
	void setBackgroundColorMouseOver(const sf::Color &fillColorMouseOver);
	void setBorderColor(const sf::Color &borderColor);
	void setTextColor(const sf::Color &textColor);
	void setTextSize(const unsigned int &textSize);
	void setText(const std::string &text);
	void setTextPadding(const sf::Vector2i &padding);

	bool getMouseOver();

	Button();
	Button(const sf::Vector2i &position, const sf::Vector2i &size, const std::string &text);
	Button(const sf::Vector2i &position, const sf::Vector2i &size, const std::string &text, const unsigned int &textSize, const sf::Vector2i &textPadding);

	void update(const sf::RenderWindow &window);
	void draw(sf::RenderWindow &window);
};

#endif // BUTTON_H