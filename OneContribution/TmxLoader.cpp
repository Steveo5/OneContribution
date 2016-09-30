#include "TmxLoader.h"



TmxLoader::TmxLoader()
{
}


TmxLoader::~TmxLoader()
{
}

TileMap TmxLoader::load(char location[])
{
	pugi::xml_document doc;
	pugi::xml_parse_result result;
	result = doc.load_file(location);
	if (result)
	{
		//For each layer get the tiles
		pugi::xml_node nodes = doc.child("map");

		vector<Tileset> tileSets;
		
		//Load each tileset into memory
		for (pugi::xml_node tool = nodes.child("tileset"); tool; tool = tool.next_sibling("tileset"))
		{
			std::cout << tool.attribute("firstgid").value() << std::endl;
			//int firstGid = tool.attribute("firstgid").value();
			std::cout << firstGid << std::endl;
			//tileSets.push_back(Tileset());
		}
	}
	else
	{
		std::cout << "XML [" << location << "] parsed with errors, attr value: [" << doc.child("node").attribute("attr").value() << "]\n";
		std::cout << "Error description: " << result.description() << "\n";
		std::cout << "Error offset: " << result.offset << " (error at [..." << (location + result.offset) << "]\n\n";
	}
	return TileMap();
}

Tileset::Tileset(int firstGid, char name[], int tileWidth, int tileHeight, int tileCount, int columns, sf::Texture spriteSheet)
{

}
