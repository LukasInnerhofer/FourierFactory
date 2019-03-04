#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#include "vector_math.h"

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
		inline void setBackgroundColor(const sf::Color &fillColor) { this->fillColor = fillColor; }
		inline void setBackgroundColorMouseOver(const sf::Color &fillColorMouseOver) { this->fillColorMouseOver = fillColorMouseOver; }
		inline void setBorderColor(const sf::Color &borderColor) { this->borderColor = borderColor; }
		inline void setTextColor(const sf::Color &textColor) { text.setFillColor(textColor); }
		inline void setTextSize(const unsigned int &textSize) { text.setCharacterSize(textSize); }
		inline void setText(const std::string &text) { this->text.setString(text); }
		inline void setTextPadding(const sf::Vector2f &padding) { text.setPosition(shape.getPosition() + padding); }

		inline bool getMouseOver() const { return mouseOver; }

		Button();
		Button(const sf::Vector2f &position, const sf::Vector2f &size, const std::string &text);
		Button(const sf::Vector2f &position, const sf::Vector2f &size, const std::string &text, const unsigned int &textSize, const sf::Vector2f &textPadding);

		void update(const sf::RenderWindow &window);
	};
}

#endif // BUTTON_H