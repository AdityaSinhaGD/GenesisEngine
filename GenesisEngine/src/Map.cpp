#include "Map.h"
#include "Game.h"
#include "EntityManager.h"

Map::Map(std::string textureId, int scale, int tileSize)
{
	this->textureId = textureId;
	this->scale = scale;
	this->tileSize = tileSize;
}

Map::~Map()
{
	
}

//Read map defined in text file and use it to load a grid of tiles
void Map::LoadMap(std::string filePath, int mapSizeX, int mapSizeY)
{
	
}

//Add new tile obj to the game scene
void Map::AddTile(int sourceRectX, int sourceRectY, int x, int y)
{

}
