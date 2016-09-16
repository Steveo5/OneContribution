#pragma once
#include <SFML\Graphics.hpp>

class Game
{
public:
	Game();
	~Game();
	void run();
private:
	sf::RenderWindow m_window;

	void handleEvents();
	void beginDraw();
	void endDraw();
	void tick();
	void update();
};

