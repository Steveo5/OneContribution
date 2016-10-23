#include "HealthBar.h"


HealthBar::HealthBar()
	: UIComponent(new std::string("HealthBar"))
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
	if (!m_visible) return;
	target.draw(m_healthRed);
	target.draw(m_healthGreen);
}

void HealthBar::update(sf::RenderWindow& window)
{
	double healthGreen = m_health * m_width / 100;
	m_healthGreen.setSize(sf::Vector2f(healthGreen, 20));
	m_healthRed.setSize(sf::Vector2f(m_width, 20));
}

void HealthBar::setHealth(int health)
{
	m_health = health;
}

void HealthBar::setPosition(sf::Vector2f position)
{
	m_healthGreen.setPosition(position);
	m_healthRed.setPosition(position);
}

bool HealthBar::isVisible()
{
	return m_visible;
}

void HealthBar::setVisible(bool visible)
{
	m_visible = visible;
}