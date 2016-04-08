#ifndef PYRAMIDASSET_H
#define PYRAMIDASSET_H

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#ifdef _WIN32
  #include <windows.h>
#endif
#include <GL/gl.h>
#endif

#include <vector>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "GameAsset.h"

/**
 * PyramidAsset extends GameAsset with variables and methods which
 * are used to draw a pyramid object on screen. It also stores the
 * bounding box for the pyramid, sets the asset type and passes the
 * vertices to the GPU.
 */
class PyramidAsset : public GameAsset {
public:
	PyramidAsset(float x_position, float y_position, float z_position, float scale,
			float x_rotation, float y_rotation, float z_rotation);
	~PyramidAsset();
};

#endif // PYRAMIDASSET_H
