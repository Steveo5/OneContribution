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

	//static World& getWorld();
private:
	sf::RenderWindow m_window;
	World m_world;
	sf::View m_view;
	sf::View m_miniMap;
	sf::RectangleShape m_miniMapSprite;
	bool m_fullscreen = true;

	tmx::MapLoader m_ml;

	UI* m_ui;

	sf::Clock m_tickTimer;
	//tickTimer interval in milliseconds
	const int m_tickRate = 20;

	void handleEvents();
	void beginDraw();
	void endDraw();
	void tick();
	void update();

	void toggleFullscreen();
};

