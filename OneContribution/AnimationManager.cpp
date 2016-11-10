#include "AnimationManager.h"



AnimationManager::AnimationManager()
{
}


AnimationManager::~AnimationManager()
{
}

sf::Texture* AnimationManager::getTexture(EntityType type)
{
	if (m_textures.count(type) > 0)
	{
		return &m_textures[type];
	}
	else
	{
		return NULL;
	}
}

void AnimationManager::setTexture(EntityType type, sf::Texture newTexture)
{
	m_textures[type] = newTexture;
}

Animation* AnimationManager::getAnimation(EntityType type, std::string animationName)
{
	if(m_animations.count(type) > 0)
	{
		if (m_animations[type].count(animationName) > 0)
		{
			return &m_animations[type][animationName];
		}
		return NULL;
	}
	else
	{
		return NULL;
	}
}

void AnimationManager::registerAnimation(EntityType entityType, std::string animationName, Animation animation)
{
	m_animations[entityType][animationName] = animation;
}

Animation* AnimationManager::generateAnimation(sf::Texture& texture, int row, int rowHeight, int rowWidth, int frameCount)
{
	Animation* animation = new Animation();
	animation->setSpriteSheet(texture);

	int rowPixel = row * rowHeight;
	for (int i=0;i<frameCount;i++)
	{
		int columnPixel = i * rowWidth;
		animation->addFrame(sf::IntRect(rowPixel, columnPixel, rowWidth, rowHeight));
	}
	return animation;
}