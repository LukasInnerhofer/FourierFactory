#ifndef VECTOR_MATH_H
#define VECTOR_MATH_H

#include <SFML/Graphics.hpp>
#include <cmath>

#define PI (std::atan(1) * 4)

sf::Vector2f operator+(const sf::Vector2f &v1, const sf::Vector2f &v2);
sf::Vector2f operator-(const sf::Vector2f &v1, const sf::Vector2f &v2);

namespace vectorMath
{
	float magnitude(const sf::Vector2f &vector);
	float angle(const sf::Vector2f &vector);
}

#endif // VECTOR_MATH_H