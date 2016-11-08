#include "stdafx.h"
#include <iostream>
#include <SFML\Graphics.hpp>
#include "Game.h"


int main()
{
	Game* game = new Game();
	game->run();

	game->getWorld().spawnEntity(EntityType::KNIGHT, sf::Vector2f(-50.f, 0.f));
	//game->getWorld().spawnEntity(EntityType::ENEMY, sf::Vector2f(50.f, 50.f));
	return 0;
}

