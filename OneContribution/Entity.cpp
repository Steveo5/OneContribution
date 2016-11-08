#include "Entity.h"
#include "Animation.hpp"
#include "Game.h"

#include <unordered_set>
#include <queue>

HealthBar* Entity::m_hpBar;
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
	Game::getUi()->addComponent(m_hpBar);
	m_lastPos = m_sprite.getPosition();
}



int Entity::VecToInt(sf::Vector2i v)
{
	return (v.x * Game::getWorld().getColumns()) + v.y;
}
sf::Vector2i Entity::IntToVec(int i)//height and width should be tile based not world based
{
	std::cout << "World: " << Game::getWorld().getHeight() << ", " << Game::getWorld().getHeight() << std::endl;
	int row = i / Game::getWorld().getWidth();
	int col = i % Game::getWorld().getHeight();

	return sf::Vector2i(row, col);

}

void Entity::BFS(sf::Vector2i destination)
{
	std::cout << "BFS" << std::endl;
	std::cout << "Dest: " << destination.x << ", " << destination.y << std::endl;
	std::cout << "mapSize: " << Game::getMapLoader()->GetMapSize().x << Game::getMapLoader()->GetMapSize().y << std::endl;
	std::cout << "tileSize: " << Game::getMapLoader()->GetTileSize().x << Game::getMapLoader()->GetTileSize().y << std::endl;
	sf::Vector2i startingPos = Game::getWorld().getTile(static_cast<sf::Vector2i>(m_sprite.getPosition()));//starting point
	sf::Vector2i targetPos = destination;//ending point
	const int tileCount = 10000;
	std::cout << "start: " << startingPos.x << ", " << startingPos.y <<
		" target:" << targetPos.x << ", " << targetPos.y <<
		" TileCount: " << tileCount << std::endl;
	std::unordered_set<int> visited;

	std::queue<int> queue;

	int root = VecToInt(startingPos);

	queue.push(root); // enqueue the root node
	visited.insert(root);

	std::list<int> path;

	int parents[10000];

	parents[root] = -1;//-1 = start point

	while (!queue.empty())
	{
		int node = queue.front();
		queue.pop();

		path.push_back(node);

		if (node == VecToInt(destination))
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
				m_sprite.setPosition(static_cast<sf::Vector2f>(IntToVec(root)));
				std::cout << "root: " << root << std::endl;

			}
			else
			{
				//next location = prev
				sf::Vector2f fPrev = static_cast<sf::Vector2f>(IntToVec(prev));
				m_sprite.setPosition(fPrev);

				std::cout << "prev: " << prev << std::endl;
			}
		}


		std::list <sf::Vector2i> temp = Game::getWorld().getNeighbours(IntToVec(node)), edgesVec;

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

void Entity::tick()
{
	m_hpBar->setVisible(m_visible);
	m_hpBar->setHealth(m_health);

	if (isDead())
	{
		setVisible(false);
		return;
	}

	//Check if they are colliding and stop them
	bool collision;
	for (auto layer = Game::getMapLoader()->GetLayers().begin(); layer != Game::getMapLoader()->GetLayers().end(); ++layer)
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

	m_sprite.move(sf::Vector2f(0.0, 0.8));

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
	for (auto layer = Game::getMapLoader()->GetLayers().begin(); layer != Game::getMapLoader()->GetLayers().end(); ++layer)
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

/* Get the entities current direction (UP, LEFT, DOWN, RIGHT) */
Direction Entity::getFacing()
{
	return m_facing;
}

Entity::~Entity()
{
	//delete this;
}
