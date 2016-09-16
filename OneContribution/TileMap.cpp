#include "TileMap.h"
#include "Tile.h"


TileMap::TileMap(sf::Texture tileSet, int width, int height, float tileTextureDimension, float tileWorldDimension)
{
	this->tileSet = tileSet;
	this->width = width;
	this->height = height;
	this->tileTextureDimension = tileTextureDimension;
	this->tileWorldDimension = tileWorldDimension;

	this->vertexArray = new sf::VertexArray(sf::PrimitiveType(sf::Quads), (unsigned int)width * height * 4);

	Tile tile(0, 0, sf::Color::Blue);
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			addTileVertices(tile, sf::Vector2f((float)x, (float)y));
		}
	}
}

void TileMap::addTileVertices(Tile tile, sf::Vector2f position)
{
	vertexArray->append(sf::Vertex((sf::Vector2f(0.f, 0.f) + position) * tileWorldDimension, 
		sf::Vector2f(tileTextureDimension * tile.x, tileTextureDimension * tile.y)));

	vertexArray->append(sf::Vertex((sf::Vector2f(1.f, 0.f) + position) * tileWorldDimension, 
		sf::Vector2f(tileTextureDimension * tile.x + tileTextureDimension, tileTextureDimension * tile.y)));

	vertexArray->append(sf::Vertex((sf::Vector2f(1.f, 1.f) + position) * tileWorldDimension, 
		sf::Vector2f(tileTextureDimension * tile.x + tileTextureDimension, tileTextureDimension * tile.y + tileTextureDimension)));

	vertexArray->append(sf::Vertex((sf::Vector2f(0.f, 1.f) + position) * tileWorldDimension, 
		sf::Vector2f(tileTextureDimension * tile.x, tileTextureDimension * tile.y + tileTextureDimension)));
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	state.texture = &tileSet;
	target.draw(*vertexArray, state);
}

TileMap::~TileMap()
{
}
