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

	glm::vec3 camera_position;

	glm::vec3 direction;
	glm::vec3 right;
	glm::vec3 up;

	float horizontal_angle;
	float vertical_angle;

	float mouse_delta_x;
	float mouse_delta_y;

	float camera_movement_speed;

};




#endif /* SRC_CAMERA_H_ */
