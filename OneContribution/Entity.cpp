#include "Entity.h"
#include "Animation.hpp"
#include "Game.h"
#include <algorithm>
#include <math.h>

Animation m_animation;

Entity::Entity()
{

}
Entity::Entity(EntityType entityType, sf::Vector2f location)
	: m_sprite(sf::seconds(0.2), true, false)
{
	m_tileSize = Game::instance()->getWorld().getTileSize();
	m_isSelected = false;
	m_characterSelectionBox.setFillColor(sf::Color::Transparent);
	m_characterSelectionBox.setOutlineColor(sf::Color::White);
	m_characterSelectionBox.setOutlineThickness(1.f);
	m_characterSelectionBox.setSize(sf::Vector2f(20, 40));
	m_characterSelectionBox.setOrigin(-21, 20);
	m_maxHealth = 100;
	m_entityType = entityType;
	m_health = 70;
	m_visible = true;
	m_path = new Path();

	//m_sprite stuff here
	m_sprite.setPosition(location);
	m_sprite.setOrigin(-42, 40);
	//m_sprite stuff ends


	m_hpBar = new HealthBar();
	m_hpBar->setWidth(50);
	m_hpBar->setHeight(5);
	m_hpBar->setHealth(m_health);
	m_hpBar->setPosition(location + sf::Vector2f(50, 50));
	Game::instance()->getUi()->addComponent(m_hpBar);
	m_lastPos = m_sprite.getPosition();

	if (!m_font.loadFromFile("Resources/arial.ttf"))
	{

	}

	if (m_entityType == EntityType::KNIGHT)
	{
		m_textName.setColor(sf::Color::Blue);
		m_speedStep = 4;
	}
	else
	{
		m_textName.setColor(sf::Color::Red);
		m_speedStep = 2;
	}
	m_textName.setFont(m_font);
	m_sprite.setScale(sf::Vector2f(0.5, 0.5));
	m_textName.setScale(m_sprite.getScale());//match scale of sprite

	m_nextMove = getSpritePositionInt();
	m_target = getSpritePositionInt();
	m_spawnIndex = 0;

}

void Entity::BFS()
{		
	if ((getSpritePositionInt().x >= (m_nextMove.x - m_speedStep) && getSpritePositionInt().x <= (m_nextMove.x + m_speedStep))//fix entity never reaching exactly m_nextMove (thus not updating)
		&& (getSpritePositionInt().y >= (m_nextMove.y - m_speedStep) && getSpritePositionInt().y <= (m_nextMove.y + m_speedStep)))
	{
		//std::cout << "pos = nextMove" << std::endl;
		m_sprite.setPosition(static_cast<sf::Vector2f>(m_nextMove));
	}	
	
	//debug purposes
	if (m_entityType == EntityType::ENEMY) m_target = Game::instance()->getWorld().getEntities()[0]->getSpritePositionInt();
	else
	{
		std::cout << "m_target: " << m_target.x << ", " << m_target.y << std::endl;
		std::cout << "m_nextMove: " << m_nextMove.x << ", " << m_nextMove.y << std::endl;
		std::cout << "position: " << getSpritePositionInt().x << ", " << getSpritePositionInt().y << std::endl;
	}

	//if closer to target than nextMove, nextMove = target.
	if (abs(getSpritePositionInt().x - m_nextMove.x) > abs(getSpritePositionInt().x - m_target.x) && abs(getSpritePositionInt().y - m_nextMove.y) > abs(getSpritePositionInt().y - m_target.y))
	{
		m_nextMove = m_target;
	}

	else if (getSpritePositionInt() == m_nextMove)
	{
		if (getSpritePosition().x < m_target.x)
		{
			if (getSpritePosition().y < m_target.y)
			{
				//move down-right
				m_nextMove = (sf::Vector2i(getSpritePosition().x + (m_tileSize.x / 2), getSpritePosition().y + (m_tileSize.y / 2)));
			}
			else
			{
				//move up-right
				m_nextMove = (sf::Vector2i(getSpritePosition().x + (m_tileSize.x / 2), getSpritePosition().y - (m_tileSize.y / 2)));
			}
		}
		else
		{
			if (getSpritePosition().y < m_target.y)
			{
				//move down-left
				m_nextMove = (sf::Vector2i(getSpritePosition().x - (m_tileSize.x / 2), getSpritePosition().y + (m_tileSize.y / 2)));
			}
			else
			{
				//move up-left
				m_nextMove = (sf::Vector2i(getSpritePosition().x - (m_tileSize.x / 2), getSpritePosition().y - (m_tileSize.y / 2)));
			}
		}
	}
	
	//apply player movement
	if (m_entityType == EntityType::KNIGHT)
	{
		sf::Vector2f m_tempMovement = Math::normalize(static_cast<sf::Vector2f>(m_nextMove) - getSpritePosition());
		m_tempMovement.x *= m_speedStep;
		m_tempMovement.y *= m_speedStep;
		m_sprite.move(m_tempMovement);
	}
	else//apply enemy movement
	{
		sf::Vector2f m_tempMovement = Math::normalize(static_cast<sf::Vector2f>(m_nextMove) - getSpritePosition());
		m_tempMovement.x *= m_speedStep;
		m_tempMovement.y *= m_speedStep;
		m_sprite.move(m_tempMovement);
	}
}

