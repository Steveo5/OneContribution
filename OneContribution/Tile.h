#pragma once
#include <SFML\Graphics.hpp>

class Tile
{
public:
	Tile(int x, int y, sf::Color color);
	~Tile();
	int x;
	int y;

	sf::Color color;
};

