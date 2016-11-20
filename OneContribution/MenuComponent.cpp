#include "MenuComponent.h"



MenuComponent::MenuComponent()
	: UIComponent(new std::string("Menu"))
{
	m_text[0] = sf::Text();
	m_text[1] = sf::Text();
	m_text[2] = sf::Text();
	m_text[3] = sf::Text();
	m_text[0].setString("Options");
	m_text[1].setString("Controls");
	m_text[2].setString("Help");
	m_text[3].setString("Exit");

	for (int i = 0; i < 4; i++)
	{
		m_text[i].setCharacterSize(40);
		if (i == m_selected)
		{
			m_text[i].setColor(sf::Color::Red);
		}
		else
		{
			m_text[i].setColor(sf::Color::White);
		}
	}
	m_background.setFillColor(sf::Color::Black);
	m_background.setSize(sf::Vector2f(100, 100));
}


MenuComponent::~MenuComponent()
{
}

void MenuComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_enabled)
	{
		target.draw(m_background);
		for (int i = 0; i < 4; i++)
		{
			target.draw(m_text[i]);
		}
	}
}

void MenuComponent::display(bool i)
{
	m_enabled = i;
}

void MenuComponent::update(sf::RenderWindow& window)
{
	m_background.setPosition(window.mapPixelToCoords(sf::Vector2i(0, 0)));
}

void MenuComponent::handleInput(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::F12)
	{
		if (m_enabled)
		{
			m_enabled = false;
		}
		else
		{
			m_enabled = true;
		}
	}
}