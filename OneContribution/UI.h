#pragma once
#include "SFML\Graphics.hpp"

class Game;

class UIComponent : public sf::Drawable
{
public:
	UIComponent(std::string* name);
	~UIComponent();

	virtual void update(sf::RenderWindow& window);
	virtual void handleInput(sf::Keyboard::Key key);
	virtual void handleInput(sf::Mouse::Button button);

	std::string* getName();

	void setPosition(sf::Vector2f location);
	sf::Vector2f getPosition();
private:
	std::string* m_name;
	sf::Vector2f m_position;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

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

	void update(sf::RenderWindow &window);
	void updateDrawTime();

	void addComponent(UIComponent* component);
private:
	int m_drawTime = 0;
	int m_fps = 0;
	sf::Clock m_drawTimer;

	sf::Text m_txtDebug;
	sf::Font m_fontArial;

	std::vector<UIComponent*> m_components;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};