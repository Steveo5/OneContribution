#include "Game.h"

#include "tmx\MapLoader.h"

Game::Game()
	: m_window(sf::VideoMode(1280, 720), "OneContribution", sf::Style::Fullscreen)
	, m_view(sf::FloatRect(0, 0, 1280, 720))
	, m_miniMap(sf::FloatRect(sf::FloatRect(200.f, 200.f, 200, 200)))
	, m_miniMapSprite(sf::RectangleShape(sf::Vector2f(m_miniMap.getSize().x, m_miniMap.getSize().y)))
{
	m_miniMap.setViewport(sf::FloatRect(0, 0, 0.2, 0.2));
	m_miniMap.zoom(10);
	m_miniMapSprite.setOutlineColor(sf::Color::Blue);
	m_miniMapSprite.setOutlineThickness(5.f);
	m_miniMapSprite.setPosition(0, 0);
	m_miniMapSprite.setFillColor(sf::Color::Transparent);
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
		if (m_tickTimer.getElapsedTime().asMilliseconds() > m_tickRate)
		{
			tick();
			m_tickTimer.restart();
		}

		m_window.draw(m_world);
		ml.Draw(m_window, 0, true);
		m_window.draw(m_miniMapSprite);

		m_window.setView(m_miniMap);
		m_window.draw(m_world);
		ml.Draw(m_window, 0, true);

		m_window.setView(m_view);
		m_window.draw(m_ui);
		//Display everything to the screen
		endDraw();
	}
}

void Game::handleEvents()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_view.move(-2.0, 0.0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_view.move(2.0, 0.0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_view.move(-0.0, -1.5);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_view.move(0.0, 1.5);
	}
	sf::Vector2i mousePos = sf::Mouse::getPosition();
	if (mousePos.x > m_window.getSize().x - 5)
	{
		m_view.move(2.0, 0.0);
	}
	if (mousePos.x < 5)
	{
		m_view.move(-2.0, 0.0);
	}
	if (mousePos.y > m_window.getSize().y - 5)
	{
		m_view.move(0.0, 1.5);
	}
	if (mousePos.y < 5)
	{
		m_view.move(0.0, -1.5);
	}
	sf::Event event;
	while (m_window.pollEvent(event))
	{

		switch (event.type)
		{
			case sf::Event::Closed:
				m_window.close();
				break;
			case sf::Event::MouseWheelScrolled:
				if (event.mouseWheelScroll.delta == 1)
				{
					m_view.setSize(m_view.getSize().x + 20, m_view.getSize().y + 20);
				}
				else
				{
					m_view.setSize(m_view.getSize().x - 20, m_view.getSize().y - 20);
				}
				break;
			case sf::Event::KeyPressed:
				m_ui.handleInput(event.key.code);
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
					toggleFullscreen();
			case sf::Event::Resized:
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				m_window.setView(sf::View(visibleArea));
				break;
		}
	}
}

void Game::beginDraw()
{
	m_window.clear(sf::Color::Black);
	m_ui.updateDrawTime();
}

void Game::endDraw()
{
	m_miniMap.setCenter(m_view.getCenter());
	m_window.display();
}

void Game::tick()
{
	m_world.tick();
}

void Game::update()
{
	m_world.update();
	//m_window.setView(m_view);
}


void Game::toggleFullscreen()
{
	m_window.close();
	if (m_fullscreen)
	{
		m_window.create(sf::VideoMode(640, 480), "OneContribution", sf::Style::Default);
		m_fullscreen = false;
	}
	else
	{
		m_window.create(sf::VideoMode(1280, 720), "OneContribution", sf::Style::Fullscreen);
		m_fullscreen = true;
	}
	m_window.display();
}