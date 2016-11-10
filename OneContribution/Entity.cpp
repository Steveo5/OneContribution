#include "Entity.h"
#include "Animation.hpp"
#include "Game.h"

#include <unordered_set>
#include <queue>

Animation m_animation;

Entity::Entity()
{

}
Entity::Entity(EntityType entityType, sf::Vector2f location)
{
	m_maxHealth = 100;
	//m_rectangle.setOrigin(m_rectangle.getSize().x / 2, m_rectangle.getSize().y / 2);
	m_entityType = entityType;
	m_health = 70;
	m_visible = true;
	m_isCharacterSprite = 0;
	//m_rectangle.setPosition(location);
	//m_rectangle.setFillColor(sf::Color::Red);
	//m_rectangle.setSize(sf::Vector2f(100.f, 100.f));
	m_path = new Path();

	//m_sprite stuff here
	m_sprite.setPosition(location);
	if (!m_characterSprite.loadFromFile("sprite.png"))
	{
		std::cout << "Error loading resource sprite.png"
			<< std::endl;
	}
	m_sprite.setTextureRect(sf::IntRect(30, 50, 65, 95));
	m_sprite.setTexture(m_characterSprite);
	//m_sprite stuff ends


	m_hpBar = new HealthBar();
	m_hpBar->setWidth(100);
	m_hpBar->setHealth(m_health);
	m_hpBar->setPosition(location + sf::Vector2f(50, 50));
	Game::instance()->getUi()->addComponent(m_hpBar);
	m_lastPos = m_sprite.getPosition();
}



int Entity::VecToInt(sf::Vector2i v)
{
	return (v.x * Game::instance()->getWorld().getColumns()) + v.y;
}
sf::Vector2i Entity::IntToVec(int i)//height and width should be tile based not world based
{
	std::cout << "World: " << Game::instance()->getWorld().getRows() << ", " << Game::instance()->getWorld().getColumns() << std::endl;
	int row = i / Game::instance()->getWorld().getColumns();
	int col = i % Game::instance()->getWorld().getColumns();

	return sf::Vector2i(row, col);

}

void Entity::BFS()
{
	std::cout << "BFS" << std::endl;
	//std::cout << "Dest: " << destination.x << ", " << destination.y << std::endl;
	std::cout << "mapSize: " << Game::instance()->getMapLoader()->GetMapSize().x << Game::instance()->getMapLoader()->GetMapSize().y << std::endl;
	std::cout << "tileSize: " << Game::instance()->getMapLoader()->GetTileSize().x << Game::instance()->getMapLoader()->GetTileSize().y << std::endl;
	std::cout << "spritePos: " << m_sprite.getPosition().x << ", " << m_sprite.getPosition().y << std::endl;

	sf::Vector2i startingPos = Game::instance()->getWorld().getTile(static_cast<sf::Vector2i>(m_sprite.getPosition()));//starting point
	//	ending point is m_target
	//m_sprite.setPosition(static_cast<sf::Vector2f>(Game::instance()->getWorld().getTilePos(m_target)));//test movement

	const int tileCount = Game::instance()->getWorld().getTileCount();
	std::cout << "start: " << startingPos.x << ", " << startingPos.y <<
		" target:" << m_target.x << ", " << m_target.y <<
		" TileCount: " << tileCount << std::endl;
	std::unordered_set<int> visited;

	std::queue<int> queue;

	int root = VecToInt(startingPos);
	std::cout << "root: " << root << std::endl;

	queue.push(root); // enqueue the root node
	std::cout << "queue.back: " << queue.back() << std::endl;
	visited.insert(root);

	std::list<int> path;

	int parents[10000];

	parents[root] = -1;//-1 = start point

	while (!queue.empty())
	{
		std::cout << "queue is not empty" << std::endl;
		int node = queue.front();
		queue.pop();

		path.push_back(node);

		if (node == VecToInt(m_target))
		{
			int path = 0;

			int parent = node;

			int prev = -1;//prev is a trail when tracing path, 
						  //so once path is tracked back to start, prev will be the next move
			while (parent != root)
			{
				prev = parent;
				parent = parents[parent];

			}

			if (prev == -1)//already at destination
			{
				//next location = root
				m_sprite.setPosition(static_cast<sf::Vector2f>(Game::instance()->getWorld().getTilePos(IntToVec(root))));
				std::cout << "SpritePos post change: "<< m_sprite.getPosition().x << ", " << m_sprite.getPosition().y << std::endl;
				std::cout << "root: " << root << std::endl;

			}
			else
			{
				//next location = prev
				m_sprite.setPosition(static_cast<sf::Vector2f>(Game::instance()->getWorld().getTilePos(IntToVec(prev))));
				std::cout << "SpritePos post change: " << m_sprite.getPosition().x << ", " << m_sprite.getPosition().y << std::endl;
				std::cout << "prev: " << prev << std::endl;
			}
		}


		std::list <sf::Vector2i> temp = Game::instance()->getWorld().getNeighbours(IntToVec(node)), edgesVec;

		for (std::list<sf::Vector2i>::iterator it = temp.begin(); it != temp.end(); ++it)
		{
			//if (!willCollide(*it))//if tile is valid location(no collisions)
			//edgesVec.push_back(*it);
		}
		std::list <int> edges;
		while (!edges.empty())
		{
			edges.push_back(VecToInt(edgesVec.front()));
			edgesVec.pop_front();
		}

		for (std::list<int>::iterator it = edges.begin(); it != edges.end(); it++)
		{
			int nde = *it;

			if (visited.count(nde) == 0)
			{
				visited.insert(nde);
				queue.push(nde);

				parents[nde] = node;//chld data = parent index
			}
		}
	}




}

