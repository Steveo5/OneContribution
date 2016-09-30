#pragma once
#include <SFML\Graphics.hpp>

class World : public sf::Drawable
{
public:
	World();
	~World();

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Texture m_texture;
};

