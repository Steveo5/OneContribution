#include "SFML\Graphics.hpp"
//#include "Game.h"
#include "HealthBar.h"
#pragma once
enum EntityType
{
	ENEMY,
	KNIGHT
};

enum Direction
{
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class Entity : public sf::Drawable
{
public:
	Entity();
	Entity(EntityType entityType, sf::Vector2f location);
	int VecToInt(sf::Vector2i v);
	sf::Vector2i IntToVec(int i);
	~Entity();

	void BFS(sf::Vector2i, sf::Vector2i);

	void tick();
	void update();

	void setSpriteSheet();


	void setHealth(int health);
	int getHealth();
	bool willCollide(sf::Vector2f position);
	bool isHitting(sf::Vector2f position);
	//Move an entity to a position in target seconds
	void moveTo(sf::Vector2f position, int seconds);
	bool isDead();
	bool isControllable();
	void setControllable(bool control);
	bool isVisible();
	void setVisible(bool visible);
	Direction getFacing();

	sf::Vector2f getSpritePosition();

	//sf::RectangleShape m_rectangle;

	//m_sprite stuff here
	sf::Sprite m_sprite;
	sf::Texture m_characterSprite;
	bool m_isCharacterSprite;
	void updateSprite();
	int movingFrames;
	int idleFrames;
	int deathFrames;
	int actionFrames;
	int m_curFrames;
	sf::Vector2i startMove;
	sf::Vector2i startIdle;
	sf::Vector2i startDeath;
	sf::Vector2i startAction;
	sf::Vector2i m_curStart;
	sf::Vector2i m_frameSize;


	//m_sprite stuff ends

private:

	bool m_controllable;
	EntityType m_entityType;
	int m_health;
	bool m_visible;
	int m_maxHealth;
	static HealthBar* m_hpBar;
	Direction m_facing;

	//Used for getting the entities direction
	sf::Vector2f m_lastPos;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

