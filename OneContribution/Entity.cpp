#include "Entity.h"
#include "Animation.hpp"
#include "Game.h"
#include <algorithm>
#include <unordered_set>
#include <queue>

Animation m_animation;

Entity::Entity()
{

}
Entity::Entity(EntityType entityType, sf::Vector2f location)
	: m_sprite(sf::seconds(0.2), true, false)
{
	m_isSelected = false;
	m_characterSelectionBox.setFillColor(sf::Color::Transparent);
	m_characterSelectionBox.setOutlineColor(sf::Color::White);
	m_characterSelectionBox.setOutlineThickness(1.f);
	m_characterSelectionBox.setSize(sf::Vector2f(20, 40));
	m_maxHealth = 100;
	//m_rectangle.setOrigin(m_rectangle.getSize().x / 2, m_rectangle.getSize().y / 2);
	m_entityType = entityType;
	m_health = 70;
	m_visible = true;
	//m_rectangle.setPosition(location);
	//m_rectangle.setFillColor(sf::Color::Red);
	//m_rectangle.setSize(sf::Vector2f(100.f, 100.f));
	m_path = new Path();

	//m_sprite stuff here
	m_sprite.setPosition(location);
	//m_sprite stuff ends


	m_hpBar = new HealthBar();
	m_hpBar->setWidth(100);
	m_hpBar->setHealth(m_health);
	m_hpBar->setPosition(location + sf::Vector2f(50, 50));
	Game::instance()->getUi()->addComponent(m_hpBar);
	m_lastPos = m_sprite.getPosition();

	if (!m_font.loadFromFile("Resources/arial.ttf"))
	{

	}

	m_textName.setColor(sf::Color::Blue);
	m_textName.setFont(m_font);

	m_sprite.setScale(sf::Vector2f(0.5, 0.5));
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
	if (m_entityType == EntityType::KNIGHT)
	{
		m_sprite.setPosition(static_cast<sf::Vector2f>(m_target));
		std::cout << "m_sprite position: " << m_sprite.getPosition().x << ", " << m_sprite.getPosition().y << std::endl;
	}
	else if (m_entityType == EntityType::ENEMY)
	{
		m_target = static_cast<sf::Vector2i>(Game::instance()->getWorld().getEntities()[0]->getSpritePosition());

		if (m_sprite.getPosition().x > m_target.x)
		{
			if (m_sprite.getPosition().y > m_target.y)
			{
				std::cout << "move down-right" << std::endl;
				//move down-right
				Path().addTile(sf::Vector2f(getSpritePosition().x + 64, getSpritePosition().y + 32));
			}
			else
			{
				std::cout << "move up-right" << std::endl;
				//move up-right
				Path().addTile(sf::Vector2f(getSpritePosition().x + 64, getSpritePosition().y - 32));
			}
		}
		else
		{
			if (m_sprite.getPosition().y > m_target.y)
			{
				std::cout << "move down-left" << std::endl;
				//move down-left
				Path().addTile(sf::Vector2f(getSpritePosition().x - 64, getSpritePosition().y + 32));
			}
			else
			{
				std::cout << "move up-left" << std::endl;
				//move up-left

				m_lastPos = getSpritePosition();
				Path().addTile(sf::Vector2f(getSpritePosition().x - 64, getSpritePosition().y - 32));
				//m_sprite.setPosition(sf::Vector2f(getSpritePosition().x - 64, getSpritePosition().y - 32));
			}
		}
	}
	


	/*
	std::cout << "BFS" << std::endl;
	std::cout << "tile coords: " << Game::instance()->getWorld().getTilePos(m_target).x << ", " << Game::instance()->getWorld().getTilePos(m_target).y << std::endl;
	std::unordered_map <int, std::list<int>> m_graph = *Game::instance()->getWorld().getGraph();
	std::unordered_set<int> visited;

	std::queue<int> queue;

	int root = VecToInt(m_target);

	queue.push(root); // enqueue the root node
	visited.insert(root);

	std::list<int> path;

	int parents[10000];

	parents[root] = -1;

	while (!queue.empty())
	{
		int node = queue.front();
		std::cout << "node: " << node << std::endl;
		queue.pop();

		path.push_back(node);

		if (node == VecToInt(m_target))
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
				m_sprite.setPosition(static_cast<sf::Vector2f>(IntToVec(root)));
				std::cout << "ROOT!" << root << std::endl;;
			}
			else
			{
				std::cout << "PREV!" << std::endl;;
			}
		}

		std::list <int> edges = m_graph[node];

		for (std::list<int>::iterator it = edges.begin(); it != edges.end(); it++)
		{
			std::cout << "edges " << *it << std::endl;
			int nde = *it;

			if (visited.count(nde) == 0)
			{
				visited.insert(nde);
				queue.push(nde);

				parents[nde] = node;
			}
		}
	}*/
}

sf::Clock pathTimer;
void Entity::tick()
{
	if (isDead())
	{
		setVisible(false);
		return;
	}

	//m_sprite.setAnimation()
	Animation *anim = Game::instance()->getAnimator()->getAnimation(EntityType::KNIGHT, "walkLeft");
	m_sprite.play(*anim);

	if (pathTimer.getElapsedTime().asSeconds() > 5)
	{
		pathTimer.restart();
		if (m_path->getNextTile() != NULL)
		{
			std::cout << "Next tile = " << m_path->getNextTile()->x << " " << m_path->getNextTile()->y << std::endl;
			std::cout << "Current Pos " << m_sprite.getPosition().x << " " << m_sprite.getPosition().y << std::endl;
			m_sprite.setPosition(*m_path->getNextTile());
			m_path->setCurrentTile(m_path->getCurrentTileNumber() + 1);
		}
		BFS();
	}
	m_hpBar->setVisible(m_visible);
	m_hpBar->setHealth(m_health);


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

void Entity::setSelected(bool selected)
{
	m_isSelected = selected;
}
bool Entity::isSelected()
{
	return m_isSelected;
}

bool Entity::isHitting(sf::Vector2f position)
{
	return m_sprite.getGlobalBounds().contains(position);
}

void Entity::update(sf::Time deltaTime)
{
	if (isSelected())
	{
		m_characterSelectionBox.setPosition(getSpritePosition());
	}

	if (m_path->getNextTile() != NULL)
	{
		//sf::Vector2f direction = Math::normalize(getSpritePosition() - *m_path->getNextTile());
		
		//m_sprite.setPosition(m_sprite.getPosition() + (direction * (1000.f * deltaTime.asSeconds())));
	}
}

sf::Text& Entity::getTextName()
{
	return m_textName;
}

sf::FloatRect Entity::getGlobalBounds()
{
	return m_sprite.getGlobalBounds();
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

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_visible)
	{
		target.draw(m_sprite);
	}

	if (m_isSelected == true)
	{
		target.draw(m_characterSelectionBox);
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
	if (m_entityType == EntityType::KNIGHT && isSelected())
	{
		std::cout << "setTarget(): " << t.x << ", " << t.y << std::endl;
		m_target = t;
	}
	
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
	m_textName.setString(m_name);
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