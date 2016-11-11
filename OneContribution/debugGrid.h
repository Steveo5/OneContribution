#pragma once
#include "UI.h"
class debugGrid:public UIComponent
{
public:
	debugGrid(float x, float y);
	~debugGrid();
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(sf::RenderWindow& window);

	bool m_enabled = false;

	void handleInput(sf::Keyboard::Key key);
};


