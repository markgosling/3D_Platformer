#ifndef PYRAMIDASSET_H
#define PYRAMIDASSET_H

#include <vector>
#include <GL/gl.h>
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
	PyramidAsset(float x_position, float y_position, float z_position);
	~PyramidAsset();
};

#endif // PYRAMIDASSET_H
