#include "Entity.h"



Entity::Entity(EntityType entityType, sf::Vector2f location)
{
	m_rectangle.setPosition(location);
	m_entityType = entityType;
	m_health = m_maxHealth;
	m_invisible = false;

	m_rectangle.setFillColor(sf::Color::Red);
	m_rectangle.setSize(sf::Vector2f(100.f, 100.f));
}

void Entity::tick()
{

}

void Entity::update()
{
	float healthBarWidth = m_health / m_maxHealth * 100;
	m_healthGreen.setSize(sf::Vector2f(healthBarWidth, 20.f));
	m_healthRed.setSize(sf::Vector2f(100.f - healthBarWidth, 20.f));
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (!m_invisible)
	{
		target.draw(m_rectangle);
		target.draw(m_healthRed);
		target.draw(m_healthGreen);
	}
		
}


Entity::~Entity()
{
	delete this;
}
