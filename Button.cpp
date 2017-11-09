#include "Button.h"

namespace sf
{
	sf::Vector2f Button::getPosition()
	{
		return shape.getPosition();
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

	void Button::setTextPadding(const sf::Vector2f &padding)
	{
		text.setPosition(shape.getPosition() + padding);
	}

	bool Button::getMouseOver()
	{
		return mouseOver;
	}

	Button::Button()
	{
		fillColor = sf::Color::White;
		fillColorMouseOver = sf::Color(200, 200, 200, 255);
		borderColor = sf::Color::White;
		font.loadFromFile("D:/C++/fonts/arial.ttf");
		text = sf::Text("", font);
		text.setFillColor(sf::Color::Black);
	}

	Button::Button(const sf::Vector2f &position, const sf::Vector2f &size, const std::string &text = "") : Button()
	{
		shape.setPosition(position);
		shape.setSize(size);
		this->text.setString(text);
	}

	Button::Button(const sf::Vector2f &position, const sf::Vector2f &size, const std::string &text, const unsigned int &textSize, const sf::Vector2f &textPadding) :
		Button(position, size, text)
	{
		this->text.setCharacterSize(textSize);
		this->text.setPosition(shape.getPosition() + textPadding);
	}

	void Button::update(const sf::RenderWindow &window)
	{
		if (sf::Mouse::getPosition(window).x > shape.getPosition().x && sf::Mouse::getPosition(window).x < shape.getPosition().x + shape.getSize().x &&
			sf::Mouse::getPosition(window).y > shape.getPosition().y && sf::Mouse::getPosition(window).y < shape.getPosition().y + shape.getSize().y)
		{
			if (!mouseOver)
			{
				mouseOver = true;
				shape.setFillColor(fillColorMouseOver);
				shape.setOutlineColor(borderColor);
			}
		}
		else
		{
			if (mouseOver)
			{
				mouseOver = false;
				shape.setFillColor(fillColor);
				shape.setOutlineColor(borderColor);
			}
		}
	}

	void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		target.draw(shape, states);
		target.draw(text, states);
	}
}