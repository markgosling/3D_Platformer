#ifndef CUBEASSET_H
#define CUBEASSET_H

#include <vector>

#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "GameAsset.h"

class CubeAsset : public GameAsset {
 public:
  CubeAsset(float x_position, float y_position, float z_position);
  ~CubeAsset();
  void Draw(GLuint);

 private:


};

#endif // CUBEASSET_H


