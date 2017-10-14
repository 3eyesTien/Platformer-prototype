/*Graphics class
*Holds all info dealing with graphics for the game
*/

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <map>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

/*Forward declaration of SDL_Window and Render since they're pointers and I don't want to #include SDL here.
  This allows us to declare these variable names for pointer names even though we haven't included them.
  SDL will be #included in an implementation file.*/
struct SDL_Window;
struct SDL_Renderer;

class Graphics {
public:
	Graphics();
	~Graphics();

	/* loadImage 
	 * Loads an image into the spriteSheets map if it doesn't already exist
	 * Returns the image from the map regardless of whether or not it was just loaded
	 */
	struct SDL_Surface* loadImage(const std::string &filePath);

	/* blitSurface
	 * Draws a texture to a certain part of the screen
	 * sourceRectangle is the rectangle that we're grabbing from the spritesheet
	 * destinationRectangle is where we're going to draw sourceRectangle onto the screen
	 */
	void blitSurface(struct SDL_Texture* source, struct SDL_Rect* sourceRectangle, struct SDL_Rect* destinationRectangle);

	/* blitSurface_left
	 * Draws a texture to a certain part of the screen, but mirrored horizontally
	 * Only characters and enemies should ever need this... I think
	 */
	void Graphics::blitSurface_MirroredHoriz(SDL_Texture* texture, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle);

	/* flip 
	 * Renders everything to the screen by flipping the buffered images after the frame has been drawn on them
	 */
	void flip();

	/* clear
	 * Clears the screen
	 */
	void clear();

	//At the beginning of every frame order is clear() screen, blitSurface(), flip() buffer surface to draw to screen

	/* getRenderer()
	 * returns the renderer
	 */
	SDL_Renderer* getRenderer() const;
private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	/* spriteSheets
	 * This map will hold, in memory in our graphics object, every spritesheet we've loaded into the game
	 * This way we only need to load things once when the game is started*/
	std::map<std::string, SDL_Surface*> spriteSheets;
};
#endif
