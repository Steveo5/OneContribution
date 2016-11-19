#include "stdafx.h"
#include <iostream>
#include <SFML\Graphics.hpp>
#include "Game.h"

void runGame()
{
	Game* game = new Game();

	game->setTest("test");

	std::cout << game->getTest() << std::endl;



	Entity* ent = Game::instance()->getWorld().spawnEntity(EntityType::KNIGHT, static_cast<sf::Vector2f>(Game::instance()->getWorld().getTile(sf::Vector2i(0, 1600))));
	ent->setName("Chandler");
	Path* path = new Path();
	ent->setPath(path);

	std::string enemyNames[20] = { "Ipes", "Ranesorth", "Margroth", "Zaramoran", "Ankruulde", "Ushu", "Ferran", "Gaapan", "Oskelze", "Drasnee", "Raxskel", "teca", "Shandrek", "Zergmo", "Tagamil", "Fenla", "Lormy", "Nockdruk", "Zergca" };
	sf::Vector2i spawnPoints[20] = { sf::Vector2i(-448,288), sf::Vector2i(-736,464), sf::Vector2i(-1120,656), sf::Vector2i(-1664,928), sf::Vector2i(-2272,1232), //top-left edge
		sf::Vector2i(2208,1264), sf::Vector2i(1696,976), sf::Vector2i(1312,816), sf::Vector2i(960,640), sf::Vector2i(544,368), //top-right edge
		sf::Vector2i(128,2944), sf::Vector2i(512,2720), sf::Vector2i(864,2512), sf::Vector2i(1024,2208), sf::Vector2i(1888,2000), //bottom-right edge
		sf::Vector2i(-320,2976), sf::Vector2i(-1088,2560), sf::Vector2i(-2720,1720), sf::Vector2i(-2240,1984), sf::Vector2i(-1888,2160) //bottom-left edge
	};

	int i = 0;
	Entity* ent2 = Game::instance()->getWorld().spawnEntity(EntityType::ENEMY, static_cast<sf::Vector2f>(Game::instance()->getWorld().getTile(spawnPoints[i])));
	Path* path2 = new Path();
	ent2->setName(enemyNames[i]);
	i++;

	Entity* ent3 = Game::instance()->getWorld().spawnEntity(EntityType::ENEMY, static_cast<sf::Vector2f>(Game::instance()->getWorld().getTile(spawnPoints[i])));
	Path* path3 = new Path();
	ent3->setName(enemyNames[i]);
	i++;

	Entity* ent4 = Game::instance()->getWorld().spawnEntity(EntityType::ENEMY, static_cast<sf::Vector2f>(Game::instance()->getWorld().getTile(spawnPoints[i])));
	Path* path4 = new Path();
	ent4->setName(enemyNames[i]);
	i++;

	Entity* ent5 = Game::instance()->getWorld().spawnEntity(EntityType::ENEMY, static_cast<sf::Vector2f>(Game::instance()->getWorld().getTile(spawnPoints[i])));
	Path* path5 = new Path();
	ent5->setName(enemyNames[i]);
	i++;

	Entity* ent6 = Game::instance()->getWorld().spawnEntity(EntityType::ENEMY, static_cast<sf::Vector2f>(Game::instance()->getWorld().getTile(spawnPoints[i])));
	Path* path6 = new Path();
	ent6->setName(enemyNames[i]);
	i++;

	Entity* ent7 = Game::instance()->getWorld().spawnEntity(EntityType::ENEMY, static_cast<sf::Vector2f>(Game::instance()->getWorld().getTile(spawnPoints[i])));
	Path* path7 = new Path();
	ent7->setName(enemyNames[i]);
	i++;

	Entity* ent8 = Game::instance()->getWorld().spawnEntity(EntityType::ENEMY, static_cast<sf::Vector2f>(Game::instance()->getWorld().getTile(spawnPoints[i])));
	Path* path8 = new Path();
	ent8->setName(enemyNames[i]);
	i++;

	Entity* ent9 = Game::instance()->getWorld().spawnEntity(EntityType::ENEMY, static_cast<sf::Vector2f>(Game::instance()->getWorld().getTile(spawnPoints[i])));
	Path* path9 = new Path();
	ent9->setName(enemyNames[i]);
	i++;

	Entity* ent10 = Game::instance()->getWorld().spawnEntity(EntityType::ENEMY, static_cast<sf::Vector2f>(Game::instance()->getWorld().getTile(spawnPoints[i])));
	Path* path10 = new Path();
	ent10->setName(enemyNames[i]);
	i++;

	Entity* ent11 = Game::instance()->getWorld().spawnEntity(EntityType::ENEMY, static_cast<sf::Vector2f>(Game::instance()->getWorld().getTile(spawnPoints[i])));
	Path* path11 = new Path();
	ent11->setName(enemyNames[i]);
	i++;

	Entity* ent12 = Game::instance()->getWorld().spawnEntity(EntityType::ENEMY, static_cast<sf::Vector2f>(Game::instance()->getWorld().getTile(spawnPoints[i])));
	Path* path12 = new Path();
	ent12->setName(enemyNames[i]);
	i++;

	Entity* ent13 = Game::instance()->getWorld().spawnEntity(EntityType::ENEMY, static_cast<sf::Vector2f>(Game::instance()->getWorld().getTile(spawnPoints[i])));
	Path* path13 = new Path();
	ent13->setName(enemyNames[i]);
	i++;

	Entity* ent14 = Game::instance()->getWorld().spawnEntity(EntityType::ENEMY, static_cast<sf::Vector2f>(Game::instance()->getWorld().getTile(spawnPoints[i])));
	Path* path14 = new Path();
	ent14->setName(enemyNames[i]);
	i++;

	Entity* ent15 = Game::instance()->getWorld().spawnEntity(EntityType::ENEMY, static_cast<sf::Vector2f>(Game::instance()->getWorld().getTile(spawnPoints[i])));
	Path* path15 = new Path();
	ent15->setName(enemyNames[i]);
	i++;

	Entity* ent16 = Game::instance()->getWorld().spawnEntity(EntityType::ENEMY, static_cast<sf::Vector2f>(Game::instance()->getWorld().getTile(spawnPoints[i])));
	Path* path16 = new Path();
	ent16->setName(enemyNames[i]);
	i++;

	Entity* ent17 = Game::instance()->getWorld().spawnEntity(EntityType::ENEMY, static_cast<sf::Vector2f>(Game::instance()->getWorld().getTile(spawnPoints[i])));
	Path* path17 = new Path();
	ent17->setName(enemyNames[i]);
	i++;

	Entity* ent18 = Game::instance()->getWorld().spawnEntity(EntityType::ENEMY, static_cast<sf::Vector2f>(Game::instance()->getWorld().getTile(spawnPoints[i])));
	Path* path18 = new Path();
	ent18->setName(enemyNames[i]);
	i++;

	Entity* ent19 = Game::instance()->getWorld().spawnEntity(EntityType::ENEMY, static_cast<sf::Vector2f>(Game::instance()->getWorld().getTile(spawnPoints[i])));
	Path* path19 = new Path();
	ent19->setName(enemyNames[i]);
	i++;

	Entity* ent20 = Game::instance()->getWorld().spawnEntity(EntityType::ENEMY, static_cast<sf::Vector2f>(Game::instance()->getWorld().getTile(spawnPoints[i])));
	Path* path20 = new Path();
	ent20->setName(enemyNames[i]);
	i++;

	//Initialize animations
	AnimationManager* animator = Game::instance()->getAnimator();

	//Animation* walkAnim = animator->generateAnimation("Resources/Sprite/KNIGHT_long.png", EntityType::KNIGHT, 0, 34, 25, 4);
	//animator->registerAnimation(EntityType::KNIGHT, "walkLeft", walkAnim);

	Animation* plyrwalkDown = animator->generateAnimation("Resources/Sprite/KNIGHT_long.png", EntityType::KNIGHT, 0, 34, 25, 4);
	animator->registerAnimation(EntityType::KNIGHT, "plyrwalkDown", plyrwalkDown);
	Animation* plyrwalkUp = animator->generateAnimation("Resources/Sprite/KNIGHT_long.png", EntityType::KNIGHT, 1, 34, 25, 4);
	animator->registerAnimation(EntityType::KNIGHT, "plyrwalkUp", plyrwalkUp);
	Animation* plyrwalkRight = animator->generateAnimation("Resources/Sprite/KNIGHT_long.png", EntityType::KNIGHT, 2, 34, 25, 4);
	animator->registerAnimation(EntityType::KNIGHT, "plyrwalkRight", plyrwalkRight);
	Animation* plyrwalkLeft = animator->generateAnimation("Resources/Sprite/KNIGHT_long.png", EntityType::KNIGHT, 3, 34, 25, 4);
	animator->registerAnimation(EntityType::KNIGHT, "plyrwalkLeft", plyrwalkLeft);
	Animation* enemwalkDown = animator->generateAnimation("Resources/Sprite/ENEMY_long.png", EntityType::ENEMY, 0, 34, 25, 4);
	animator->registerAnimation(EntityType::ENEMY, "enemwalkDown", enemwalkDown);
	Animation* enemwalkUp = animator->generateAnimation("Resources/Sprite/ENEMY_long.png", EntityType::ENEMY, 1, 34, 25, 4);
	animator->registerAnimation(EntityType::ENEMY, "enemwalkUp", enemwalkUp);
	Animation* enemwalkRight = animator->generateAnimation("Resources/Sprite/ENEMY_long.png", EntityType::ENEMY, 2, 34, 25, 4);
	animator->registerAnimation(EntityType::ENEMY, "enemwalkRight", enemwalkRight);
	Animation* enemwalkLeft = animator->generateAnimation("Resources/Sprite/ENEMY_long.png", EntityType::ENEMY, 3, 34, 25, 4);
	animator->registerAnimation(EntityType::ENEMY, "enemwalkLeft", enemwalkLeft);

	//for (int i = 0; i < walkAnim->getSize(); i++)
	//{
	//	std::cout << "Top " << walkAnim->getFrame(i).top << std::endl;
	//	std::cout << "Left " << walkAnim->getFrame(i).left << std::endl;
	//	std::cout << "Height " << walkAnim->getFrame(i).height << std::endl;
	//	std::cout << "Width " << walkAnim->getFrame(i).width << std::endl;
	//}

	std::cout << game->getTest() << std::endl;

	if (game->run() == false)
	{
		game->~Game();
		runGame();
	}
		
}

int main()
{
	runGame();

	return 0;
}

