#define GLEW_STATIC // Easier debugging
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <memory>


//Code from http://stackoverflow.com/questions/3907818/opengl-headers-for-os-x-linux.
//Allows the code to be compiled for linux and osx devices (which have the opengl libaries in a different location to linux).
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#ifdef _WIN32
  #include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <boost/program_options.hpp>
#include "common.h"
#include "GameWorld.h"
#include "GameLoop.h"

#define RUN_GRAPHICS_DISPLAY 0x00;

/**
 * @file GameLoop.cc
 * @version 1.0
 *
 * @section Description
 *
 * The GameLoop class contains the main game loop for the program. It also initialises
 * the SDL window and openGL settings. It also runs a SDL event loop
 * which responds to timer and user events to handle input and to call
 * methods which update the state of the game.
 */


/** SDL timers run in separate threads.  In the timer thread
* push an event onto the event queue.  This event signifies
* to call display() from the thread in which the OpenGL
* context was created.
*/
Uint32 tick(Uint32 interval, void *param) {
	SDL_Event event;
	event.type = SDL_USEREVENT;
	event.user.code = RUN_GRAPHICS_DISPLAY;
	event.user.data1 = 0;
	event.user.data2 = 0;
	SDL_PushEvent(&event);
	return interval;
}

//Structure used to destroy the game window.
struct SDLWindowDeleter {
	inline void operator()(SDL_Window* window) {
		SDL_DestroyWindow(window);
	}
};

/**
 * InitWorld method that creates the game window with an openGL context and
 * specifies the openGL settings.
 *
 * @return a shared pointer to the game window.
 */
std::shared_ptr<SDL_Window> GameLoop::InitWorld() {
	Uint32 width = 640;
	Uint32 height = 480;
	SDL_Window * _window;
	std::shared_ptr<SDL_Window> window;

	//Glew will later ensure that OpenGL 3 *is* supported.
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	//Do double buffering in GL.
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	//Initialise SDL - when using C/C++ it's common to have to
	//initialise libraries by calling a function within them.
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER)<0) {
		std::cout << "Failed to initialise SDL: " << SDL_GetError() << std::endl;
		return nullptr;
	}

	//When we close a window quit the SDL application.
	atexit(SDL_Quit);

	//Create a new window with an OpenGL surface.
	_window = SDL_CreateWindow("3D Platformer"
			, SDL_WINDOWPOS_CENTERED
			, SDL_WINDOWPOS_CENTERED
			, width
			, height
			, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (!_window) {
		std::cout << "Failed to create SDL window: " << SDL_GetError() << std::endl;
		return nullptr;
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	if (!glContext) {
		std::cout << "Failed to create OpenGL context: " << SDL_GetError() << std::endl;
		return nullptr;
	}

	//Initialise GLEW - an easy way to ensure OpenGl 3.0+
	//This *must* be done after we have set the video mode - otherwise we have no
	//OpenGL context to test.
	glewInit();
	if (!glewIsSupported("GL_VERSION_3_0")) {
		std::cerr << "OpenGL 3.0 not available" << std::endl;
		return nullptr;
	}

	//OpenGL settings.
	glDisable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	window.reset(_window, SDL_DestroyWindow);
	return window;
}

/**
 * Method 'Draw' that clears the depth buffer and sets the background
 * colour of the screen, calls the method to draw the entire game world
 * and then swaps the window buffers.
 *
 * @param window - shared_ptr - A shared pointer to the game window.
 * @param game_world - shared_ptr - A shared pointer to the instance of game_world.
 */
void GameLoop::Draw(const std::shared_ptr<SDL_Window> &window, const std::shared_ptr<GameWorld> &game_world) {


	//Set the background colour to a light blue.
	glClearColor(0.6f, 0.6f, 0.90f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	//Call the method in game_world to update the entire screen.
	game_world->Draw();

	//Swap the window buffers.
	SDL_GL_SwapWindow(window.get());
}

//Fix to prevent WinMain errors when building in Cygwin as shown here: http://stackoverflow.com/questions/29846946/undefined-reference-to-winmain-when-using-cygwin-sdl2-and-netbeans
#ifdef main
# undef main
#endif

/**
 * Main game loop which runs the game, initialises the game
 * window and other objects, creates a timer and handles the
 * SDL event loop.
 */
void GameLoop::Run() {

	//Set the timer delay (currently refreshes the screen at 60fps).
	Uint32 delay = 1000/60; // in milliseconds

	//Calls the method to initialise SDL and create the window.
	auto window = InitWorld();

	//Create a shared pointer to 'GameWorld'.
	auto game_world = std::make_shared<GameWorld>();

	//Create variables to store the mouse coordinates.
	int mouse_x;
	int mouse_y;

	//Create a variable to store the keyboard state.
	const Uint8 *keyboard_state;

	//Enum variable used to store the input direction being entered on the
	//keyboard, initialised to 'NONE;'.
	InputDirection input_direction = NONE;

	//Quit SDL if the window is closed.
	if(!window) {
		SDL_Quit();
	}

	//Call the function "tick" every delay milliseconds.
	SDL_AddTimer(delay, tick, NULL);

	//Let the window grab and hide the mouse pointer.
	//Code snippet found on https://wiki.libsdl.org/SDL_SetRelativeMouseMode.
	SDL_SetRelativeMouseMode(SDL_TRUE);

	//Add the main event loop.
	SDL_Event event;
	while (SDL_WaitEvent(&event)) {

		//Respond depending on the event received.
		switch (event.type) {
		case SDL_QUIT:
			SDL_Quit();
			break;
		case SDL_USEREVENT: //User events are added by the timer.
		{
			//Get the mouse x and y coordinates.
			//SDL mouse event code adapted from example at:
			//https://wiki.libsdl.org/SDL_GetRelativeMouseState
			SDL_GetRelativeMouseState(&mouse_x, &mouse_y);

			//Detect key presses and respond to them by setting the direction state.
			//Keyboard presses implemented as per the example on https://wiki.libsdl.org/SDL_GetKeyboardState
			keyboard_state = SDL_GetKeyboardState(NULL);
			if(keyboard_state[SDL_SCANCODE_A]){
				input_direction = LEFT;
			}else if(keyboard_state[SDL_SCANCODE_S]){
				input_direction = DOWN;
			}else if(keyboard_state[SDL_SCANCODE_D]){
				input_direction = RIGHT;
			}else if(keyboard_state[SDL_SCANCODE_W]){
				input_direction = UP;
			}else if(keyboard_state[SDL_SCANCODE_ESCAPE]){
				SDL_SetRelativeMouseMode(SDL_FALSE);
			}else{
				input_direction = NONE;
			}

			//If the left button is clicked, let the window grab the mouse.
			if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
				SDL_SetRelativeMouseMode(SDL_TRUE);
			}

			//Only update the game state if the mouse is captured by the window.
			if(SDL_GetRelativeMouseMode() == true){
				//Call the method in 'game_world' to update the game state based on the directional input,
				//entered by the user and the mouse x and y coordinates.
				game_world->UpdateCameraPosition(input_direction, mouse_x, mouse_y);

				//Call the 'Draw' method to show the updated game state on screen.
				Draw(window, game_world);
			}

			break;
		}

		default:
			break;
		}
	}
}

