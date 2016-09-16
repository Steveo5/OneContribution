#pragma once
#include <SFML\Graphics.hpp>
#include "World.h"

class Game
{
public:
	Game();
	~Game();
	void run();
private:
	sf::RenderWindow m_window;
	World m_world;
	sf::View m_view;

	void handleEvents();
	void beginDraw();
	void endDraw();
	void tick();
	void update();

	void toggleFullscreen();
};

