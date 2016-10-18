#include "SFML\Graphics.hpp"
//#include "Game.h"
#include "HealthBar.h"
#pragma once
enum EntityType
{
	ARROW,
	KNIGHT
};

class Entity : public sf::Drawable
{
public:
	Entity(EntityType entityType, sf::Vector2f location);
	~Entity();

	void tick();
	void update();

	void setHealth(int health);
	int getHealth();
	bool isColliding(sf::Vector2f position);
	//Move an entity to a position in target seconds
	void moveTo(sf::Vector2f position, int seconds);
	bool isDead();
	bool isControllable();
	void setControllable(bool control);
	bool isVisible();
	void setVisible(bool visible);

	//sf::RectangleShape m_rectangle;

	//m_sprite stuff here
	sf::Sprite m_sprite;
	sf::Texture m_characterSprite;
	//m_sprite stuff ends


private:

	bool m_controllable;
	EntityType m_entityType;
	int m_health;
	bool m_visible;
	int m_maxHealth;
	static HealthBar* m_hpBar;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

