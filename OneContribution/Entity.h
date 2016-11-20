#include "SFML\Graphics.hpp"
//#include "Game.h"
#include "HealthBar.h"
#include "Math.cpp"
#include "AnimatedSprite.hpp"
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
	sf::Vector2i m_tileSize;
	sf::Vector2i m_nextMove;
	
	AnimatedSprite* getSprite();
	~Entity();

	void BFS();

	void tick();
	void update(sf::Time deltaTime);

	Path* getPath();
	void setPath(Path* newPath);
	void startPathing();
	void resetPathing();
	void stopPathing();

	void setHealth(int health);
	int getHealth();
	std::string getName();
	sf::Vector2i getSpawnPoint();
	void setName(std::string name);
	bool willCollide(sf::Vector2f position);
	bool isHitting(sf::Vector2f position);
	void setSelected(bool selected);
	bool isSelected();
	void Entity::setTarget(sf::Vector2i);
	bool isDead();
	void applyDamage(int damage);
	void drawTracer();
	bool getTracer();
	void shootEnemy(int index, sf::RenderTarget &target);
	void adjustAmmo(int i);
	void setAmmo(int i);
	int getAmmo();
	bool isControllable();
	void setControllable(bool control);
	bool isVisible();
	void setVisible(bool visible);

	sf::FloatRect getGlobalBounds();
	Direction getFacing();
	void setFacing(Direction dir);


	sf::Text& getTextName();

	sf::Vector2f getSpritePosition();

	sf::Vector2i getSpritePositionInt();

	//sf::RectangleShape m_rectangle;

	//m_sprite stuff here
	AnimatedSprite m_sprite;
	sf::RectangleShape m_characterSelectionBox;

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

	sf::Font m_font;
	sf::Text m_textName;

	bool m_isSelected = false;

	Path* m_path;

	int m_ammo;
	float m_fireRate;
	bool m_tracer;
	int m_entityTarget;
	int m_alpha;

	//Used for getting the entities direction
	sf::Vector2f m_lastPos;
	sf::Vector2i m_target;
	int m_speedStep;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	int m_spawnIndex;
	sf::Vector2i m_spawnPoints[20] = { sf::Vector2i(-448,288), sf::Vector2i(-736,464), sf::Vector2i(-1120,656), sf::Vector2i(-1664,928), sf::Vector2i(-2272,1232), //top-left edge
		sf::Vector2i(2208,1264), sf::Vector2i(1696,976), sf::Vector2i(1312,816), sf::Vector2i(960,640), sf::Vector2i(544,368), //top-right edge
		sf::Vector2i(128,2944), sf::Vector2i(512,2720), sf::Vector2i(864,2512), sf::Vector2i(1024,2208), sf::Vector2i(1888,2000), //bottom-right edge
		sf::Vector2i(-320,2976), sf::Vector2i(-1088,2560), sf::Vector2i(-2720,1720), sf::Vector2i(-2240,1984), sf::Vector2i(-1888,2160) //bottom-left edge
	};
};


