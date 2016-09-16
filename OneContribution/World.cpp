#include "World.h"


World::World()
{
	if (!m_texture.loadFromFile("Resources/background.png"))
	{

	}

	
}


World::~World()
{
}

void World::Draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	
}
