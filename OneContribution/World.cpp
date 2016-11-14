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
	/*for (int i = 0; i < m_entities.size(); i++)
	{
		m_entities[i]->tick();
	}*/
	m_entities[1]->tick();
	m_entities[0]->tick();
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
	std::cout << "getTile(): " << location.x << ", " << location.y << std::endl;
	sf::Vector2i m_location = static_cast<sf::Vector2i>(location);
	//location.x -= getWidth();
	sf::Vector2i m_tileCoords = sf::Vector2i(m_location.x - (m_location.x % m_tileSize.x), m_location.y - (m_location.y % m_tileSize.y));
	//sf::Vector2i m_tileCoords = sf::Vector2i(m_location.x - (m_location.x % 64), m_location.y - (m_location.y %32));
	std::cout << "getTile(): tile coords: " << m_tileCoords.x << ", " << m_tileCoords.y << std::endl;
	return m_tileCoords;
}

sf::Vector2i World::getTilePos(sf::Vector2i location)
{
	sf::Vector2i temp;
	temp.x = (location.x * getTileSize().x) - 6400;
	temp.x = (location.y * getTileSize().y);
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
	std::cout << "World: " << getRows() << ", " << getColumns() << std::endl;
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

std::unordered_map<int, std::list<int>>* World::getGraph()
{
	return &graph;
}

void World::createGraph()
{
	for (int row = -3200; row < 3200; row+= 64)
	{
		for (int col = 0; col < 3200; col+=32)
		{
			int id = VecToInt(sf::Vector2i(row, col));

			if (!willCollide(sf::Vector2f(row, col)))
			{
				std::list <int> edges;

				if (!willCollide(sf::Vector2f(row - 64, col)))
				{
					edges.emplace_front(VecToInt(sf::Vector2i(row - 64, col)));
				}
				if (!willCollide(sf::Vector2f(row + 64, col)))
				{
					edges.emplace_front(VecToInt(sf::Vector2i(row + 64, col)));
				}
				if (!willCollide(sf::Vector2f(row, col - 32)))
				{
					edges.emplace_front(VecToInt(sf::Vector2i(row, col - 32)));
				}
				if (!willCollide(sf::Vector2f(row, col + 32)))
				{
					edges.emplace_front(VecToInt(sf::Vector2i(row, col + 32)));
				}

				graph[id] = edges;
			}
		}
	}
}
