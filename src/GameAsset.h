#ifndef GAMEASSET_H
#define GAMEASSET_H

#include <iostream>

#include <GL/gl.h>
#include <vector>

#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class GameAsset {

 public:
  enum AssetType {CUBE, PYRAMID};
  void Draw(GLuint);
  AssetType GetAssetType();
  bool DetectXCollision(float camera_x_position);
  bool DetectYCollision(float camera_y_position);
  bool DetectZCollision(float camera_z_position);
  bool DetectCollision(float camera_x_position, float camera_y_position, float camera_z_position);


 protected:
  AssetType assetType;
  GLuint element_buffer_length;
  GLuint vertex_buffer_token, element_buffer_token;
  float width;
  float depth;
  float height;
  float x_position;
  float y_position;
  float z_position;

 private:
  void checkError(std::string file, int line);


};

#endif
