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
}

void BasicComponent::update(sf::RenderWindow& window)
{
	for (int i = 0; i < Game::instance()->getWorld().getEntities().size(); i++)
	{
		Entity* ent = Game::instance()->getWorld().getEntities()[i];
		sf::Text& toDraw = ent->getTextName();
		if (ent->getFacing() != Direction::NONE)
		{
			toDraw.setPosition(ent->getSpritePosition().x, ent->getSpritePosition().y - 100);
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
					while (sound.getStatus() == sf::Music::Playing);
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
