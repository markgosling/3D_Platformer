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
  bool DetectXCollision();
  bool DetectYCollision();


 protected:
  AssetType assetType;
  GLuint element_buffer_length;
  GLuint vertex_buffer_token, element_buffer_token;

 private:
  void checkError(std::string file, int line);

};

#endif
