#pragma once
#include <iostream>
#include "SFML\Graphics.hpp"
#include "Entity.h"
#include "Animation.hpp"
#include <algorithm>

class AnimationManager
{
public:
	AnimationManager();
	~AnimationManager();

	sf::Texture* getTexture(EntityType type);
	void setTexture(EntityType type, sf::Texture newTexture);

	Animation* getAnimation(EntityType type, std::string animationName);
	void registerAnimation(EntityType entityType, std::string animationName, Animation animation);

	Animation* generateAnimation(sf::Texture& texture, int row, int rowHeight, int rowWidth, int frameCount);
private:
	std::map<EntityType, sf::Texture> m_textures;
	std::map<EntityType, std::map<std::string, Animation>> m_animations;
};

