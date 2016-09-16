#pragma once
#include <SFML\Graphics.hpp>
#include "Tile.h"

class TileMap : public sf::Drawable
{
public:
	TileMap(sf::Texture tileSet, int width, int height, float tileTextureDimension, float tileWorldDimension);
	~TileMap();

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
	void addTileVertices(Tile tile, sf::Vector2f position);

private:
	sf::Texture tileSet;
	sf::VertexArray *vertexArray;

	int height;
	int width;
	float tileTextureDimension;
	float tileWorldDimension;
};

