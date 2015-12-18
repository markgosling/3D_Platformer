#include "Camera.h"
#include <glm/ext.hpp>
#include <iostream>

/*
 * Camera.cc
 *
 *  Created on: 8 Dec 2015
 *      Author: mark
 */


Camera::Camera(){
	  camera_x_position = -3.0f;
	  camera_y_position = 1.5f;
	  camera_z_position = 0.0f;

	  camera_position = glm::vec3(-3.0f, 1.5f, 0.0f);
	  direction = glm::vec3(0,0,0);
	  right = glm::vec3(0,0,0);
	  up = glm::vec3(0,0,0);

	  horizontal_angle = 0;
	  vertical_angle = 0;

	  mouse_delta_x = 0;
	  mouse_delta_y = 0;

	  camera_movement_speed = 0.1;

}

glm::mat4 Camera::UpdateCameraPosition(InputDirection inputDirection, int mouse_x, int mouse_y){

	//The camera matrix code and code to look around were based on and adapted from
	//tutorials found at the following links:
	//http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/
	//http://www.opengl-tutorial.org/beginners-tutorials/tutorial-6-keyboard-and-mouse/

	//Get the relative mouse delta position (passed to the method as a parameter) and invert it.
	mouse_delta_x = -mouse_x;
	mouse_delta_y = -mouse_y;

    //Add the delta value onto the angle values and slow the movement speed down by
	//multiplying the delta by a value < 1.
	horizontal_angle += 0.01 * mouse_delta_x;

	//Restrict the vertical viewing angle to prevent the camera from flipping upside down.
	if((vertical_angle + (0.01 * mouse_delta_y)) < 1 && (vertical_angle + (0.01 * mouse_delta_y)) > -1 ){
		vertical_angle += 0.01 * mouse_delta_y;
	}

	//Calculate the new direction to look at.
	direction = glm::vec3(
			cos(vertical_angle) * sin(horizontal_angle),
			sin(vertical_angle),
			cos(vertical_angle) * cos(horizontal_angle));

	//Create a angle to the right of the right of the horizontal angle.
	right = glm::vec3(
			sin(horizontal_angle - 3.14/2.0f),
			0,
			cos(horizontal_angle - 3.14/2.0f));

	//Create an angle directly up and between the forward and right angles.
	up = glm::cross(right, direction);


	if(inputDirection == UP){

	  //camera_z_position += 0.1;
	  // cout << "up " << player_z_position << endl;
	  //camera_position += direction * camera_movement_speed;
	  camera_position += glm::vec3(cos(vertical_angle) * sin(horizontal_angle),
							       0,
								   cos(vertical_angle) * cos(horizontal_angle))
								   * camera_movement_speed;
	}else if(inputDirection == DOWN){
	  //camera_z_position -= 0.1;
	  //cout << "down " << player_z_position << endl;
	  //camera_position -= direction * camera_movement_speed;
	  camera_position -= glm::vec3(cos(vertical_angle) * sin(horizontal_angle),
								   0,
								   cos(vertical_angle) * cos(horizontal_angle))
                                   * camera_movement_speed;
	}else if(inputDirection == LEFT){
	  //camera_x_position += 0.1;
	  //cout << "left " << player_x_position << endl;
		camera_position -= right * camera_movement_speed;
	}else if(inputDirection == RIGHT){
	  //camera_x_position -= 0.1;
	  //cout << "right " << player_x_position << endl;
		camera_position += right * camera_movement_speed;
	}



	  return glm::lookAt(camera_position,
			  	  	     camera_position + direction,
						 up);
}


