#include "Game.h"



Game::Game()
	: m_window(sf::VideoMode(640, 480), "OneContribution")
{
}


Game::~Game()
{
}

void Game::run()
{
	while (m_window.isOpen())
	{
		//Clear the screen with black
		beginDraw();
		//Handle all events
		handleEvents();
		//Update the game
		update();
		//Do a game tick
		tick();
		//Display everything to the screen
		endDraw();
	}
}

void Game::handleEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				m_window.close();
				break;
			case sf::Keyboard::LAlt:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return))
				{
					toggleFullscreen();
				}
				break;
		}
	}
}

void Game::beginDraw()
{
	m_window.clear(sf::Color::Black);
}

void Game::endDraw()
{
	m_window.display();
}

void Game::tick()
{

}

void Game::update()
{

}


void Game::toggleFullscreen()
{
	m_window.close();
	m_window.create(sf::VideoMode(640, 480), "OneContribution", sf::Style::Fullscreen);
	m_window.display();
}