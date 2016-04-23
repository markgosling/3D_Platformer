#include <memory>
#include "GameLoop.h"



/**
 * Main entry point to the program which is used to start the main
 * game loop.
 *
 * @param argc - Integer - Arguments passed the game at run time.
 * @param argv - char - Arguments passed to the game at run time.
 */
int main(int argc, char ** argv) {

	std::shared_ptr<GameLoop> game_loop = std::shared_ptr<GameLoop>();
	game_loop->run();


}
