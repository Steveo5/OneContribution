#pragma once
#include "UI.h"
class GameOver :public UIComponent
{
public:
	GameOver();
	~GameOver();
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void display(bool i);

	bool m_enabled = false;

	sf::Text m_text;
	sf::Font m_fontArial;
};