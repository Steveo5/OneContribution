#include <SFML\System\Vector2.hpp>

namespace Math
{
	template <class T>
	float inline magnitude(const sf::Vector2<T> &vec)
	{
		return std::sqrt(vec.x * vec.x + vec.y * vec.y);
	};


	template <class T>
	sf::Vector2<T> normalize(const sf::Vector2<T> &vec)
	{
		float m = magnitude(vec);

		return vec / m;
	};

	template <class T>
	float dot(const sf::Vector2<T> &vec1, const sf::Vector2<T> &vec2)
	{
		return (vec1.x * vec2.x) + (vec1.y * vec2.y);
	};
}