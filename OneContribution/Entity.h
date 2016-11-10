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
	DOWN,
	NONE
};

enum Action
{
	DYING,
	SPAWNING,
	ATTACKING,
	TAKING_DAMAGE
};

class Path
{
public:
	std::vector<sf::Vector2f>* getTiles();
	void setTiles(std::vector<sf::Vector2f> tiles);
	void addTile(sf::Vector2f tile);
	void removeTile(int index);
	sf::Vector2f* getCurrentTile();
	int getCurrentTileNumber();
	void setCurrentTile(int index);
	bool isPaused();
	bool isStopped();

	sf::Vector2f* getPreviousTile();
	sf::Vector2f* getNextTile();

private:
	std::vector<sf::Vector2f> m_tiles;
	int m_currentTile = -1;
};

class Entity : public sf::Drawable
{
public:
	Entity();
	Entity(EntityType entityType, sf::Vector2f location);
	int VecToInt(sf::Vector2i v);
	sf::Vector2i IntToVec(int i);
	
	~Entity();

	void newBFS();
	void BFS();

	void tick();
	void update();

	void setSpriteSheet();

	Path* getPath();
	void setPath(Path* newPath);
	void startPathing();
	void resetPathing();
	void stopPathing();

	void setHealth(int health);
	int getHealth();
	std::string getName();
	void setName(std::string name);
	bool willCollide(sf::Vector2f position);
	bool isHitting(sf::Vector2f position);
	void Entity::setTarget(sf::Vector2i);
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
	std::string m_name;
	int m_maxHealth;
	HealthBar* m_hpBar;
	Direction m_facing;

	Path* m_path;

	//Used for getting the entities direction
	sf::Vector2f m_lastPos;

	
	sf::Vector2i m_target;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


