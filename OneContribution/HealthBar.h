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
	void setHeight(int height);
	void setHealth(int health);
	void setPosition(sf::Vector2f position);
	bool isVisible();
	void setVisible(bool visible);

private:
	int m_width;
	int m_height;
	int m_health;
	sf::RectangleShape m_healthGreen;
	sf::RectangleShape m_healthRed;
	bool m_visible;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void update(sf::RenderWindow& window);
};

