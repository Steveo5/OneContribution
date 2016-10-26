#include "Entity.h"

#include "Game.h"

#include <unordered_set>
#include <queue>

HealthBar* Entity::m_hpBar;

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

void Entity::BFS(sf::Vector2i destination)
{
	sf::Vector2i startingPos = Game::getWorld().getTile(static_cast<sf::Vector2i>(m_sprite.getPosition()));//starting point
	sf::Vector2i targetPos = destination;//ending point
	const int tileCount = Game::getWorld().getTileCount();
	
	/*
	std::unordered_set<int> visited;

	std::queue<int> queue;

	int root = source;

	queue.push(root); // enqueue the root node
	visited.insert(root);

	std::list<int> path;

	const int parentSz = Map::COLUMN_COUNT * Map::ROW_COUNT;

	int parents[parentSz];

	parents[root] = -1;

	while (!queue.empty())
	{
		int node = queue.front();
		queue.pop();

		path.push_back(node);

		if (debug)
		{
			std::pair<int, int> pair = map.convert1Dto2D(node);
			sf::RectangleShape rectangle;
			rectangle.setPosition(pair.second * BLOCK_SZ, pair.first * BLOCK_SZ);
			rectangle.setSize(sf::Vector2f(BLOCK_SZ, BLOCK_SZ));

			sf::Color color = sf::Color::Green;

			rectangle.setFillColor(color);

			window.draw(rectangle);
		}

		if (node == target)
		{
			int path = 0;

			int parent = node;

			while (parent != -1)
			{
				parent = parents[parent];
				path++;
			}
			parent = node;

			float progress = (float)path;
			int prev = -1;
			while (parent != root)
			{
				prev = parent;
				parent = parents[parent];

				progress = progress - 1.0f;
			}

			if (prev == -1)
			{
				return root;
			}
			else
			{
				return prev;
			}
		}

		std::list <int> edges = graph[node];

		for (std::list<int>::iterator it = edges.begin(); it != edges.end(); it++)
		{
			int nde = *it;

			if (visited.count(nde) == 0)
			{
				visited.insert(nde);
				queue.push(nde);

				parents[nde] = node;
			}
		}
	}
	


*/
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
	delete this;
}
