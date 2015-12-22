#ifndef PYRAMIDASSET_H
#define PYRAMIDASSET_H

#include <vector>

#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "GameAsset.h"

using namespace std;

class PyramidAsset : public GameAsset {
 public:
  PyramidAsset(float x_position, float y_position, float z_position);
  ~PyramidAsset();
};

#endif // PYRAMIDASSET_H
