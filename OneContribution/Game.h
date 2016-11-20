#pragma once
#include <SFML\Graphics.hpp>
#include "tmx\MapLoader.h"
#include "UI.h"
#include "World.h"
#include <iostream>
#include "SFML\Audio.hpp"
#include "AnimationManager.h"
#include "MenuComponent.h"

class Game
{
public:
	Game();
	~Game();
	bool run();

	UI* getUi();
	tmx::MapLoader* getMapLoader();
	World& getWorld();
	sf::RenderWindow & getWindow();
	AnimationManager* getAnimator();
	void playSound(std::string name);
	static Game* instance();

	void setTest(std::string test);
	std::string getTest();

	void gameOver();
	
	int getKillCount();
	void setKillCount(int i);

	//static World& getWorld();
private:
	sf::RenderWindow m_window;
	World m_world;
	sf::View m_view;
	sf::View m_miniMap;
	sf::RectangleShape m_miniMapSprite;
	bool m_fullscreen = true;

	std::string m_test;

	static Game* m_instance;

	AnimationManager* m_animator;

	tmx::MapLoader* m_ml;

	sf::Music m_music;
	sf::Sound m_gun;
	sf::Sound m_reload;
	sf::Sound m_ouch;
	sf::Sound m_dead;
	sf::Sound m_you_died;
	sf::SoundBuffer m_gunBuffer;
	sf::SoundBuffer m_reloadBuffer;
	sf::SoundBuffer m_gameOverBuffer;
	sf::SoundBuffer m_ouchBuffer;
	sf::SoundBuffer m_deadBuffer;

	UI m_ui;

	sf::Clock m_tickTimer;
	//tickTimer interval in milliseconds
	const int m_tickRate = 20;
	//Game speed multiplier
	const sf::Time m_timePerFrame = sf::seconds(1.f / 60.f);

	bool m_gameOver;
	sf::Sprite m_gameOverImg;
	sf::Texture m_gameOverImgTexture;
	sf::Font m_arialFont;

	void handleEvents();
	void beginDraw();
	void endDraw();
	void tick();
	void update(sf::Time deltaTime);
	int m_killCount = 0;



	void toggleFullscreen();
};

