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
	ent->setName("Knight");
	Path* path = new Path();
	path->addTile(sf::Vector2f(50, 50));
	path->addTile(sf::Vector2f(150, 50));
	path->addTile(sf::Vector2f(550, 50));
	path->addTile(sf::Vector2f(350, 500));
	path->setCurrentTile(0);
	ent->setPath(path);
	Entity* ent2 = Game::instance()->getWorld().spawnEntity(EntityType::KNIGHT, sf::Vector2f(150.f, 100.f));
	Path* path2 = new Path();
	path2->addTile(sf::Vector2f(500, 50));
	path2->addTile(sf::Vector2f(50, 50));
	path2->addTile(sf::Vector2f(50, 500));
	path2->addTile(sf::Vector2f(50, 100));
	path2->setCurrentTile(0);
	ent2->setPath(path);
	ent2->setName("Also Knight");

	//Entity* ent2 = Game::instance()->getWorld().spawnEntity(EntityType::KNIGHT, sf::Vector2f(50.f, 0.f));

	//game->getWorld().spawnEntity(EntityType::ENEMY, sf::Vector2f(50.f, 50.f));

	std::cout << game->getTest() << std::endl;

	game->run();

	return 0;
}

