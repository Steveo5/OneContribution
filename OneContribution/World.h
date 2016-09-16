#pragma once
#include <SFML\Graphics.hpp>

class World : sf::Drawable
{
public:
	World();
	~World();

private:
	void Draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Texture m_texture;
};

