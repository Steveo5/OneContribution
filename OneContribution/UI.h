#pragma once
#include "SFML\Graphics.hpp"

class UI : public sf::Drawable
{
public:
	UI();
	~UI();
	void handleInput(sf::Keyboard::Key key);
	void handleInput(sf::Mouse::Button button);

	sf::RectangleShape m_debugOverlay;
	bool m_debugOverlayEnabled = false;

	void toggleDebugMenu();

	void updateDrawTime();
private:
	int m_drawTime = 0;
	sf::Clock m_drawTimer;

	sf::Text m_txtFps;
	sf::Font m_fontArial;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

