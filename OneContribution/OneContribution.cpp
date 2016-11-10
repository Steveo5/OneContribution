#include "stdafx.h"
#include <iostream>
#include <SFML\Graphics.hpp>
#include "Game.h"


int main()
{
	Game* game = new Game();

	game->setTest("test");

	std::cout << game->getTest() << std::endl;

	Entity* ent = Game::instance()->getWorld().spawnEntity(EntityType::KNIGHT, sf::Vector2f(50.f, 0.f));

	Entity* ent2 = Game::instance()->getWorld().spawnEntity(EntityType::KNIGHT, sf::Vector2f(150.f, 100.f));


	//Entity* ent2 = Game::instance()->getWorld().spawnEntity(EntityType::KNIGHT, sf::Vector2f(50.f, 0.f));

	//game->getWorld().spawnEntity(EntityType::ENEMY, sf::Vector2f(50.f, 50.f));

	std::cout << game->getTest() << std::endl;

	game->run();

	return 0;
}

