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

std::vector<Entity*>& World::getEntities()
{
	return m_entities;
}

sf::Vector2i World::getTile(sf::Vector2i location)
{
	std::cout << "tileSize: " << m_tileSize.x << ", " << m_tileSize.y << std::endl;
	sf::Vector2i temp = sf::Vector2i(location.x - (location.x % m_tileSize.x), location.y - (location.y % m_tileSize.y));
	sf::Vector2i tempTileSize(static_cast<sf::Vector2i>(Game::instance()->getMapLoader()->GetTileSize()));
	std::cout << tempTileSize.x << ", " << tempTileSize.y << std::endl;
	temp.x /= tempTileSize.x;
	temp.y /= tempTileSize.y;
	std::cout << "getTile(): " << temp.x << ", " << temp.y << std::endl;
	return temp;
}

sf::Vector2i World::getTilePos(sf::Vector2i location)
{
	sf::Vector2i temp;
	temp.x = location.x * Game::instance()->getMapLoader()->GetTileSize().x;
	temp.x = location.y * Game::instance()->getMapLoader()->GetTileSize().y;
	std::cout << "getTilePos(): " << temp.x << ", " << temp.y << std::endl;
	return temp;
	
}

const int World::getTileCount()
{
	int m_tileCountTemp = ((m_worldBounds.x / m_tileSize.x) * (m_worldBounds.y / m_tileSize.y));
	std::cout << "tileCount: " << m_tileCountTemp << std::endl;
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

std::list<sf::Vector2i> World::getNeighbours(sf::Vector2i i)
{
	std::list<sf::Vector2i> neighbours;
	//neighbours.push_back(sf::Vector2i(getTile(i).x - m_tileSize.x, getTile(i).y - m_tileSize.y));//up-left
	neighbours.push_back(sf::Vector2i(getTile(i).x, getTile(i).y - m_tileSize.y));//up
	//neighbours.push_back(sf::Vector2i(getTile(i).x + m_tileSize.x, getTile(i).y - m_tileSize.y));//up-right
	neighbours.push_back(sf::Vector2i(getTile(i).x - m_tileSize.x, getTile(i).y));//left
	neighbours.push_back(sf::Vector2i(getTile(i).x + m_tileSize.x, getTile(i).y));//right
	//neighbours.push_back(sf::Vector2i(getTile(i).x - m_tileSize.x, getTile(i).y + m_tileSize.y));//down-left
	neighbours.push_back(sf::Vector2i(getTile(i).x, getTile(i).y + m_tileSize.y));//down
	//neighbours.push_back(sf::Vector2i(getTile(i).x + m_tileSize.x, getTile(i).y + m_tileSize.y));//down-right
	return neighbours;
}