sf::Clock pathTimer;
void Entity::tick()
{
	if (pathTimer.getElapsedTime().asSeconds() > 1)
	{
		pathTimer.restart();
		if (m_path->getNextTile() != NULL)
		{
			std::cout << "Next tile = " << m_path->getNextTile()->x << " " << m_path->getNextTile()->y << std::endl;
			m_sprite.setPosition(*m_path->getNextTile());
			m_path->setCurrentTile(m_path->getCurrentTileNumber() + 1);
		}
		BFS();
	}
	m_hpBar->setVisible(m_visible);
	m_hpBar->setHealth(m_health);

	//BFS();//start BFS on each tick

	if (isDead())
	{
		setVisible(false);
		return;
	}

	//Check if they are colliding and stop them
	bool collision;
	for (auto layer = Game::instance()->getMapLoader()->GetLayers().begin(); layer != Game::instance()->getMapLoader()->GetLayers().end(); ++layer)
	{
		if (layer->name == "Collision")
		{
			for (auto object = layer->objects.begin(); object != layer->objects.end(); ++object)
			{
				collision = object->Contains(m_sprite.getPosition());

				if (collision) return;
			}
		}
	}

	//m_sprite.move(sf::Vector2f(0.0, 0.8));

	m_hpBar->setPosition(sf::Vector2f(m_sprite.getPosition().x, m_sprite.getPosition().y - 30));

	//Update the entities m_facing property
	if (m_lastPos != m_sprite.getPosition())
	{
		if (m_lastPos.x > m_sprite.getPosition().x)
		{
			m_facing = Direction::RIGHT;
		}
		else if (m_lastPos.x < m_sprite.getPosition().x)
		{
			m_facing = Direction::LEFT;
		}
		else if (m_lastPos.y > m_sprite.getPosition().y)
		{
			m_facing = Direction::UP;
		}
		else if (m_lastPos.y < m_sprite.getPosition().y)
		{
			m_facing = Direction::DOWN;
		}
		else
		{
			m_facing = Direction::NONE;
		}
	}
}

bool Entity::isHitting(sf::Vector2f position)
{
	return m_sprite.getGlobalBounds().contains(position);
}

void Entity::update()
{
	updateSprite();
}

