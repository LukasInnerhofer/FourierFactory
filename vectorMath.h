#ifndef VECTOR_MATH_H
#define VECTOR_MATH_H

#include <SFML/Graphics.hpp>

sf::Vector2f operator+(const sf::Vector2f &v1, const sf::Vector2f &v2);

namespace vectorMath
{
	sf::Vector2f toVector2f(const sf::Vector2i &vector);
}

#endif // VECTOR_MATH_H