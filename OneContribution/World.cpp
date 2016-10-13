#include "World.h"

World::World()
{

	//m_tileMap = new TileMap(m_texture, 1, 1, 32.f, 2008.f);
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
