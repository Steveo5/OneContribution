#include "UI.h"

#include <iostream>

UI::UI()
{
	m_debugOverlay.setSize(sf::Vector2f(600, 400));
	m_debugOverlay.setFillColor(sf::Color::Black);
	m_debugOverlay.setPosition(0, 0);

	m_fontArial.loadFromFile("Resources/arial.ttf");
	m_txtDebug.setFont(m_fontArial);
	m_txtDebug.setCharacterSize(10);
	m_txtDebug.setColor(sf::Color::White);
	m_txtDebug.setPosition(0, 0);
	/*
	std::vector<Entity*> entities = Game::getWorld().getEntities();
	for (int i = 0; i < entities.size(); i++)
	{
		entities[i]->m_healthRed.setFillColor(sf::Color::Red);
		entities[i]->m_healthRed.setPosition(entities[i]->m_rectangle.getPosition().x - 50, entities[i]->m_rectangle.getPosition().y - 80);

		entities[i]->m_healthGreen.setFillColor(sf::Color::Green);
		entities[i]->m_healthGreen.setPosition(entities[i]->m_healthRed.getPosition().x + entities[i]->m_healthRed.getSize().x, entities[i]->m_healthRed.getPosition().y);
		
	}
	*/
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
		target.draw(m_txtDebug);
	}

	for (int i = 0; i < m_components.size(); i++)
	{
		target.draw(*m_components[i]);
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
		m_fps = m_drawTime;
		m_drawTime = 0;
	}
	m_drawTime++;
}

void UI::update(sf::RenderWindow &window)
{
	sf::Vector2f newDebugPos = window.mapPixelToCoords(sf::Vector2i(0, 0));
	sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition());
	m_debugOverlay.setPosition(newDebugPos);
	m_txtDebug.setPosition(newDebugPos);
	std::string fps = "Fps: " + std::to_string(m_fps);
	std::string mousePosStr = "Mouse Position: x " + std::to_string(mousePos.x) + " y " + std::to_string(mousePos.y);
	m_txtDebug.setString(fps + "\n" + mousePosStr);
	

	for (int i = 0; i < m_components.size(); i++)
	{
		m_components[i]->update(window);
	}
}

void UI::addComponent(UIComponent* component)
{
	m_components.push_back(component);
}

UIComponent::UIComponent(std::string* name)
{
	m_name = name;
}
UIComponent::~UIComponent()
{

}

std::string* UIComponent::getName()
{
	return m_name;
}

void UIComponent::update(sf::RenderWindow& window)
{

}

void UIComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

}

void UIComponent::setPosition(sf::Vector2f location)
{
	m_position = location;
}
sf::Vector2f UIComponent::getPosition()
{
	return m_position;
}