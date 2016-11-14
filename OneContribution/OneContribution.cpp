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
	ent->setName("Chandler");
	Path* path = new Path();
	path->addTile(sf::Vector2f(50, 50));
	path->addTile(sf::Vector2f(150, 50));
	path->addTile(sf::Vector2f(250, 50));
	path->addTile(sf::Vector2f(350, 200));
	//path->setCurrentTile(0);
	ent->setPath(path);
	
	Entity* ent2 = Game::instance()->getWorld().spawnEntity(EntityType::KNIGHT, sf::Vector2f(150.f, 100.f));
	Path* path2 = new Path();
	//path2->addTile(sf::Vector2f(10, 40));
	//path2->addTile(sf::Vector2f(40, 50));
	//path2->addTile(sf::Vector2f(50, 300));
	//path2->addTile(sf::Vector2f(50, 100));
	//path2->setCurrentTile(0);
	ent2->setPath(path);
	ent2->setName("Pidwick");
	
	//Initialize animations
	AnimationManager* animator = Game::instance()->getAnimator();

	Animation* walkAnim = animator->generateAnimation("Resources/Sprite/testing.png", EntityType::KNIGHT, 1, 80, 40, 4);
	animator->registerAnimation(EntityType::KNIGHT, "walkLeft", walkAnim);
	
	for (int i = 0; i < walkAnim->getSize(); i++)
	{
		std::cout << "Top " << walkAnim->getFrame(i).top << std::endl;
		std::cout << "Left " << walkAnim->getFrame(i).left << std::endl;
		std::cout << "Height " << walkAnim->getFrame(i).height << std::endl;
		std::cout << "Width " << walkAnim->getFrame(i).width << std::endl;
	}
	//Entity* ent2 = Game::instance()->getWorld().spawnEntity(EntityType::KNIGHT, sf::Vector2f(50.f, 0.f));

	//game->getWorld().spawnEntity(EntityType::ENEMY, sf::Vector2f(50.f, 50.f));

	std::cout << game->getTest() << std::endl;

	game->run();

	return 0;
}

