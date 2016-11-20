#include "UI.h"
#include <iostream>
#pragma once
class MenuComponent :public UIComponent
{
public:
	MenuComponent();
	~MenuComponent();
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void display(bool i);

	void handleInput(sf::Keyboard::Key key);
	void update(sf::RenderWindow& window);

	bool m_enabled = false;

	sf::Text m_text[4] = {};
	sf::Font m_fontArial;
	sf::RectangleShape m_background;

	int m_selected = 0;
};