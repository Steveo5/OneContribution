#include "debugGrid.h"
#include <iostream>


debugGrid::debugGrid(float x, float y)
	: UIComponent(new std::string("debugGrid"))
{
	std::cout << "debugGrid(): " << x << ", " << y << std::endl;

}

void debugGrid::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
	//m_RW = static_cast<sf::RenderWindow>(target.);
	for (int i = 0; i < 6400; i += 64)
	{
		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(i, 0), sf::Color::Red),
			sf::Vertex(sf::Vector2f(i, target.getSize().y), sf::Color::Red)
		};
		target.draw(line, 2, sf::Lines);
	}

	for (int j = 0; j < 3200; j += 64)
	{
		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(0, j), sf::Color::Red),
			sf::Vertex(sf::Vector2f(target.getSize().y, j), sf::Color::Red)
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
