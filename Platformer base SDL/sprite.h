/* Sprite class
* Holds all information for individual sprites
*/

#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>
#include <string>

class Graphics;

class Sprite {

public:
	Sprite();
	
	/* This is the constructor we'll be using most often
	 * sourceX is the x position on the spritesheet, sourceY is the y position on the spritesheet
	 * width and height are the width and height of the sprite we're grabbing  
	 * posX and posY is their spawn point on screen
	 */
	Sprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, float posX, float posY);

	virtual ~Sprite();
	virtual void update();	//Virtual because we'll have some stuff, but it will be overridden in animated sprites
	void draw(Graphics &graphics, int x, int y);

protected:
	SDL_Rect sourceRect;		//Where on the spritesheet to get the sprite from
	SDL_Texture* spriteSheet;	//The spritesheet we're getting the sprite from
	float x, y;					//x and y position
private:

};

#endif
