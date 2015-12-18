#define GLEW_STATIC // Easier debugging
#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <memory>

#include <boost/program_options.hpp>

#define RUN_GRAPHICS_DISPLAY 0x00;

#include "common.h"
#include "GameWorld.h"

using namespace std;

/*
 * SDL timers run in separate threads.  In the timer thread
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

struct SDLWindowDeleter {
  inline void operator()(SDL_Window* window) {
    SDL_DestroyWindow(window);
  }
};

shared_ptr<SDL_Window> InitWorld() {
  Uint32 width = 640;
  Uint32 height = 480;
  SDL_Window * _window;
  shared_ptr<SDL_Window> window;

  // Glew will later ensure that OpenGL 3 *is* supported
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

  // Do double buffering in GL
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

  // Initialise SDL - when using C/C++ it's common to have to
  // initialise libraries by calling a function within them.
  if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER)<0) {
    cout << "Failed to initialise SDL: " << SDL_GetError() << endl;
    return nullptr;
  }

  // When we close a window quit the SDL application
  atexit(SDL_Quit);

  // Create a new window with an OpenGL surface
  _window = SDL_CreateWindow("Shader Example"
                             , SDL_WINDOWPOS_CENTERED
                             , SDL_WINDOWPOS_CENTERED
                             , width
                             , height
                             , SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
  if (!_window) {
    cout << "Failed to create SDL window: " << SDL_GetError() << endl;
    return nullptr;
  }

  SDL_GLContext glContext = SDL_GL_CreateContext(_window);
  if (!glContext) {
    cout << "Failed to create OpenGL context: " << SDL_GetError() << endl;
    return nullptr;
  }

  // Initialise GLEW - an easy way to ensure OpenGl 3.0+
  // The *must* be done after we have set the video mode - otherwise we have no
  // OpenGL context to test.
  glewInit();
  if (!glewIsSupported("GL_VERSION_3_0")) {
    cerr << "OpenGL 3.0 not available" << endl;
    return nullptr;
  }

  // OpenGL settings
  glDisable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  window.reset(_window, SDL_DestroyWindow);
  return window;
}


void Draw(const shared_ptr<SDL_Window> window, const shared_ptr<GameWorld> game_world) {

  //Set the background colour to a light blue.
  glClearColor(0.6f, 0.6f, 0.90f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  game_world->Draw();

  // Don't forget to swap the buffers
  SDL_GL_SwapWindow(window.get());
}

/**
 * Main function which starts the game, initialises the game
 * window and other objects, creates a timer and handles the
 * SDL event loop.
 *
 * @param argc - Integer - Arguments passed the game at run time.
 * @param argv - char - Arguments passed to the game at run time.
 */
int main(int argc, char ** argv) {

  Uint32 delay = 1000/60; // in milliseconds

  //Calls the method to initialise SDL and create the window.
  auto window = InitWorld();

  auto game_world = make_shared<GameWorld>();

  int mouse_x;
  int mouse_y;

  const Uint8 *keyboard_state;

  InputDirection input_direction = NONE;

  if(!window) {
    SDL_Quit();
  }

  // Call the function "tick" every delay milliseconds
  SDL_AddTimer(delay, tick, NULL);

  //Let the window grab and hide the mouse pointer.
  //https://wiki.libsdl.org/SDL_SetRelativeMouseMode
  SDL_SetRelativeMouseMode(SDL_TRUE);

  // Add the main event loop
  SDL_Event event;
  while (SDL_WaitEvent(&event)) {

    switch (event.type) {
    case SDL_QUIT:
      SDL_Quit();
      break;
    case SDL_USEREVENT:
    {
    	//SDL mouse event code adapted from example at:
    	//https://wiki.libsdl.org/SDL_GetRelativeMouseState
        SDL_GetRelativeMouseState(&mouse_x, &mouse_y);

        //Keyboard presses implemented as per the example on
    	//https://wiki.libsdl.org/SDL_GetKeyboardState
    	keyboard_state = SDL_GetKeyboardState(NULL);
    	if(keyboard_state[SDL_SCANCODE_A]){
    		input_direction = LEFT;
    	}else if(keyboard_state[SDL_SCANCODE_S]){
    		input_direction = DOWN;
    	}else if(keyboard_state[SDL_SCANCODE_D]){
    		input_direction = RIGHT;
    	}else if(keyboard_state[SDL_SCANCODE_W]){
    		input_direction = UP;
    	}else{
    		input_direction = NONE;
    	}

      game_world->UpdateCameraPosition(input_direction, mouse_x, mouse_y);
      Draw(window, game_world);
      break;
    }

    default:
      break;
    }

  }
}
