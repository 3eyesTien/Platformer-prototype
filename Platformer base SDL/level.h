#ifndef LEVEL_H
#define LEVEL_H

#include "globals.h"
#include "tile.h"
#include <string>
#include <vector>

class Graphics;
struct SDL_Texture;
struct Tileset;		//Forward declaring Tileset because the Struct is beneath this class definition

class Level
{
public:
	Level();
	Level(std::string mapName, Vector2 spawnPoint, Graphics &graphics);
	~Level();
	void update(int elapsedTime);
	void draw(Graphics &graphics);

private:
	std::string mapName;
	Vector2 spawnPoint;
	
	Vector2 size;
	Vector2 tileSize; // Tilesize on the map

	SDL_Texture* backgroundTexture;

	std::vector<Tile> tileList;
	std::vector<Tileset> tilesets;

	/* loadMap
	* Load one map
	*/
	void loadMap(std::string mapName, Graphics &graphics);
};

// Tileset structure
struct Tileset 
{
	SDL_Texture* Texture;
	int FirstGid;
	
	Tileset() 
	{
		this->FirstGid = -1;
	}

	Tileset(SDL_Texture* texture, int firstGid)
	{
		this->Texture = texture;
		this->FirstGid = firstGid;
	}
};

#endif
