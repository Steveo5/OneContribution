#pragma once
#include <SFML\Graphics.hpp>
#include "TileMap.h"

class World : public sf::Drawable
{
public:
	World();
	~World();

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	TileMap* m_tileMap;
	sf::Texture m_texture;
};

