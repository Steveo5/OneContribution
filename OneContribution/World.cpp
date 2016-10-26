#include "World.h"

World::World(sf::Vector2i tileSize, sf::Vector2f worldBounds)
{

	//m_tileMap = new TileMap(m_texture, 1, 1, 32.f, 2008.f);
	m_tileSize = tileSize;
	m_worldBounds = worldBounds;
}


World::~World()
{
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//sm_tileMap->draw(target, states);
	for (int i = 0; i < m_entities.size(); i++)
	{
		target.draw(*m_entities[i]);
	}
}

void World::tick()
{
	//Entity logic tick
	for (int i = 0; i < m_entities.size(); i++)
	{
		m_entities[i]->tick();
	}
}

void World::update()
{
	//Update the entities
	for (int i = 0; i < m_entities.size(); i++)
	{
		m_entities[i]->update();
	}
}

Entity* World::spawnEntity(EntityType type, sf::Vector2f location)
{
	Entity* ent = new Entity(type, location);
	std::cout << "Entity spawned at x " << location.x << " y " << location.y << std::endl;
	m_entities.push_back(ent);
	return ent;
}

std::vector<Entity*> World::getEntities()
{
	return m_entities;
}

sf::Vector2i World::getTile(sf::Vector2i location)
{
	return sf::Vector2i(location.x - (location.x % m_tileSize.x), location.y - (location.y % m_tileSize.y));
}

const int World::getTileCount()
{
	return ((m_worldBounds.x / m_tileSize.x) * (m_worldBounds.y / m_tileSize.y));
}
sf::Vector2f World::getBounds()
{
	return m_worldBounds;
}
