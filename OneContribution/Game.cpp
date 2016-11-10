#include "Game.h"
#include "debugGrid.h"
#include "tmx\MapLoader.h"
/*
tmx::MapLoader* Game::m_ml;
UI Game::m_ui;
World Game::m_world;
Entity m_entity;
*/
Game* Game::m_instance = 0;
Game::Game()
	: m_view(sf::FloatRect(0, 0, 1280, 720))
	, m_miniMap(sf::FloatRect(sf::FloatRect(0.f, 0.f, 200, 200)))
	, m_miniMapSprite(sf::RectangleShape(sf::Vector2f(m_miniMap.getSize().x, m_miniMap.getSize().y)))
{
	m_instance = this;
	m_ml = new tmx::MapLoader("Resources");
	m_miniMap.zoom(10);
	m_miniMapSprite.setOutlineColor(sf::Color::Blue);
	m_miniMapSprite.setOutlineThickness(5.f);
	m_miniMapSprite.setOrigin(m_miniMapSprite.getSize().x / 2, m_miniMapSprite.getSize().y / 2);
	m_miniMapSprite.setPosition(m_miniMap.getCenter().x, m_miniMap.getCenter().y);
	m_miniMapSprite.setFillColor(sf::Color::Transparent);

	m_miniMap.setViewport(sf::FloatRect(0.f, 0.f, 0.2, 0.2));
	m_miniMapSprite.setSize(sf::Vector2f(m_miniMap.getViewport().width, m_miniMap.getViewport().height));
	//m_view.setSize(1280 * 4, 720 * 4);
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	m_window.create(sf::VideoMode(1280, 720), "OneContribution", sf::Style::Default, settings);
	//m_window.create(sf::VideoMode(sf::VideoMode::getDesktopMode()), "OneContribution", sf::Style::Fullscreen, settings);
	m_window.setView(m_view);
	//m_window.setVerticalSyncEnabled(true);

	//m_ui = new UI();
	m_world.setWorld(sf::Vector2i(64, 32), sf::Vector2i(6400, 3200));//manually set fix
	//std::cout << "game() tileSize: " << m_ml->GetTileSize().x << ", " << m_ml->GetTileSize().y << std::endl;
	getWorld().spawnEntity(EntityType::KNIGHT, sf::Vector2f(150.f, 150.f));
	//getWorld().spawnEntity(EntityType::ENEMY, sf::Vector2f(50.f, 50.f));
	std::cout << "Game(): spritePos: " << getWorld().getEntities()[0]->getSpritePosition().x << ", " << getWorld().getEntities()[0]->getSpritePosition().x << std::endl;
	debugGrid* grid = new debugGrid(6400, 6400);
	m_ui.addComponent(grid);
}


Game::~Game()
{
}

void Game::run()
{
	if (!m_ml->Load("Map.tmx"))
	{
		std::cout << "failed to load map" << std::endl;
		return;
	}
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (m_window.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		//Clear the screen with black
		beginDraw();
		while (timeSinceLastUpdate > m_timePerFrame)
		{
			timeSinceLastUpdate -= m_timePerFrame;
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

		}

		m_window.draw(*m_ml);
		m_window.draw(getWorld());
		//m_window.draw(m_miniMapSprite);

		//Objects to draw to minimap
		m_window.setView(m_miniMap);
		m_window.draw(getWorld());
		m_window.draw(*m_ml);

		//Objects to draw to main window view
		m_window.setView(m_view);
		m_window.draw(m_ui);
		//Display everything to the screen
		endDraw();
	}
}

void Game::setTest(std::string test)
{
	m_test = test;
}
std::string Game::getTest()
{
	return m_test;
}

Game* Game::instance()
{
	return m_instance;
}

void Game::handleEvents()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		//m_view.move(-2.0, 0.0);
		m_view.setCenter(m_view.getCenter().x - 5.0, m_view.getCenter().y);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		//m_view.move(2.0, 0.0);
		m_view.setCenter(m_view.getCenter().x + 5.0, m_view.getCenter().y);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_view.setCenter(m_view.getCenter().x, m_view.getCenter().y - 5);
		//m_view.move(-0.0, -1.5);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		//m_view.move(0.0, 1.5);
		m_view.setCenter(m_view.getCenter().x, m_view.getCenter().y + 5);
	}

	sf::Vector2i mousePos = sf::Mouse::getPosition();
	if (mousePos.x > m_window.getSize().x + m_window.getPosition().x - 50)
	{
		m_view.move(4.0, 0.0);
	}
	if (mousePos.x <  m_window.getPosition().x + 50)
	{
		m_view.move(-4.0, 0.0);
	}
	if (mousePos.y > m_window.getSize().y + m_window.getPosition().y - 50)
	{
		m_view.move(0.0, 3.0);
	}
	if (mousePos.y < m_window.getPosition().y + 50)
	{
		m_view.move(0.0, -3.0);
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
		case::sf::Event::MouseButtonPressed:
			//Entity test
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				for (int i = 0; i < m_world.getEntities().size(); i++)
				{
					if (!m_world.getEntities()[i]->isHitting(m_window.mapPixelToCoords(sf::Mouse::getPosition()))) return;
					m_world.getEntities()[i]->setHealth(m_world.getEntities()[i]->getHealth() - 10);
					if (m_world.getEntities()[i]->getHealth() < 0) m_world.getEntities()[i]->setHealth(0);
				}
			}
			//provide target location to BFS
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				instance()->getWorld().getEntities()[0]->setTarget( instance()->getWorld().getTile(static_cast<sf::Vector2i>(m_window.mapPixelToCoords(sf::Mouse::getPosition()))));
			}
			break;
		case sf::Event::KeyPressed:
			m_ui.handleInput(event.key.code);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				toggleFullscreen();
			break;
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
	getWorld().tick();
}

void Game::update()
{
	m_world.update();
	
	m_miniMapSprite.setPosition(m_window.mapPixelToCoords(sf::Vector2i(0, 0)));
	//m_window.setView(m_view);
	m_ui.update(m_window);
}


void Game::toggleFullscreen()
{
	m_window.close();
	if (m_fullscreen)
	{
		m_window.create(sf::VideoMode(854, 480), "OneContribution", sf::Style::Default);
		m_fullscreen = false;
	}
	else
	{
		m_window.create(sf::VideoMode(sf::VideoMode::getDesktopMode()), "OneContribution", sf::Style::Fullscreen);
		m_fullscreen = true;
	}
	m_window.display();
}

tmx::MapLoader* Game::getMapLoader()
{
	return m_ml;
}

UI *Game::getUi()
{
	return &m_ui;
}

World& Game::getWorld()
{
	return m_world;
}

//World& Game::getWorld()
//{
//	return m_world;
//}