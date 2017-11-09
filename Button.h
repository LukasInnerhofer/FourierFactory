#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#include "vectorMath.h"

namespace sf
{
	class Button : public sf::Drawable
	{
	private:
		sf::RectangleShape shape;
		sf::Color fillColor, borderColor;
		sf::Color fillColorMouseOver;
		sf::Font font;
		sf::Text text;
		bool mouseOver;

		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	public:
		sf::Vector2f getPosition();

		void setBackgroundColor(const sf::Color &fillColor);
		void setBackgroundColorMouseOver(const sf::Color &fillColorMouseOver);
		void setBorderColor(const sf::Color &borderColor);
		void setTextColor(const sf::Color &textColor);
		void setTextSize(const unsigned int &textSize);
		void setText(const std::string &text);
		void setTextPadding(const sf::Vector2f &padding);

		bool getMouseOver();

		Button();
		Button(const sf::Vector2f &position, const sf::Vector2f &size, const std::string &text);
		Button(const sf::Vector2f &position, const sf::Vector2f &size, const std::string &text, const unsigned int &textSize, const sf::Vector2f &textPadding);

		void update(const sf::RenderWindow &window);
		void draw(sf::RenderWindow &window);
	};
}

#endif // BUTTON_H