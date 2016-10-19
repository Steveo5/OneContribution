#pragma once
#include <SFML\Graphics.hpp>
#include "Entity.h"
#include <iostream>

class World : public sf::Drawable
{
public:
	World();
	~World();
	
	Entity* spawnEntity(EntityType type, sf::Vector2f location);
	std::vector<Entity*> getEntities();

	void tick();
	void update();

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Texture m_texture;

	std::vector<Entity*> m_entities;
};

