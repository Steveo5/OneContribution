#pragma once
#include <SFML\Graphics.hpp>
#include "tmx\MapLoader.h"
#include "UI.h"
#include "World.h"

class Game
{
public:
	Game();
	~Game();
	void run();

	UI* getUi();
	tmx::MapLoader* getMapLoader();
	World& getWorld();
	static Game* getInstance();

	//static World& getWorld();
private:
	sf::RenderWindow m_window;
	World m_world;
	sf::View m_view;
	sf::View m_miniMap;
	sf::RectangleShape m_miniMapSprite;
	bool m_fullscreen = true;

	static Game* m_instance;

	tmx::MapLoader* m_ml;

	UI m_ui;

	sf::Clock m_tickTimer;
	//tickTimer interval in milliseconds
	const int m_tickRate = 20;
	//Game speed multiplier
	const sf::Time m_timePerFrame = sf::seconds(1.f / 60.f);

	void handleEvents();
	void beginDraw();
	void endDraw();
	void tick();
	void update();

	void toggleFullscreen();
};

