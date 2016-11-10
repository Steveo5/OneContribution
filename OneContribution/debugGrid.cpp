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
	for (int i = 0; i < Game::instance()->getWorld().getWidth(); i += (Game::instance()->getWorld().getWidth() / Game::instance()->getWorld().getColumns()))
	{
		sf::Vertex line[] =
		{
			//getTileAt(sf::Vector2f(i, window.getSize().y))
			sf::Vertex(sf::Vector2f(i, 0), sf::Color::Red),
			sf::Vertex(sf::Vector2f(i, Game::instance()->getWorld().getHeight()), sf::Color::Red)
		};

		target.draw(line, 2, sf::Lines);
	}
	//Draw the vertical lines
	for (int i = 0; i < Game::instance()->getWorld().getHeight(); i += (Game::instance()->getWorld().getHeight() / Game::instance()->getWorld().getRows()))
	{
		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(0.f, i), sf::Color::Red),
			sf::Vertex(sf::Vector2f(Game::instance()->getWorld().getWidth(), i), sf::Color::Red)
		};

		target.draw(line, 2, sf::Lines);
	}
	
	
}

void debugGrid::update(sf::RenderWindow& window)
{

}

debugGrid::~debugGrid()
{
}