//Load correct sprite sheet
void Entity::setSpriteSheet()
{
	if (!m_isCharacterSprite)
	{
		if (m_entityType == KNIGHT)
		{
			if (!m_characterSprite.loadFromFile("KNIGHT.png"))
			{
				std::cout << "Error loading resource sprite.png"
					<< std::endl;
			}
			m_sprite.setTexture(m_characterSprite);
			m_isCharacterSprite = true;
		}
		else if (m_entityType == ENEMY)
		{
			if (!m_characterSprite.loadFromFile("ENEMY.png"))
			{
				std::cout << "Error loading resource sprite.png"
					<< std::endl;
			}
			m_sprite.setTexture(m_characterSprite);
			m_isCharacterSprite = true;
		}
	}
}

void Entity::updateSprite()
{
	m_animation.clearFrames();

	for (int i = 0; i < m_curFrames; i++)
	{
		m_animation.addFrame(
			sf::IntRect(m_curStart.x, m_curStart.y, m_frameSize.x, m_frameSize.y)
		);
		m_curStart.x += m_frameSize.x;
	}
}

void Entity::setHealth(int health)
{
	m_health = health;
}

int Entity::getHealth()
{
	return m_health;
}

bool Entity::willCollide(sf::Vector2f position)
{
	bool collision;
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

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_visible)
	{
		target.draw(m_sprite);
	}

}

bool Entity::isDead()
{
	return m_health < 1;
}

bool Entity::isControllable()
{
	return m_controllable;
}

void Entity::setTarget(sf::Vector2i t)
{
	std::cout << "setTarget(): " << t.x << ", " << t.y << std::endl;
	m_target = t;
}

void Entity::setControllable(bool control)
{
	m_controllable = control;
}

bool Entity::isVisible()
{
	return m_visible;
}

void Entity::setVisible(bool visible)
{
	m_visible = visible;
}

/* Get the entities current direction (UP, LEFT, DOWN, RIGHT, NONE) */
Direction Entity::getFacing()
{
	return m_facing;
}

sf::Vector2f Entity::getSpritePosition()
{
	return m_sprite.getPosition();
}

void Entity::setName(std::string name)
{
	m_name = name;
}

std::string Entity::getName()
{
	return m_name;
}

Entity::~Entity()
{
	//delete this;
}

Path* Entity::getPath()
{
	return m_path;
}

void Entity::setPath(Path* newPath)
{
	m_path = newPath;
}

sf::Vector2f* Path::getPreviousTile()
{
	if (m_currentTile - 1 < 0)
	{
		return NULL;
	}
	else
	{
		return &m_tiles[m_currentTile - 1];
	}
}

sf::Vector2f* Path::getNextTile()
{
	if (m_currentTile == -1 || m_currentTile + 1 > m_tiles.size() - 1)
	{
		return NULL;
	}
	else
	{
		return &m_tiles[m_currentTile + 1];
	}
}

void Entity::startPathing()
{
	resetPathing();
}

void Entity::resetPathing()
{
	m_path->setCurrentTile(0);
}

void Entity::stopPathing()
{
	m_path->setCurrentTile(-1);
}

bool Path::isPaused()
{
	return m_currentTile != NULL;
}
bool Path::isStopped()
{
	return m_currentTile == NULL;
}

void Path::setCurrentTile(int index)
{
	m_currentTile = index;
}

sf::Vector2f* Path::getCurrentTile()
{
	if (m_currentTile > m_tiles.size())
	{
		return NULL;
	}
	else
	{
		return &m_tiles[m_currentTile];
	}
}

std::vector<sf::Vector2f>* Path::getTiles()
{
	return &m_tiles;
}
void Path::setTiles(std::vector<sf::Vector2f> tiles)
{
	m_tiles = tiles;
}
void Path::addTile(sf::Vector2f tile)
{
	m_tiles.push_back(tile);
}

int Path::getCurrentTileNumber()
{
	return m_currentTile;
}

void Path::removeTile(int index)
{
	/*
	if (m_tiles->size() > index)
	{
		m_tiles->erase(std::remove(m_tiles->begin(), m_tiles->end(), index), m_tiles->end());
	}
	*/
}