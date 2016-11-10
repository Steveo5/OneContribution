#include "BasicComponent.h"



BasicComponent::BasicComponent()
	: UIComponent(new std::string("BasicComponent"))
{

}


BasicComponent::~BasicComponent()
{
}

void BasicComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (int i = 0; i < Game::instance()->getWorld().getEntities().size(); i++)
	{
		sf::Text toDraw = Game::instance()->getWorld().getEntities()[i]->getTextName();
		target.draw(toDraw);
	}
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
}
