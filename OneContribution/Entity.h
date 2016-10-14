#include "SFML\Graphics.hpp"
#include "HealthBar.h"
#pragma once
enum EntityType
{
	NPC,
	MONSTER,
	PLAYER
};

class Entity : public sf::Drawable
{
public:
	Entity(EntityType entityType, sf::Vector2f location);
	~Entity();

	void tick();
	void update();

	sf::RectangleShape m_rectangle;

private:

	EntityType m_entityType;
	int m_health;
	bool m_invisible;
	int m_maxHealth;
	HealthBar* m_hpBar;


	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

