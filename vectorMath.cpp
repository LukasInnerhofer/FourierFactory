#include "vectorMath.h"

sf::Vector2f operator+(const sf::Vector2f &v1, const sf::Vector2f &v2)
{
	return sf::Vector2f(v1.x + v2.x, v1.y + v2.y);
}

namespace vectorMath
{
	sf::Vector2f toVector2f(const sf::Vector2i &vector)
	{
		return sf::Vector2f(static_cast<float>(vector.x), static_cast<float>(vector.y));
	}
}