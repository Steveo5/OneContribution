#include "GameOver.h"
#include <iostream>


GameOver::GameOver()
	: UIComponent(new std::string("GameOver"))
{
	m_fontArial.loadFromFile("Resources/arial.ttf");
	m_text.setFont(m_fontArial);
	m_text.setCharacterSize(100);
	m_text.setColor(sf::Color::White);
	//m_text.setOrigin()
	m_text.setPosition(0, 0);
}

void GameOver::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
	if (m_enabled)
		target.draw(m_text);
}

void GameOver::display(bool i)
{
	m_enabled = i;
}


GameOver::~GameOver()
{
}
