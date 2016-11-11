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
		return m_textures[type];
	}
	else
	{
		return NULL;
	}
}

void AnimationManager::setTexture(EntityType type, sf::Texture* newTexture)
{
	m_textures[type] = newTexture;
}

Animation* AnimationManager::getAnimation(EntityType type, std::string animationName)
{
	if(m_animations.count(type) > 0)
	{
		if (m_animations[type].count(animationName) > 0)
		{
			return m_animations[type][animationName];
		}
		return NULL;
	}
	else
	{
		return NULL;
	}
}

void AnimationManager::registerAnimation(EntityType entityType, std::string animationName, Animation* animation)
{
	m_animations[entityType][animationName] = animation;
}

Animation* AnimationManager::generateAnimation(std::string directory, EntityType type, int row, int rowHeight, int rowWidth, int frameCount)
{
	sf::Texture* texture = new sf::Texture();
	if (!texture->loadFromFile(directory))
	{
		return NULL;
	}
	setTexture(type, texture);
	Animation* animation = new Animation();
	animation->setSpriteSheet(*texture);
	
	int rowPixel = row * rowHeight;
	for (int i=0;i<frameCount;i++)
	{
		int columnPixel = i * rowWidth;
		std::cout << "Column pixel " << columnPixel << " Row Pixel " << rowPixel << std::endl;
		
		sf::IntRect* rectangle = new sf::IntRect();
		rectangle->top = rowPixel;
		rectangle->left = columnPixel;
		rectangle->height = rowHeight;
		rectangle->width = rowWidth;
		animation->addFrame(*rectangle);
	}
	
	return animation;
}