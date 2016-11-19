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

	sf::Texture m_bottomSpriteTexture;
	sf::Sprite m_bottomSprite;
	sf::Font m_arialFont;
	sf::Text m_textEntities;
	sf::Text m_scoreCount;
	sf::Text m_ammoCount;


	sf::SoundBuffer buffer;
	sf::Sound sound;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void update(sf::RenderWindow& window);
};

