#pragma once
#include "./EntityManager.h"
#include <map>
#include<string>
#include "./TextureManager.h"

class AssetManager
{
private:
	EntityManager* manager;
	std::map<std::string, SDL_Texture*> textures;
};

