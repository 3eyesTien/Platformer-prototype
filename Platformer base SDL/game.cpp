/*Game class
* This class will hold all information for our main game loop
*/

#include "game.h"
#include "graphics.h"
#include "input.h"

#include <SDL.h>
#include <algorithm>


namespace {
	const int FPS = 50;							//Cave Story ran at 50 fps
	const int MAX_FRAME_TIME = 5 * 1000 / FPS;	//The max amount of time a frame is allowed to last.
}
Game::Game() 
{
	
	SDL_Init(SDL_INIT_EVERYTHING);
	this->gameLoop();
}

Game::~Game() 
{

}

void Game::gameLoop() 
{

	Graphics graphics;
	Input input;
	SDL_Event event;

	this->player = Player(graphics, 100, 100);
	this->level = Level("level1", Vector2(100, 100), graphics);

	/*Gets number of milliseconds since the SDL library was initialized.
	 *This is our clock that we use to reference the change in time (delta time)
	 *This will be set every frame
	 */
	int LAST_UPDATE_TIME = SDL_GetTicks();		

	//Start the game loop
	while (true)
	{
		input.beginNewFrame();					//First thing to do for every frame
		if (SDL_PollEvent(&event))				//Listen for an event every frame 
		{
			if (event.type == SDL_KEYDOWN)		//Note when is key is pressed
			{
				if (event.key.repeat == 0)		//This makes sure you're not holding down a key.  We don't want this if this was a repeat
				{
					input.keyDownEvent(event);
				}
			}
			else if (event.type == SDL_KEYUP)	//Note when a key is released
			{
				input.keyUpEvent(event);
			}
			else if (event.type == SDL_QUIT)
			{
				return;
			}
		}
		if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE) == true)
		{
			return;
		}
		else if (input.isKeyHeld(SDL_SCANCODE_LEFT) == true) 
		{
			this->player.moveLeft();
		}

		else if (input.isKeyHeld(SDL_SCANCODE_RIGHT) == true) 
		{
			this->player.moveRight();
		}

		if (!input.isKeyHeld(SDL_SCANCODE_LEFT) && !input.isKeyHeld(SDL_SCANCODE_RIGHT))
		{
			this->player.stopMoving();
		}

		const int CURRENT_TIME_MS = SDL_GetTicks();
		//This LAST_UPDATE_TIME subtracted from CURRENT_TIME_MS will show how long it took to process the frame in the game loop
		int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;
		
		//Do the frame updates to the game
		//Scales the timing so that physics will work the same no matter the speed of your computer
		this->update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME));

		LAST_UPDATE_TIME = CURRENT_TIME_MS;

		this->draw(graphics);
	} 
}

void Game::draw(Graphics &graphics) 
{
	graphics.clear();

	this->level.draw(graphics);
	this->player.draw(graphics);			//Draw onto the background surface/buffer

	graphics.flip();						//flip() the surface/buffer to reveal the drawn frame
}

void Game::update(float elapsedTime) 
{
	this->player.update(elapsedTime);
	this->level.update(elapsedTime);
}