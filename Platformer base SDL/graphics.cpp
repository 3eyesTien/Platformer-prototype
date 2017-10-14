/*Graphics class
 *Holds all info dealing with graphics for the game
 */
#include "graphics.h"
#include "globals.h"


Graphics::Graphics() 
{
	SDL_CreateWindowAndRenderer(globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, 0, &this->window, &this->renderer);
	if (this->window == NULL)
	{
		printf("\nError, window is NULL\n");
	}
	SDL_SetWindowTitle(this->window, "Platformer");
}

Graphics::~Graphics()
{
	SDL_DestroyWindow(this->window);
	SDL_DestroyRenderer(this->renderer);	//Remember to destroy pointer to prevent memory leaks.
}

SDL_Surface* Graphics::loadImage(const std::string &filePath)
{
	if (this->spriteSheets.count(filePath) == 0)	//Check if the spritesheet hasn't been loaded yet
	{
		this->spriteSheets[filePath] = IMG_Load(filePath.c_str());
	}
	return this->spriteSheets[filePath];
}

void Graphics::blitSurface(SDL_Texture* texture, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle)
{
	SDL_RenderCopy(this->renderer, texture, sourceRectangle, destinationRectangle);
}

void Graphics::blitSurface_MirroredHoriz(SDL_Texture* texture, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle)
{
	SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
	SDL_RenderCopyEx(this->renderer, texture, sourceRectangle, destinationRectangle, NULL, NULL, flip);
}

void Graphics::flip()
{
	SDL_RenderPresent(this->renderer);
}

void Graphics::clear()
{
	SDL_RenderClear(this->renderer);
}

SDL_Renderer* Graphics::getRenderer() const
{
	return this->renderer;
}