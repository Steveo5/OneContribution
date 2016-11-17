#include "Game.h"
#include "debugGrid.h"
#include "BasicComponent.h"
#include "tmx\MapLoader.h"
/*
tmx::MapLoader* Game::m_ml;
UI Game::m_ui;
World Game::m_world;
Entity m_entity;
*/
Game* Game::m_instance = 0;
Game::Game()
	: m_view(sf::FloatRect(-600, 1280, 1280, 720))
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
	m_world.setWorld(sf::Vector2i(64, 32), sf::Vector2i(100, 100));//tile size, rows and columns
	
	debugGrid* grid = new debugGrid(6400, 6400);
	m_ui.addComponent(grid);

	BasicComponent* basicComponentUI = new BasicComponent();
	m_ui.addComponent(basicComponentUI);
	if (!m_music.openFromFile("Resources/Menu.ogg"))
	{
	}
	m_music.setPitch(1);
	m_music.setPosition(0, 1, 10);
	m_music.setVolume(25.f);
	m_music.setLoop(true);
	m_music.play();

	if (!m_laser.openFromFile("Resources/laser.wav"))
	{
	}
	m_laser.setPitch(1);
	m_laser.setPosition(0, 1, 10);
	m_laser.setVolume(50.f);
	m_laser.setLoop(false);

	if (!m_ouch.openFromFile("Resources/ouch.wav"))
	{
	}
	m_ouch.setPitch(1);
	m_ouch.setPosition(0, 1, 10);
	m_ouch.setVolume(50.f);
	m_ouch.setLoop(false);

	if (!m_dead.openFromFile("Resources/dead.wav"))
	{
	}
	m_dead.setPitch(1);
	m_dead.setPosition(0, 1, 10);
	m_dead.setVolume(50.f);
	m_dead.setLoop(false);

	m_animator = new AnimationManager();
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
			update(timeSinceLastUpdate);
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
				m_view.setSize(m_view.getSize().x + 100, m_view.getSize().y + 100);
			}
			else
			{
				m_view.setSize(m_view.getSize().x - 100, m_view.getSize().y - 100);
			}
			break;
		case::sf::Event::MouseButtonPressed:
			//Entity test
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				std::cout << "left click" << std::endl;
				//for (int i = 1; i < m_world.getEntities().size(); i++)
				//{
				//	if (m_world.getEntities()[i]->isHitting(m_window.mapPixelToCoords(sf::Mouse::getPosition())))
				//		m_world.getEntities()[i]->applyDamage(10);//do damage on click of entity
				//}
				for (int i = 1; i < m_world.getEntities().size(); i++)
				{
					if (!m_world.getEntities()[i]->isHitting(m_window.mapPixelToCoords(sf::Mouse::getPosition()))) return;
					else if (i > 0)
						m_world.getEntities()[i]->shootEnemy(i, m_window);//do damage on click of entity
					std::cout << "click loop" << std::endl;
				}
			}
			//provide target location to BFS
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				m_world.getEntities()[0]->setTarget(m_world.getTile(static_cast<sf::Vector2i>(m_window.mapPixelToCoords(sf::Mouse::getPosition()))));
			}
			break;
		case sf::Event::KeyPressed:
			m_ui.handleInput(event.key.code);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				toggleFullscreen();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp))
			{
				m_view.setSize(m_view.getSize().x + 200, m_view.getSize().y + 200);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown))
			{
				m_view.setSize(m_view.getSize().x - 200, m_view.getSize().y - 200);
			}
			break;
		case sf::Event::Resized:
			sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
			m_window.setView(sf::View(visibleArea));
			break;
		}
	}


}

AnimationManager* Game::getAnimator()
{
	return m_animator;
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

void Game::update(sf::Time deltaTime)
{
	m_world.update(deltaTime);
	
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

sf::RenderWindow& Game::getWindow()
{
	return m_window;
}

void Game::playSound(std::string name)
{
	if (name == "laser")
		m_laser.play();
	if (name == "ouch")
		m_ouch.play();
	if (name == "dead")
		m_dead.play();
}
//test