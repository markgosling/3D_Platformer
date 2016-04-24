#include <SDL2/SDL.h>
#include <memory>
#include "GameWorld.h"

/*
 * GameLoop.h
 *
 *  Created on: 23 Apr 2016
 *      Author: mark
 *
 * The GameLoop class contains the main game loop for the program. It also initialises
 * the SDL window and openGL settings. It also runs a SDL event loop
 * which responds to timer and user events to handle input and to call
 * methods which update the state of the game.
 */

#ifndef SRC_GAMELOOP_H_
#define SRC_GAMELOOP_H_

class GameLoop{

public:
	std::shared_ptr<SDL_Window> InitWorld();
	void Draw(const std::shared_ptr<SDL_Window> &window, const std::shared_ptr<GameWorld> &game_world);
	void Run();
};



#endif /* SRC_GAMELOOP_H_ */
