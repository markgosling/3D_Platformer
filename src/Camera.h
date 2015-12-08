#include <glm/ext.hpp>
#include "common.h"

/*
 * Camera.h
 *
 *  Created on: 8 Dec 2015
 *      Author: mark
 */

#ifndef SRC_CAMERA_H_
#define SRC_CAMERA_H_
class Camera{

public:
	Camera();
	glm::mat4 UpdateCameraPosition(InputDirection inputDirection, int mouse_x, int mouse_y);

private:

	float camera_x_position;
	float camera_y_position;
	float camera_z_position;

	float horizontal_angle;
	float vertical_angle;


};




#endif /* SRC_CAMERA_H_ */
