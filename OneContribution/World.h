#pragma once
#include <SFML\Graphics.hpp>
#include "Entity.h"
#include <iostream>
#include <list>

class World : public sf::Drawable
{
public:
	World();
	void setWorld(sf::Vector2i tileSize, sf::Vector2i worldBounds);
	//World::World(sf::Vector2i tileSize, sf::Vector2f worldBounds);
	~World();
	
	Entity* spawnEntity(EntityType type, sf::Vector2f location);
	std::vector<Entity*> getEntities();
	sf::Vector2i getTile(sf::Vector2i location);

	const int getTileCount();

	sf::Vector2i getBounds();

	int getWidth();

	int getRows();

	int getHeight();

	int getColumns();

	std::list <sf::Vector2i> getNeighbours(sf::Vector2i);


	void tick();
	void update();

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Texture m_texture;

	std::vector<Entity*> m_entities;

	sf::Vector2i m_tileSize;
	sf::Vector2i m_worldBounds;
};

