/*Input class
*This class will keep track of the keyboard state
*/

#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
#include <map>	//map from STL library.  //Holds two types of information together

class Input {

public:
	void beginNewFrame();
	void keyUpEvent(const SDL_Event& event);
	void keyDownEvent(const SDL_Event& event);

	bool wasKeyPressed(SDL_Scancode key);
	bool wasKeyReleased(SDL_Scancode key);
	bool isKeyHeld(SDL_Scancode key);

private:
	std::map<SDL_Scancode, bool> heldKeys; //Contains what keys are currently being held
	std::map<SDL_Scancode, bool> pressedKeys;
	std::map<SDL_Scancode, bool> releasedKeys;
};

#endif
