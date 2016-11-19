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
	m_characterSelectionBox.setOrigin(-20, 10);
	m_maxHealth = 100;
	m_entityType = entityType;
	m_health = 100;
	m_visible = true;
	m_path = new Path();

	//m_sprite stuff here
	m_sprite.setPosition(location);
	m_sprite.setOrigin(-20, 10);
	//m_sprite stuff ends


	m_hpBar = new HealthBar();
	m_hpBar->setWidth(50);
	m_hpBar->setHeight(3);
	m_hpBar->setHealth(m_health);
	m_hpBar->setPosition(location + sf::Vector2f(50, 50));
	Game::instance()->getUi()->addComponent(m_hpBar);
	m_lastPos = m_sprite.getPosition();

	m_ammo = 10;
	m_tracer = false;
	m_entityTarget = 0;
	m_alpha = 255;

	if (!m_font.loadFromFile("Resources/arial.ttf"))
	{

	}

	if (m_entityType == EntityType::KNIGHT)
	{
		m_textName.setColor(sf::Color::Green);
		m_speedStep = 4;
		
		m_fireRate = 0.25;
	}
	else
	{
		m_textName.setColor(sf::Color::Red);
		m_speedStep = 2;
	}
	m_textName.setFont(m_font);
	m_sprite.setScale(sf::Vector2f(1.0, 1.0));
	m_textName.setScale((m_sprite.getScale().x/2), (m_sprite.getScale().y / 2));//match scale of sprite halved (as sprite is no longer half scale)

	m_nextMove = getSpritePositionInt();
	m_target = getSpritePositionInt();
	m_spawnIndex = 0;

}

void Entity::BFS()//not a BFS, just a chase AI :/
{		
	if ((getSpritePositionInt().x >= (m_nextMove.x - m_speedStep) && getSpritePositionInt().x <= (m_nextMove.x + m_speedStep))//fix entity never reaching exactly m_nextMove (thus not updating)
		&& (getSpritePositionInt().y >= (m_nextMove.y - m_speedStep) && getSpritePositionInt().y <= (m_nextMove.y + m_speedStep)))
	{
		//std::cout << "pos = nextMove" << std::endl;
		m_sprite.setPosition(static_cast<sf::Vector2f>(m_nextMove));
	}	
	
	//update enemy target
	if (m_entityType == EntityType::ENEMY) m_target = Game::instance()->getWorld().getEntities()[0]->getSpritePositionInt();
	

	//if closer to target than nextMove, nextMove = target.
	if (abs(getSpritePositionInt().x - m_nextMove.x) > abs(getSpritePositionInt().x - m_target.x) && abs(getSpritePositionInt().y - m_nextMove.y) > abs(getSpritePositionInt().y - m_target.y))
	{
		m_nextMove = m_target;
	}

	else if (getSpritePositionInt() == m_nextMove)//&& m_nextMove != m_target)
	{
		if (getSpritePosition().x < m_target.x)
		{
			if (getSpritePosition().y < m_target.y)
			{
				//move down-right
				m_nextMove = (sf::Vector2i(getSpritePosition().x + (m_tileSize.x / 2), getSpritePosition().y + (m_tileSize.y / 2)));
				m_facing = Direction::RIGHT;
			}
			else
			{
				//move up-right
				m_nextMove = (sf::Vector2i(getSpritePosition().x + (m_tileSize.x / 2), getSpritePosition().y - (m_tileSize.y / 2)));
				m_facing = Direction::UP;
			}
		}
		else
		{
			if (getSpritePosition().y < m_target.y)
			{
				//move down-left
				m_nextMove = (sf::Vector2i(getSpritePosition().x - (m_tileSize.x / 2), getSpritePosition().y + (m_tileSize.y / 2)));
				m_facing = Direction::DOWN;
			}
			else
			{
				//move up-left
				m_nextMove = (sf::Vector2i(getSpritePosition().x - (m_tileSize.x / 2), getSpritePosition().y - (m_tileSize.y / 2)));
				m_facing = Direction::LEFT;
			}
		}
	}
	
	//apply player movement
	if (getSpritePositionInt() != m_target)
	{
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
}

AnimatedSprite* Entity::getSprite()
{
	return &m_sprite;
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
	/*if (m_lastPos != m_sprite.getPosition())
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
	}*/
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
	std::cout << "ammo: " << Game::instance()->getWorld().getEntities()[0]->getAmmo() << std::endl;
	//adjust if too much damage is dealt
	if (m_health < 0) m_health = 0;
	return;
}

void Entity::drawTracer()
{
	if (m_tracer)
	{
		sf::Vertex tracer[] =
		{
			sf::Vertex(sf::Vector2f(Game::instance()->getWorld().getEntities()[0]->getSpritePosition()), sf::Color(255,255,255,m_alpha)),
			sf::Vertex(sf::Vector2f(Game::instance()->getWorld().getEntities()[m_entityTarget]->getSpritePosition()), sf::Color(255,255,255,m_alpha))
		};

		Game::instance()->getWindow().draw(tracer, 3, sf::Lines);
		m_alpha -= 25;
		if (m_alpha < 0)
		{
			m_tracer = false;
			m_alpha = 255;
		}
	}
}

bool Entity::getTracer()
{
	return m_tracer;
}

void Entity::shootEnemy(int index, sf::RenderTarget &target)
{
	m_entityTarget = index;
	if (attackTimer.getElapsedTime().asSeconds() > m_fireRate)
	{
		m_tracer = true;
		
		if (Game::instance()->getWorld().getEntities()[0]->getAmmo() > 0)
		{
			Game::instance()->playSound("gun");
			m_fireRate = 0.33;
			Game::instance()->getWorld().getEntities()[0]->adjustAmmo(1);
		}
		if (Game::instance()->getWorld().getEntities()[0]->getAmmo() <= 0)
		{
			Game::instance()->playSound("reload");
			Game::instance()->getWorld().getEntities()[0]->setAmmo(10);
			m_fireRate = 3.0;//take longer to shoot next bullet due to reload.
		}
		
		Game::instance()->getWorld().getEntities()[index]->applyDamage(25);
		attackTimer.restart();
	}
	else
		return;
}

void Entity::adjustAmmo(int i)
{
	m_ammo--;

}

void Entity::setAmmo(int i)
{
	m_ammo = i;
}

int Entity::getAmmo()
{
	return m_ammo;
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
	//if (m_entityType == EntityType::KNIGHT && isSelected())
	//{
		std::cout << "setTarget(): " << t.x << ", " << t.y << std::endl;
		m_target = t;
	//}
	
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