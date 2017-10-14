#include "tile.h"
#include "graphics.h"

#include <SDL.h>

Tile::Tile() {}

Tile::Tile(SDL_Texture* tileset, Vector2 size, Vector2 tilesetPosition, Vector2 position) :
	tileset(tileset),
	size(size),
	tilesetPosition(tilesetPosition),
	position(Vector2(position.x * globals::SPRITE_SCALE, position.y * globals::SPRITE_SCALE)) 
{}

void Tile::update(int elapsedTime) {}

void Tile::draw(Graphics &graphics) 
{
	// Where we're going to draw it to the screen
	SDL_Rect destRect = { this->position.x, this->position.y, this->size.x * globals::SPRITE_SCALE, this->size.y * globals::SPRITE_SCALE };

	// Where we're getting the source images from on the tileset/sheet 
	SDL_Rect sourceRect = { this->tilesetPosition.x, this->tilesetPosition.y, this->size.x, this->size.y };

	graphics.blitSurface(this->tileset, &sourceRect, &destRect);
}
