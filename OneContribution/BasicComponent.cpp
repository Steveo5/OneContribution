#include "BasicComponent.h"


BasicComponent::BasicComponent()
	: UIComponent(new std::string("BasicComponent"))
{
	m_selectionBox.setOutlineColor(sf::Color::White);
	m_selectionBox.setFillColor(sf::Color::Transparent);
	m_selectionBox.setOutlineThickness(1.f);
	

	if (!buffer.loadFromFile("Resources/ogre2.wav"))
	{

	}
	sound.setLoop(true);
	sound.setPitch(1.5f);
	sound.setVolume(75.f);
	sound.setBuffer(buffer);

	if (!m_bottomSpriteTexture.loadFromFile("Resources/BottomBar.png"))
	{
		return;
	}

	m_bottomSprite.setTexture(m_bottomSpriteTexture);
	m_bottomSprite.setScale(sf::Vector2f(0.7, 0.7));
	//m_bottomSprite.setOrigin(m_bottomSprite.getGlobalBounds().width / 2, m_bottomSprite.getGlobalBounds().height / 2);
	if (!m_arialFont.loadFromFile("Resources/arial.ttf"))
	{
		return;
	}

	m_textEntities.setFont(m_arialFont);
	m_textEntities.setColor(sf::Color::White);
	m_textEntities.setCharacterSize(20);
}

BasicComponent::~BasicComponent()
{
}

bool wasLeftClicked = false;
void BasicComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (int i = 0; i < Game::instance()->getWorld().getEntities().size(); i++)
	{
		sf::Text toDraw = Game::instance()->getWorld().getEntities()[i]->getTextName();
		target.draw(toDraw);
	}

	if(wasLeftClicked)
		target.draw(m_selectionBox);

	target.draw(m_bottomSprite);
	target.draw(m_textEntities);
}

void BasicComponent::update(sf::RenderWindow& window)
{
	sf::Vector2f bottomSpritePos = window.mapPixelToCoords(sf::Vector2i(window.getSize().x / 2 - 400, window.getSize().y - 200));
	m_bottomSprite.setPosition(bottomSpritePos);
	
	m_textEntities.setPosition(bottomSpritePos.x + 100, bottomSpritePos.y + 50);

	if (Game::instance()->getWorld().getEntities().size() > 0)
	{
		std::string message = "Selected:";
		for (int i = 0; i < Game::instance()->getWorld().getEntities().size(); i++)
		{
			if(Game::instance()->getWorld().getEntities()[i]->isSelected())
				message += "\n" + Game::instance()->getWorld().getEntities()[i]->getName();
		}
		m_textEntities.setString(message);
	}
	else
	{
		m_textEntities.setString("Selected\nNone");
	}

	for (int i = 0; i < Game::instance()->getWorld().getEntities().size(); i++)
	{
		Entity* ent = Game::instance()->getWorld().getEntities()[i];
		sf::Text& toDraw = ent->getTextName();
		if (ent->getFacing() != Direction::NONE)
		{
			toDraw.setPosition(ent->getSpritePosition().x, ent->getSpritePosition().y - 50);
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		wasLeftClicked = true;
		if (m_isFirstClick)
		{
			for (int i = 0; i < Game::instance()->getWorld().getEntities().size(); i++)
			{
				Entity* ent = Game::instance()->getWorld().getEntities()[i];
				if (ent->getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition())))
				{
					ent->setSelected(true);
					if(sound.getStatus() != sf::Sound::Playing)
						sound.play();
					//while (sound.getStatus() == sf::Music::Playing);
				}
			}
			m_selectionBox.setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
			m_isFirstClick = false;
		}

		m_selectionBox.setSize(window.mapPixelToCoords(sf::Mouse::getPosition(window)) - m_selectionBox.getPosition());
	}
	else
	{
		if (wasLeftClicked)
		{
			wasLeftClicked = false;
			for (int i = 0; i < Game::instance()->getWorld().getEntities().size(); i++)
			{
				Entity* ent = Game::instance()->getWorld().getEntities()[i];
				if (m_selectionBox.getGlobalBounds().intersects(ent->getGlobalBounds()))
				{
					ent->setSelected(true);

				}
				else if (ent->isSelected())
				{
					ent->setSelected(false);
				}
			}
		}
		m_isFirstClick = true;
	}
}
