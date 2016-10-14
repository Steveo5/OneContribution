#include "Entity.h"



Entity::Entity(EntityType entityType, sf::Vector2f location)
{
	m_rectangle.setPosition(location);
	m_entityType = entityType;
	m_health = m_maxHealth;
	m_invisible = false;

	m_rectangle.setFillColor(sf::Color::Red);
	m_rectangle.setSize(sf::Vector2f(100.f, 100.f));

	m_hpBar = new HealthBar();
	m_hpBar->setWidth(100);
}

void Entity::tick()
{
	m_hpBar->setHealth(m_health);
}

void Entity::update()
{
	float healthBarWidth = m_health / m_maxHealth * 100;
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (!m_invisible)
	{
		target.draw(m_rectangle);
	}
		
}


Entity::~Entity()
{
	delete this;
}
