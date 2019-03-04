#include "line_shape.h"
#include <iostream>

namespace sf
{
	LineShape::LineShape()
	{
		shape = sf::RectangleShape();
		shape.setFillColor(sf::Color::White);
	}

	LineShape::LineShape(const sf::Vector2f &point1, const sf::Vector2f &point2)
	{
		sf::Vector2f lineVector; 
		lineVector.x = point2.x - point1.x;
		lineVector.y = point1.y - point2.y;
		shape.setSize({ vectorMath::magnitude(lineVector), 1 });
		shape.setPosition(point1);
		shape.setRotation(vectorMath::angle(lineVector) * 180 / PI);
	}

	void LineShape::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		target.draw(shape, states);
	}
}