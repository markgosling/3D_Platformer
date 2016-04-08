#ifndef CUBEASSET_H
#define CUBEASSET_H

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

/*
 * CubeAsset extends GameAsset with variables and methods which
 * are used to draw a cube object on screen. It also stores the
 * bounding box for the cube, sets the asset type and passes the
 * vertices to the GPU.
 */
class CubeAsset : public GameAsset {
public:
	CubeAsset(float x_position, float y_position, float z_position, float scale,
			float x_rotation, float y_rotation, float z_rotation);
	~CubeAsset();
	void Draw(GLuint);

private:
};

#endif // CUBEASSET_H


