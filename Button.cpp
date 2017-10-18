#include "Button.h"

sf::Vector2i Button::getPosition()
{
	return position;
}

void Button::setBackgroundColor(const sf::Color &fillColor)
{
	this->fillColor = fillColor;
}

void Button::setBackgroundColorMouseOver(const sf::Color &fillColorMouseOver)
{
	this->fillColorMouseOver = fillColorMouseOver;
}

void Button::setBorderColor(const sf::Color &borderColor)
{
	this->borderColor = borderColor;
}

void Button::setTextColor(const sf::Color &textColor)
{
	text.setFillColor(textColor);
}

void Button::setTextSize(const unsigned int &textSize)
{
	text.setCharacterSize(textSize);
}

void Button::setText(const std::string &text)
{
	this->text.setString(text);
}

Button::Button()
{
	fillColor = sf::Color(255, 255, 255, 255);
	fillColorMouseOver = sf::Color(200, 200, 200, 255);
	borderColor = sf::Color(0, 0, 0, 255);
	font.loadFromFile("D:/C++/fonts/arial.ttf");
	text = sf::Text("", font);
	text.setFillColor(sf::Color(0, 0, 0, 255));
	textPadding = sf::Vector2i(0, 0);
}

Button::Button(const sf::Vector2i &position, const sf::Vector2i &size, const std::string &text = "") : Button()
{
	this->position = position;
	this->size = size;
	this->text = sf::Text(text, font);
	this->text.setPosition(vectorMath::toVector2f(this->position + textPadding));
}

void Button::update(const sf::RenderWindow &window)
{
	if (sf::Mouse::getPosition(window).x > position.x && sf::Mouse::getPosition(window).x < position.x + size.x &&
		sf::Mouse::getPosition(window).y > position.y && sf::Mouse::getPosition(window).y < position.y + size.y)
	{
		mouseOver = true;
	}
	else
	{
		mouseOver = false;
	}
}

void Button::draw(sf::RenderWindow &window)
{
	sf::RectangleShape rectangle;
	rectangle.setSize(vectorMath::toVector2f(size));
	rectangle.setPosition(vectorMath::toVector2f(position));
	rectangle.setFillColor(mouseOver ? fillColorMouseOver : fillColor);
	rectangle.setOutlineColor(borderColor);

	window.draw(rectangle);
	window.draw(text);
}