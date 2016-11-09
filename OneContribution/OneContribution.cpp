#include "stdafx.h"
#include <iostream>
#include <SFML\Graphics.hpp>
#include "Game.h"


int main()
{
	Game* game = new Game();

	game->setTest("test");

	std::cout << game->getTest() << std::endl;

	Game::instance()->getWorld().spawnEntity(EntityType::KNIGHT, sf::Vector2f(-100.f, 0.f));
	//game->getWorld().spawnEntity(EntityType::ENEMY, sf::Vector2f(50.f, 50.f));

	std::cout << game->getTest() << std::endl;

	game->run();

	return 0;
}

