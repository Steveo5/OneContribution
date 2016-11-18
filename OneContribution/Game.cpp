#include "Game.h"
#include "debugGrid.h"
#include "BasicComponent.h"
#include "GameOver.h"
#include "tmx\MapLoader.h"
#include "OneContribution.h"

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
	//m_window.create(sf::VideoMode(1280, 720), "OneContribution", sf::Style::Default, settings);
	m_window.create(sf::VideoMode(sf::VideoMode::getDesktopMode()), "OneContribution", sf::Style::Fullscreen, settings);
	m_window.setView(m_view);
	//m_window.setVerticalSyncEnabled(true);

	//m_ui = new UI();
	m_world.setWorld(sf::Vector2i(64, 32), sf::Vector2i(100, 100));//tile size, rows and columns
	
	debugGrid* grid = new debugGrid(6400, 6400);
	m_ui.addComponent(grid);

	//text for gameover screen
	m_gameOver = false;
	
	if (!m_arialFont.loadFromFile("Resources/arial.ttf"))
	{
	}

	m_gameOverText.setFont(m_arialFont);
	m_gameOverText.setColor(sf::Color::White);
	m_gameOverText.setCharacterSize(100);
	m_gameOverText.setString("GAME OVER");


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

	
	if (!m_gunBuffer.loadFromFile("Resources/gun.wav"))
	{
		std::cout << "gun.wav has not loaded correctly." << std::endl;
	}
	m_gun.setBuffer(m_gunBuffer);
	m_gun.setVolume(50.f);
	m_gun.setLoop(false);

	if (!m_reloadBuffer.loadFromFile("Resources/reload.wav"))
	{
		std::cout << "reload.wav has not loaded correctly." << std::endl;
	}
	m_reload.setBuffer(m_reloadBuffer);
	m_reload.setVolume(100.f);
	m_reload.setLoop(false);

	if (!m_gameOverBuffer.loadFromFile("Resources/nextTime.wav"))
	{
		std::cout << "nextTime.wav has not loaded correctly." << std::endl;
	}
	m_nextTime.setBuffer(m_gameOverBuffer);
	m_nextTime.setVolume(100.f);
	m_nextTime.setLoop(false);

	if (!m_ouchBuffer.loadFromFile("Resources/ouch.wav"))
	{
		std::cout << "ouch.wav has not loaded correctly." << std::endl;
	}
	m_ouch.setBuffer(m_ouchBuffer);
	m_ouch.setVolume(100.f);
	m_ouch.setLoop(false);

	if (!m_deadBuffer.loadFromFile("Resources/dead.wav"))
	{
		std::cout << "dead.wav has not loaded correctly." << std::endl;
	}
	m_dead.setBuffer(m_deadBuffer);
	m_dead.setVolume(100.f);
	m_dead.setLoop(false);

	m_animator = new AnimationManager();
}


Game::~Game()
{
	m_window.close();
}

bool Game::run()
{
	if (!m_ml->Load("Map.tmx"))
	{
		std::cout << "failed to load map" << std::endl;
		return true;
	}
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (m_window.isOpen())
	{
		if (m_gameOver)
		{
			m_window.draw(m_gameOverText);
			playSound("nextTime");
			//if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			//{
			//	//restart game
			//	return false;
			//}
			//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			//	return true; //end game
		}
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		//Clear the screen with black
		beginDraw();
		if (timeSinceLastUpdate > m_timePerFrame)
		{
			timeSinceLastUpdate -= m_timePerFrame;
			//Handle all events
			handleEvents();
			//Update the game
			update(timeSinceLastUpdate);
			//Do a game tick
			
			if (!m_gameOver)
			{
				if (m_tickTimer.getElapsedTime().asMilliseconds() > m_tickRate)
				{
					tick();
					m_tickTimer.restart();
				}
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

		m_world.getEntities()[0]->drawTracer();
		//Display everything to the screen
		endDraw();
	}
	return true;
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
	if (m_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			
			m_window.close();
			return;
		/*case sf::Event::MouseWheelScrolled:
			if (event.mouseWheelScroll.delta == 1)
			{
				m_view.setSize(m_view.getSize().x + 100, m_view.getSize().y + 100);
			}
			else
			{
				m_view.setSize(m_view.getSize().x - 100, m_view.getSize().y - 100);
			}
			break;*/
		case::sf::Event::MouseButtonPressed:
			//Entity test
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				for (int i = 1; i < m_world.getEntities().size(); i++)
				{
					if (!(m_world.getEntities()[i]->isHitting(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window))))) continue;
					else if (i > 0)
						m_world.getEntities()[i]->shootEnemy(i, m_window);//do damage on click of entity
				}
			}
			//provide target location to BFS
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				m_world.getEntities()[0]->setTarget(m_world.getTile(static_cast<sf::Vector2i>(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window)))));
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
	m_ui.update(m_window);
}

void Game::gameOver()
{
	m_gameOver = true;
}

void Game::toggleFullscreen()
{
	m_window.close();
	if (m_fullscreen)
	{
		m_window.create(sf::VideoMode(1280, 720), "OneContribution", sf::Style::Default);
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
	if (name == "gun") m_gun.play();
	if (name == "reload") m_reload.play();
	if (name == "ouch") m_ouch.play();
	if (name == "dead") m_dead.play();
	if (name == "nextTime")	m_nextTime.play();
}
//test