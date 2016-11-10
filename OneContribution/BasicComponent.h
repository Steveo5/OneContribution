#include "UI.h"
#include <iostream>
#include "Game.h"
#include "SFML\Audio.hpp"
#pragma once
class BasicComponent : public UIComponent
{
public:
	BasicComponent();
	~BasicComponent();

private:
	sf::Font font;
	sf::RectangleShape m_selectionBox;
	bool m_isFirstClick = true;

	sf::SoundBuffer buffer;
	sf::Sound sound;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void update(sf::RenderWindow& window);
};

