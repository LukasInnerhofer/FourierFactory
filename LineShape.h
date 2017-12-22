#ifndef LINE_SHAPE_H
#define LINE_SHAPE_H

#include <SFML/Graphics.hpp>

#include "vectorMath.h"

namespace sf
{
	class LineShape : public sf::Drawable
	{
	private:
		sf::RectangleShape shape;

		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	public:
		LineShape();
		LineShape(const sf::Vector2f &point1, const sf::Vector2f &point2);
	};
}

#endif // LINE_SHAPE_H