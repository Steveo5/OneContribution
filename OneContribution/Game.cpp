#include "Game.h"



Game::Game()
	: m_window(sf::VideoMode(640, 480), "OneContribution")
	, m_view(sf::FloatRect(200, 200, 300, 200))
	, m_miniMap(sf::FloatRect(sf::FloatRect(0.75f, 0, 0.25f, 0.25f)))
{
	m_view.rotate(315.f);
	m_view.zoom(7);
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_view.setCenter(m_view.getCenter().x - 0.5, m_view.getCenter().y);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_view.setCenter(m_view.getCenter().x + 0.5, m_view.getCenter().y);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_view.setCenter(m_view.getCenter().x, m_view.getCenter().y - 0.5);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_view.setCenter(m_view.getCenter().x, m_view.getCenter().y + 0.5);
	}

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