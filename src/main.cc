#include <memory>
#include "GameLoop.h"

/**
 * @file main.cc
 * @version 1.0
 *
 * @section Description
 *
 * This file contains the main entry point of the program. When loaded it
 * creates an instance of GameLoop and calls the Run() method to start the game.
 *
 * This project is based off original code written by Aidan Delaney which
 * is available on github at https://github.com/AidanDelaney/glex.
 */


/**
 * Main entry point to the program which is used to start the main
 * game loop.
 *
 * @param argc - Integer - Arguments passed the game at run time.
 * @param argv - char - Arguments passed to the game at run time.
 */
int main(int argc, char ** argv) {

	std::shared_ptr<GameLoop> game_loop = std::shared_ptr<GameLoop>();
	game_loop->Run();
}
