// Tile class
// Logic to draw a texture onto an individual tile.  
// Will likely be used for objects like maps and stuff

#ifndef TILE_H
#define TILE_H

#include "globals.h"

struct SDL_Texture;
class Graphics;

class Tile {
public:
	Tile();
	
	Tile(SDL_Texture* tileset, Vector2 size, Vector2 tilesetPosition, Vector2 position);
	
	void update(int elapsedTime);

	void draw(Graphics &graphics);
private:
	SDL_Texture* tileset;
	Vector2 size;				// Size of the tile
	Vector2 tilesetPosition;	// Position on the tileset/sheet
	Vector2 position;			// Position on the map

};

#endif
