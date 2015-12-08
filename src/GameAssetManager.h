#ifndef GAMEASSETMANAGER_H
#define GAMEASSETMANAGER_H

#include <memory>
#include <vector>
#include <string>
#include <utility>
#include <fstream>
#include <iostream>
#include <vector>
#include <GL/gl.h>
#include <glm/ext.hpp>

#include "common.h"
#include "GameAsset.h"

/**
 * GameAssetManager is a container for GameAssets.  It also provides utility
 * functions to to create a simple OpenGL program that can be used to draw a
 * simple GameAsset.
 */
class GameAssetManager {
 public:
  explicit GameAssetManager(ApplicationMode); // constructor
  virtual ~GameAssetManager();
  GameAssetManager(GameAssetManager const&); // copy constructor
  GameAssetManager(GameAssetManager const&&); // move constructor
  void operator=(GameAssetManager const&); // assignment
  void AddAsset(std::shared_ptr<GameAsset>, int x, int y, int z);
  void Draw();
  GLuint CreateGLProgram(std::string &, std::string &);

  //Method which accepts player directional inputs from main.cc
  //and updates the camera matrix accordingly.
  void UpdateCameraPosition(InputDirection, int mouse_x, int mouse_y);

 private:
  GLuint CreateGLESShader(GLenum, std::string &);
  // As this is private and we're writing to the GPU, we will use raw pointers.
  std::pair<GLchar *, GLint>  ReadShader(std::string &);

  // The internal scene graph is a simple list.
  std::vector<std::shared_ptr<GameAsset>> draw_list;
  GLuint program_token;

  //Uniform variables used to communicate with the shaders.
  GLuint camera_x_position;
  GLuint camera_y_position;
  GLuint camera_z_position;
  GLuint shape_red_value;
  GLuint shape_green_value;
  GLuint shape_blue_value;
  GLuint translate_matrix_link;
  GLuint view_matrix_link;

  glm::mat4 translate_matrix; //The position of the model.
  glm::mat4 view_matrix;	//The position of the camera.

  float player_x_position;
  float player_z_position;

  float horizontal_angle;
  float vertical_angle;

  std::vector<std::vector<std::vector<std::shared_ptr<GameAsset>>>> world_array;

};

#endif // GAMEASSETMANAGER_H
