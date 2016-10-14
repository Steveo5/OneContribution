#include <iostream>
#include "UI.h"

#pragma once
class HealthBar : public UIComponent
{
public:
	HealthBar();
	~HealthBar();

	int getWidth();
	void setWidth(int width);

	void setHealth(int health);

private:
	int m_width;
	int m_health;
	sf::RectangleShape m_healthGreen;
	sf::RectangleShape m_healthRed;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void update(sf::RenderWindow& window);
};

