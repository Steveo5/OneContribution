#include "UI.h"
#include <iostream>
#include "Game.h"
#pragma once
class BasicComponent : public UIComponent
{
public:
	BasicComponent();
	~BasicComponent();

private:
	sf::Font font;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void update(sf::RenderWindow& window);
};

