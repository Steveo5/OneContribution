#include "pugixml.hpp"
#include "TileMap.h"
#include <iostream>
#include <vector>
#include "SFML\Graphics.hpp"

using namespace std;

class TmxLoader
{

private:

public:
	TmxLoader();
	~TmxLoader();
	static TileMap load(char location[]);

};

class Tileset
{
	Tileset(int firstGid, char name[], int tileWidth, int tileHeight, int tileCount, int columns, sf::Texture spriteSheet);
};

