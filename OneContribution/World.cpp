#include "World.h"
#include <list>
#include "Game.h"

World::World()
{
	
}
void World::setWorld(sf::Vector2i tileSize, sf::Vector2i worldBounds)
{

	//m_tileMap = new TileMap(m_texture, 1, 1, 32.f, 2008.f);
	m_tileSize = tileSize;
	m_worldBounds = sf::Vector2i(worldBounds.x * tileSize.x, worldBounds.y * tileSize.y);
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

void World::update(sf::Time deltaTime)
{
	//Update the entities
	for (int i = 0; i < m_entities.size(); i++)
	{
		m_entities[i]->update(deltaTime);
	}
}

Entity* World::spawnEntity(EntityType type, sf::Vector2f location)
{
	Entity* ent = new Entity(type, location);
	std::cout << "Entity spawned at x " << location.x << " y " << location.y << std::endl;
	m_entities.push_back(ent);
	return ent;
}

std::vector<Entity*>& World::getEntities()
{
	return m_entities;
}

sf::Vector2i World::getTile(sf::Vector2i location)
{
	sf::Vector2i m_location = sf::Vector2i(location.x + 3168, location.y + 1584);
	sf::Vector2i m_tileCoords = sf::Vector2i(m_location.x - (m_location.x % (m_tileSize.x)), m_location.y - (m_location.y % (m_tileSize.y/2)));
	m_tileCoords.x -= 3200;
	m_tileCoords.y -= 1600;
	//fix alignment for isometric tile locations
	if (m_tileCoords.y / 16 % 2 == 0)
		m_tileCoords.x -= 32;
	if (m_tileCoords.x / 16 % 2 == 0)
		m_tileCoords.x += 32;
	
	return m_tileCoords;
}

sf::Vector2i World::getTilePos(sf::Vector2i location)
{
	sf::Vector2i temp;
	temp.x = (location.x * getTileSize().x) - 6400;
	temp.x = (location.y * getTileSize().y);
	return temp;
	
}

const int World::getTileCount()
{
	int m_tileCountTemp = ((m_worldBounds.x / m_tileSize.x) * (m_worldBounds.y / m_tileSize.y));
	return m_tileCountTemp;
}
sf::Vector2i World::getBounds()
{
	return m_worldBounds;
}

int World::getWidth()
{
	return m_worldBounds.x;
}

int World::getRows()
{
	return m_worldBounds.x / m_tileSize.x;
}

int World::getHeight()
{
	return m_worldBounds.y;
}

int World::getColumns()
{
	return m_worldBounds.y / m_tileSize.y;
}

sf::Vector2i World::getTileSize()
{
	return m_tileSize;
}

int World::VecToInt(sf::Vector2i v)
{
	return (v.x * getColumns()) + v.y;
}
sf::Vector2i World::IntToVec(int i)//height and width should be tile based not world based
{
	int row = i / getColumns();
	int col = i % getColumns();

	return sf::Vector2i(row, col);
}

bool World::willCollide(sf::Vector2f position)
{
	bool collision = false;
	for (auto layer = Game::instance()->getMapLoader()->GetLayers().begin(); layer != Game::instance()->getMapLoader()->GetLayers().end(); ++layer)
	{
		if (layer->name == "Collision")
		{
			for (auto object = layer->objects.begin(); object != layer->objects.end(); ++object)
			{
				collision = object->Contains(position);

				if (collision) return true;
			}
		}
	}
	return collision;
}