sf::Clock pathTimer;
sf::Clock attackTimer;
void Entity::tick()
{
	if (isDead())
	{
		if (m_entityType == EntityType::ENEMY)
		{
			setVisible(false);
			m_sprite.setPosition(static_cast<sf::Vector2f>(getSpawnPoint()));
			setVisible(true);
			setHealth(100);
			return;
		}
		if (m_entityType == EntityType::KNIGHT)
		{
			setVisible(false);

			Game::instance()->gameOver();
		}
		
	}

	//check for doing damage
	if (m_entityType == EntityType::ENEMY)
	{
		if ((abs(getSpritePositionInt().x - Game::instance()->getWorld().getEntities()[0]->getSpritePositionInt().x) < 30) 
			&& (abs(getSpritePositionInt().y - Game::instance()->getWorld().getEntities()[0]->getSpritePositionInt().y) < 30))//range for hit registration on player
		{
			if (attackTimer.getElapsedTime().asSeconds() > 1)//only allow 1 attack every second per enemy
			{
				Game::instance()->getWorld().getEntities()[0]->applyDamage(10);
				attackTimer.restart();//restart the timer for next attack
			}
		}
	}
	else
	{
		//player character damage updates
	}

	Animation *anim = Game::instance()->getAnimator()->getAnimation(EntityType::KNIGHT, "walkLeft");
	m_sprite.play(*anim);
	BFS();
	if (pathTimer.getElapsedTime().asSeconds() > 1)
	{
		pathTimer.restart();
		if (m_path->getNextTile() != NULL)
		{
			//std::cout << "Next tile = " << m_path->getNextTile()->x << " " << m_path->getNextTile()->y << std::endl;
			//std::cout << "Current Pos " << m_sprite.getPosition().x << " " << m_sprite.getPosition().y << std::endl;
			m_sprite.setPosition(*m_path->getNextTile());
			m_path->setCurrentTile(m_path->getCurrentTileNumber() + 1);
		}
	}

	//update health bars
	m_hpBar->setVisible(m_visible);
	m_hpBar->setHealth(m_health);
	m_hpBar->setPosition(sf::Vector2f(m_sprite.getPosition().x + 7, m_sprite.getPosition().y - 30));


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
		m_characterSelectionBox.setPosition(m_sprite.getPosition());
	}

	if (m_path->getNextTile() != NULL)
	{
		//std::cout << "getNextTile" << std::endl;
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

void Entity::applyDamage(int damage)
{
	//only do damage when alive
	if (m_health > 0)
	{
		m_health -= damage;
		Game::instance()->playSound("ouch");
		if (m_health == 0)
			Game::instance()->playSound("dead");
	}

	

	//adjust if too much damage is dealt
	if (m_health < 0) m_health = 0;
	return;
}

void Entity::shootEnemy(int index, sf::RenderTarget &target)
{
	if (attackTimer.getElapsedTime().asSeconds() > 0.25)
	{
		sf::Vertex tracer[] =
		{
			sf::Vertex(sf::Vector2f(Game::instance()->getWorld().getEntities()[0]->getSpritePosition()), sf::Color::Red),
			sf::Vertex(sf::Vector2f(Game::instance()->getWorld().getEntities()[index]->getSpritePosition()), sf::Color::Yellow)
		};
		Game::instance()->playSound("laser");
		target.draw(tracer, 2, sf::Lines);
		Game::instance()->getWorld().getEntities()[index]->applyDamage(10);
		attackTimer.restart();
	}
	else
		return;
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

sf::Vector2i Entity::getSpritePositionInt()
{
	return static_cast<sf::Vector2i>(m_sprite.getPosition());
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

sf::Vector2i Entity::getSpawnPoint()
{
	m_spawnIndex++;
	return Game::instance()->getWorld().getTile(m_spawnPoints[m_spawnIndex]);
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