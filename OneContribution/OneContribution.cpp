#include "stdafx.h"
#include <iostream>
#include <SFML\Graphics.hpp>
#include "Game.h"


int main()
{
	Game* game = new Game();
	game->run();

	Game::getInstance()->getWorld().spawnEntity(EntityType::KNIGHT, sf::Vector2f(100, 200));

	game->getWorld().spawnEntity(EntityType::ARROW, sf::Vector2f(50, 50));

	return 0;
}

