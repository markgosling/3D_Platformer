#include "Camera.h"
#include <glm/ext.hpp>
#include <iostream>
#include "GameAsset.h"

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
	  camera_old_position = camera_position;
	  direction = glm::vec3(0,0,0);
	  right = glm::vec3(0,0,0);
	  up = glm::vec3(0,0,0);

	  horizontal_angle = 0;
	  vertical_angle = 0;

	  mouse_delta_x = 0;
	  mouse_delta_y = 0;

	  camera_movement_speed = 0.1;

	  //The size parameters are used to create the bounding box for the camera.
	  width = 0.5;
	  depth = 0.5;
	  height = 0.5;



}

glm::mat4 Camera::UpdateCameraPosition(InputDirection inputDirection, int mouse_x, int mouse_y, std::vector<std::vector<std::vector<std::shared_ptr<GameAsset>>>> &world_array){

	//collision_type = DetectCollisionWithAsset(world_array);

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

	camera_old_position = camera_position;
	camera_old_x_position = camera_x_position;
	camera_old_y_position = camera_y_position;
	camera_old_z_position = camera_z_position;

	if(inputDirection == UP){

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

  		//If no collision is detected, freely move the camera left.
  	//	if(collision_type == NOCOLLISION){
  			camera_position -= right * camera_movement_speed;

  	//	}else{
  		//	camera_position += right * camera_movement_speed;
  		//}

	}else if(inputDirection == RIGHT){
	  //camera_x_position -= 0.1;
	  //cout << "right " << player_x_position << endl;

  		//If no collision is detected, freely move the camera right.
  		//if(collision_type == NOCOLLISION){
  			camera_position += right * camera_movement_speed;

  		//}else{
  		//	camera_position -= right * camera_movement_speed;
  		//}

	}

	//Store the updated coordinates for the camera.
	//Invert the X coordinate of the camera to match the x coordinates of the blocks which are also inverted
     camera_x_position = -camera_position[0];

     camera_y_position = camera_position[1];

     camera_z_position = camera_position[2];

std::cout << "camera position " << camera_position[2] << std::endl;
std::cout << "camera old position " << camera_old_position[2] << std::endl;

	//Check to see if a collision has  between the camera and an asset. If so,
	//revert the camera position back to the old location to prevent it colliding
	//with the object and to prevent it from moving.
    if(DetectCollisionWithAsset(world_array) != NOCOLLISION){
   	 camera_position = camera_old_position;
   	 camera_x_position = camera_old_x_position;
   	 camera_y_position = camera_old_y_position;
   	 camera_z_position = camera_old_z_position;
   	 std::cout << "test" << std::endl;
    }



	  return glm::lookAt(camera_position,
			  	  	     camera_position + direction,
						 up);
}

CollisionType Camera::DetectCollisionWithAsset(std::vector<std::vector<std::vector<std::shared_ptr<GameAsset>>>> &world_array){

	for(int x = 0; x < world_array.size(); x++){
    	for(int y = 0; y < world_array[x].size(); y++){
    		for(int z = 0; z < world_array[x][y].size(); z++){

    			//Check that an object exists in the array before attempting to access it.
    			if(world_array[x][y][z] != NULL){

        			auto ga = world_array[x][y][z];

        			if(ga->DetectCollision(this->GetLeft(), this->GetRight(), this->GetTop(), this->GetBottom(), this->GetFront(), this->GetBack()) != NOCOLLISION){

        				return ga->DetectCollision(this->GetLeft(), this->GetRight(), this->GetTop(), this->GetBottom(), this->GetFront(), this->GetBack());
        			}
    			}
    		}
    	}
    }

	return NOCOLLISION;
}

float Camera::GetLeft(){
	return camera_x_position - width/2;
}

float Camera::GetRight(){
	return camera_x_position + width/2;
}

float Camera::GetTop(){
	return camera_y_position + height/2;
}

float Camera::GetBottom(){
	return camera_y_position - height/2;
}

float Camera::GetFront(){
	return camera_z_position + depth/2;
}

float Camera::GetBack(){
	return camera_z_position - depth/2;
}
