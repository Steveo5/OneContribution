#include "UI.h"

#include <iostream>

UI::UI()
	: m_debugOverlay(sf::RectangleShape(sf::Vector2f(600, 400)))
{
	m_debugOverlay.setFillColor(sf::Color::Black);
	m_debugOverlay.setPosition(0, 0);

	m_fontArial.loadFromFile("Resources/arial.ttf");
	m_txtFps.setFont(m_fontArial);
	m_txtFps.setCharacterSize(10);
	m_txtFps.setColor(sf::Color::White);
}


UI::~UI()
{
}

void UI::handleInput(sf::Keyboard::Key key)
{
	switch (key)
	{
	case sf::Keyboard::F3:
		std::cout << "test" << std::endl;
		toggleDebugMenu();
		break;
	}
}
void UI::handleInput(sf::Mouse::Button button)
{

}

void UI::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_debugOverlayEnabled)
	{
		target.draw(m_debugOverlay);
		target.draw(m_txtFps);
	}
}

void UI::toggleDebugMenu()
{
	if (m_debugOverlayEnabled == false)
	{
		m_debugOverlayEnabled = true;
	}
	else
	{
		m_debugOverlayEnabled = false;
	}
}

void UI::updateDrawTime()
{
	if (m_drawTimer.getElapsedTime().asSeconds() >= 1)
	{
		m_drawTimer.restart();
		m_txtFps.setString(std::to_string(m_drawTime));
		m_drawTime = 0;
	}
	m_drawTime++;
}
