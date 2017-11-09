#ifndef LINE_SHAPE_H
#define LINE_SHAPE_H

#include <SFML/Graphis.hpp>

namespace sf
{
	class LineShape : public sf::Drawable
	{
	private:
		sf::RectangleShape shape;

		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	};
}

#endif // LINE_SHAPE_H