#include "Game.h"

#include "tmx\MapLoader.h"

Game::Game()
	: m_window(sf::VideoMode(640, 480), "OneContribution")
	, m_view(sf::FloatRect(200, 200, 200, 200))
	, m_miniMap(sf::FloatRect(sf::FloatRect(0.75f, 0, 0.25f, 0.25f)))
{
	m_view.zoom(7);
}


Game::~Game()
{
}

void Game::run()
{
	tmx::MapLoader ml("Resources");
	if (!ml.Load("Map.tmx"))
	{
		std::cout << "failed to load map" << std::endl;
	}
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
		m_window.draw(ml);
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
	m_window.draw(m_world);
	m_window.display();
}

void Game::tick()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_view.move(-0.2, 0.2);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_view.move(0.2, -0.2);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_view.move(-0.2, -0.2);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_view.move(0.2, 0.2);
	}
}

void Game::update()
{
	m_window.setView(m_view);
}


void Game::toggleFullscreen()
{
	m_window.close();
	m_window.create(sf::VideoMode(640, 480), "OneContribution", sf::Style::Fullscreen);
	m_window.display();
}