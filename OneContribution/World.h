#pragma once
#include <SFML\Graphics.hpp>
#include "Entity.h"
#include <iostream>
#include <list>
#include <unordered_map>

class World : public sf::Drawable
{
public:
	World();
	void setWorld(sf::Vector2i tileSize, sf::Vector2i worldBounds);
	//World::World(sf::Vector2i tileSize, sf::Vector2f worldBounds);
	~World();
	
	Entity* spawnEntity(EntityType type, sf::Vector2f location);
	std::vector<Entity*>& getEntities();
	sf::Vector2i getTile(sf::Vector2i location);

	sf::Vector2i getTilePos(sf::Vector2i location);

	const int getTileCount();

	sf::Vector2i getBounds();

	int getWidth();

	int getRows();

	int getHeight();

	int getColumns();

	sf::Vector2i getTileSize();

	int VecToInt(sf::Vector2i v);

	sf::Vector2i IntToVec(int i);

	bool willCollide(sf::Vector2f position);

	int pnpoly(int npol, float x, float y);
	float * pVertY;
	float * pVertX;
	

	void tick();
	void update(sf::Time deltaTime);

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Texture m_texture;

	std::vector<Entity*> m_entities;

	sf::Vector2i m_tileSize;
	sf::Vector2i m_worldBounds;

	float vertX[4] = { 0, -3200, 0, 3200 };
	float vertY[4] = { 15, 1615, 3215, 1615 };
};

