#include "HealthBar.h"


HealthBar::HealthBar()
	: UIComponent("HealthBar")
{
	m_healthRed.setFillColor(sf::Color::Red);
	m_healthGreen.setFillColor(sf::Color::Green);
}

HealthBar::~HealthBar()
{
}

int HealthBar::getWidth()
{
	return m_width;
}
void HealthBar::setWidth(int width)
{
	m_width = width;
}

void HealthBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	std::cout << "Drawing ui component " << std::endl;
	target.draw(m_healthGreen);
	target.draw(m_healthRed);
}

void HealthBar::update(sf::RenderWindow& window)
{
	m_healthRed.setSize(sf::Vector2f(m_health, 20));
}

void HealthBar::setHealth(int health)
{
	m_health = health;
}