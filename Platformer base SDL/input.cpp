/*Input class
*This class will keep track of the keyboard state
*/

#include "input.h"

/*This function gets called at the beginning of each new frame
 *to reset the keys that are no longer relevant
 */
void Input::beginNewFrame() {

	//Clear out keys that don't matter in the next frame
	this->pressedKeys.clear();	
	this->releasedKeys.clear();
}

//This gets called when a key is pressed
void Input::keyDownEvent(const SDL_Event& event) {
	
	//Index the scancode key to the pressedKeys map by setting the bool to true
	this->pressedKeys[event.key.keysym.scancode] = true;	
	
	//Since the key is pressed, it is technically held too.
	this->heldKeys[event.key.keysym.scancode] = true;
}

//This is called when a key is released
void Input::keyUpEvent(const SDL_Event& event) {

	this->releasedKeys[event.key.keysym.scancode] = false;
	
	//Release heldKeys map
	this->heldKeys[event.key.keysym.scancode] = false;
}

//Check if a certain key was pressed during the current frame
bool Input::wasKeyPressed(SDL_Scancode key) {

	return this->pressedKeys[key];
}

//Check if a certain key was released during the current frame
bool Input::wasKeyReleased(SDL_Scancode key) {

	return this->releasedKeys[key];
}

//Check if a certain key is currently being held
bool Input::isKeyHeld(SDL_Scancode key) {
	
	return this->heldKeys[key];
}