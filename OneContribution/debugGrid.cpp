#include "debugGrid.h"
#include <iostream>
#include "Game.h"

debugGrid::debugGrid(float x, float y)
	: UIComponent(new std::string("debugGrid"))
{
	std::cout << "debugGrid(): " << x << ", " << y << std::endl;

}

void debugGrid::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
	if (m_enabled == false)
	{
		return;
	}
	sf::Vertex line[] =
	{
		//getTileAt(sf::Vector2f(i, window.getSize().y))
		sf::Vertex(sf::Vector2f(0, 0), sf::Color::Green),
		sf::Vertex(sf::Vector2f(100, 100), sf::Color::Green)
	};
	target.draw(line, 2, sf::Lines);

	for (int i = -(Game::instance()->getWorld().getWidth() / 2); i <= Game::instance()->getWorld().getWidth() / 2; i += (Game::instance()->getWorld().getWidth() / Game::instance()->getWorld().getColumns()))
	{
		sf::Vertex line[] =
		{
			//getTileAt(sf::Vector2f(i, window.getSize().y))
			sf::Vertex(sf::Vector2f(i, 0), sf::Color::Red),
			sf::Vertex(sf::Vector2f(i, Game::instance()->getWorld().getHeight()), sf::Color::Red)
		};

		target.draw(line, 2, sf::Lines);
	}
	//Draw the horizontal lines
	for (int i = 0; i <= Game::instance()->getWorld().getHeight(); i += (Game::instance()->getWorld().getHeight() / Game::instance()->getWorld().getRows()))
	{
		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(-(Game::instance()->getWorld().getWidth() / 2), i), sf::Color::Red),
			sf::Vertex(sf::Vector2f(Game::instance()->getWorld().getWidth() / 2, i), sf::Color::Red)
		};

		target.draw(line, 2, sf::Lines);
	}
	
	
}

void debugGrid::update(sf::RenderWindow& window)
{

}

void debugGrid::handleInput(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::F4)
	{
		if (m_enabled == true)
		{
			m_enabled = false;
		}
		else
		{
			m_enabled = true;
		}
	}
}

debugGrid::~debugGrid()
{
}
