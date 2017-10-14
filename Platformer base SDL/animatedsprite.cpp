/* AnimatedSprite class
* Contains logic for animating sprites
*/

#include "animatedsprite.h"
#include "graphics.h"

AnimatedSprite::AnimatedSprite() {}

AnimatedSprite::AnimatedSprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY,
	int width, int height, float posX, float posY, float timeToUpdate) :
	Sprite(graphics, filePath, sourceX, sourceY, width, height, posX, posY),
	frameIndex(0),
	timeToUpdate(timeToUpdate),
	visible(true),
	currentAnimationOnce(false),
	currentAnimation(""),
	timeElapsed(0)	// Initialize at 0. Sometimes when you don't it starts as a ridiculously high negative number
{}

void AnimatedSprite::addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset)
{
	std::vector<SDL_Rect> rectangles;	//Temp var to hold rectangles that have the sprites facing right
	
	for (int i = 0; i < frames; i++)
	{
		SDL_Rect newRect = { (i + x) * width, y, width, height };
		
		rectangles.push_back(newRect);
	}

	this->animations.insert(std::pair<std::string, std::vector<SDL_Rect> >(name, rectangles));	// Pass in name and rectangles into pair map values respectively
	this->offsets.insert(std::pair<std::string, Vector2>(name, offset));
}

void AnimatedSprite::reverseAnimation(std::string animatedSprite, std::string reversedAnimation)
{
	std::vector<SDL_Rect> rectangles, rectReverse;
	rectangles = animations.at(animatedSprite);	//Copy values of animation rectangles from the animation map with the key (name) entered

	for (int i = rectangles.size()-1; i >= 0; i--) {
		SDL_Rect newRect = rectangles.at(i);
		rectReverse.push_back(newRect);
	}
	this->animations.insert(std::pair<std::string, std::vector<SDL_Rect> >(reversedAnimation, rectReverse));
}

void AnimatedSprite::resetAnimations()
{
	this->animations.clear();
	this->offsets.clear();
}

void AnimatedSprite::playAnimation(std::string animation, bool once)
{

	this->currentAnimationOnce = once;
	if (this->currentAnimation != animation)	// Make sure the one that's about to be played isn't the once currently playing
	{
		this->currentAnimation = animation;
		this->frameIndex = 0;
	}
}

void AnimatedSprite::setVisible(bool visible)
{
	this->visible = visible;
}

void AnimatedSprite::stopAnimation()
{
	this->frameIndex = 0;
	this->animationDone(this->currentAnimation);
}

void AnimatedSprite::update(int elapsedTime)
{
	Sprite::update();

	this->timeElapsed += elapsedTime;
	if (this->timeElapsed > this->timeToUpdate)
	{
		this->timeElapsed -= this->timeToUpdate;

		if (this->frameIndex < this->animations[this->currentAnimation].size() - 1)	// If this isn't the last frame in the animation
		{
			this->frameIndex++;	//Continue to next frame in animation
		} 
		else
		{
			if (this->currentAnimationOnce == true)	// If the current animation has played out once
			{
				this->setVisible(false);
			}
			this->frameIndex = 1;	// Set it to 1 here because the first frame is for transition from idle.
									// I need to think about another way
			this->animationDone(this->currentAnimation);
		}
	}
}

void AnimatedSprite::draw(Graphics &graphics, int x, int y, std::string facing)
{
	if (this->visible)
	{
		if(facing == "right")
		{
			SDL_Rect destinationRectangle;
			destinationRectangle.x = x + this->offsets[this->currentAnimation].x;
			destinationRectangle.y = y + this->offsets[this->currentAnimation].y;
			destinationRectangle.w = this->sourceRect.w * globals::SPRITE_SCALE;
			destinationRectangle.h = this->sourceRect.h * globals::SPRITE_SCALE;

			SDL_Rect sourceRect = this->animations[this->currentAnimation][this->frameIndex];
			graphics.blitSurface(this->spriteSheet, &sourceRect, &destinationRectangle);
		}
		else if (facing == "left")
		{
			SDL_Rect destinationRectangle;
			destinationRectangle.x = x + this->offsets[this->currentAnimation].x;
			destinationRectangle.y = y + this->offsets[this->currentAnimation].y;
			destinationRectangle.w = this->sourceRect.w * globals::SPRITE_SCALE;
			destinationRectangle.h = this->sourceRect.h * globals::SPRITE_SCALE;

			SDL_Rect sourceRect = this->animations[this->currentAnimation][this->frameIndex];
			graphics.blitSurface_MirroredHoriz(this->spriteSheet, &sourceRect, &destinationRectangle);
		}
	}
}
