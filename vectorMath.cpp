#include "vectorMath.h"

sf::Vector2f operator+(const sf::Vector2f &v1, const sf::Vector2f &v2)
{
	return sf::Vector2f(v1.x + v2.x, v1.y + v2.y);
}

sf::Vector2f operator-(const sf::Vector2f &v1, const sf::Vector2f &v2)
{
	return sf::Vector2f(v1.x - v2.x, v1.y - v2.y);
}

namespace vectorMath
{
	sf::Vector2f toVector2f(const sf::Vector2i &vector)
	{
		return sf::Vector2f(static_cast<float>(vector.x), static_cast<float>(vector.y));
	}

	float magnitude(const sf::Vector2f &vector)
	{
		return std::sqrt(std::pow(vector.x, 2) + std::pow(vector.y, 2));
	}

	float angle(const sf::Vector2f &vector)
	{
		if (vector.y / vector.x > 0)	// Q1 or Q3
		{
			if (vector.x > 0)			// Q1
			{
				return std::atan(vector.y / vector.x);
			}
			else						// Q3
			{
				return std::atan(vector.y / vector.x) + PI;
			}
		}
		else							// Q2 or Q4
		{
			if (vector.x < 0)			// Q2
			{
				return std::atan(vector.y / vector.x) + PI;
			}
			else						// Q4
			{
				return std::atan(vector.y / vector.x) + 2 * PI;
			}
		}
	}

	sf::Vector2f rotate(const sf::Vector2f &vector, const float &deltaAngle)
	{
		return sf::Vector2f(magnitude(vector) * std::cos(angle(vector) + deltaAngle), magnitude(vector) * std::sin(angle(vector) + deltaAngle));
	}
}