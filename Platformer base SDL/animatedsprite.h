/* AnimatedSprite class
 * Contains logic for animating sprites 
 */

#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "globals.h"
#include "sprite.h"

#include <map>
#include <string>
#include <vector>

class Graphics;

class AnimatedSprite : public Sprite
{
public:
	AnimatedSprite();
	AnimatedSprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, 
		float posX, float posY, float timeToUpdate);

	/* void playAnimation
	 * Plays the animation provided if it's not already playing
	 */
	void playAnimation(std::string animation, bool once = false);

	/* void update
	 * Uses the elapsedTime as a timer to know when to change to the next sprite
	 */
	void update(int elapsedTime);

	void draw(Graphics &graphics, int x, int y, std::string facing);

protected:	
	double timeToUpdate;
	bool currentAnimationOnce;
	std::string currentAnimation;
	
	// This is how we add animations to our list of animations
	// int frames = # of frames in the animation
	// int x, int y is where on the spritesheet the animation starts
	void addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset);

	/* void resetAnimations
	 * Resets all animations associated with this sprite
	 */
	void resetAnimations();

	/* void stopAnimation
	 * Stops the current animation
	 */
	void stopAnimation();

	/* void setVisible
	 * Changes the visibility of the sprite
	 */
	void setVisible(bool visible);

	/* void animationDone
	 * Logic that happens when an animation ends
	 */
	virtual void animationDone(std::string currentAnimation) = 0;	//Pure virtual function

	/* virtual void setupAnimations
	* A required function that sets up all animations for a sprite
	*/
	virtual void setupAnimations() = 0;

	/* void reverseAnimation
	* Take an animation and reverse the frames to make it a seperate animation
	*/
	void reverseAnimation(std::string name, std::string animationName);

private:
	// Map that contains a list of rectangles (SDL_Rect)
	std::map<std::string, std::vector<SDL_Rect> > animations;
	std::map<std::string, Vector2> offsets;

	int frameIndex;	// Which frame in the animation we're at
	double  timeElapsed;
	bool visible;
};

#endif

