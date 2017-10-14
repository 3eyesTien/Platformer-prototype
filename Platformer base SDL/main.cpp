/*Main file
Main will be used as the entry point to the game
*/

#include "game.h"

#undef main	//This gets rid of this error for some reason: Error	LNK2019	unresolved external symbol _SDL_main referenced in function _main_utf8	
			//Try running the program again without it to see if it still causes a break at compile time


int main(int argc, const char* argv[]) {
	Game game;
	return 0;
}