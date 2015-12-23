#include "Camera.h"
#include <glm/ext.hpp>
#include <iostream>
#include "GameAsset.h"

/**
 * @file Camera.cc
 * @version 1.0
 *
 * @section Description
 *
 * The Camera class is used to store the position of the camera and define a
 * boundary box around it. It is also used to generate a view matrix based on
 * the cameras current position and also checks for collisions with assets to
 * prevent the cameras position being moved if it is colliding with another object.
 */

/**
 * Constructor which initialises the position of the camera and other parameters
 * such as the movement speed and bounding box size.
 */
Camera::Camera(){

	//Set the start position of the camera.
	camera_x_position = -3.0f;
	camera_y_position = 1.5f;
	camera_z_position = 0.0f;
	camera_position = glm::vec3(camera_x_position, camera_y_position, camera_z_position);

	//Initialise the variables used to store the previous position of the
	//camera. These are used in the event the camera detects a collision
	//with an asset after it has been moved, in which case the position is
	//reverted back.
	camera_old_position = camera_position;
	camera_old_x_position = camera_x_position;
	camera_old_y_position = camera_y_position;
	camera_old_z_position = camera_z_position;

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

	collision_type = NOCOLLISION;
}

/**
 * The 'UpdateCameraPosition' method updates the camera position based on the input
 * direction entered by the player and also sets the viewing direction based on the
 * mouse X and Y coordinates. It also checks for collisions with assets to prevent
 * the camera being moved if a collision is detected. Once the camera has been moved
 * the method returns an updated view matrix which can be used by the shader program
 * to update the screen.
 *
 * @param inputDirection - InputDirection - An Enum value indicating the direction being entered by the player.
 * @param mouse_x - Integer - The mouse X coordinates.
 * @param mouse_y - Integer - The mouse Y coordinates.
 * @param world_array - vector<vector<vector<shared_ptr<GameAsset>>>> - A reference to the 3D array storing assets.
 *
 * @return an updated 4x4 view matrix.
 */
glm::mat4 Camera::UpdateCameraPosition(InputDirection input_direction, int mouse_x, int mouse_y, std::vector<std::vector<std::vector<std::shared_ptr<GameAsset>>>> &world_array){

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

	//Create an angle to the right of the right of the horizontal angle.
	right = glm::vec3(
			sin(horizontal_angle - 3.14/2.0f),
			0,
			cos(horizontal_angle - 3.14/2.0f));

	//Create an angle directly up and between the forward and right angles.
	up = glm::cross(right, direction);

	//Store the current position of the camera before it is moved.
	camera_old_position = camera_position;
	camera_old_x_position = camera_x_position;
	camera_old_y_position = camera_y_position;
	camera_old_z_position = camera_z_position;

	//Update the camera position based on the input direction being entered.
	if(input_direction == UP){

		camera_position += glm::vec3(cos(vertical_angle) * sin(horizontal_angle),
				0, cos(vertical_angle) * cos(horizontal_angle)) * camera_movement_speed;

	}else if(input_direction == DOWN){

		camera_position -= glm::vec3(cos(vertical_angle) * sin(horizontal_angle),
				0, cos(vertical_angle) * cos(horizontal_angle)) * camera_movement_speed;

	}else if(input_direction == LEFT){

		camera_position -= right * camera_movement_speed;

	}else if(input_direction == RIGHT){

		camera_position += right * camera_movement_speed;
	}

	//Store the updated coordinates for the camera.
	//Invert the X coordinate of the camera to match the x coordinates of the blocks which are also inverted.
	camera_x_position = -camera_position[0];
	camera_y_position = camera_position[1];
	camera_z_position = camera_position[2];

	//Check to see if a collision has  between the camera and an asset. If so,
	//revert the camera position back to the old location to prevent it colliding
	//with the object and to prevent it from moving.
	if(DetectCollisionWithAsset(world_array) != NOCOLLISION){
		camera_position = camera_old_position;
		camera_x_position = camera_old_x_position;
		camera_y_position = camera_old_y_position;
		camera_z_position = camera_old_z_position;
	}

	//Create and return an updated view matrix.
	return glm::lookAt(camera_position,
			camera_position + direction,
			up);
}

/**
 * The 'DetectCollisionWithAsset' method looks through the entire 3D array of assets and
 * checks them for collisions with the camera. If a collision is detected it returns the
 * side of the asset which was collided with. If no collision was detected it returns 'NOCOLLISION'.
 *
 * @param world_array - vector<vector<vector<shared_ptr<GameAsset>>>> - a 3D array containing assets.
 *
 * @return an Enum which indicates the side of the asset the camera collided with.
 */
CollisionType Camera::DetectCollisionWithAsset(std::vector<std::vector<std::vector<std::shared_ptr<GameAsset>>>> &world_array){

	//Loop through the 3D array of assets.
	for(int x = 0; x < world_array.size(); x++){
		for(int y = 0; y < world_array[x].size(); y++){
			for(int z = 0; z < world_array[x][y].size(); z++){

				//Check that an object exists in the array before attempting to access it.
				if(world_array[x][y][z] != NULL){

					//Create a variable which points to the current asset in the array.
					auto ga = world_array[x][y][z];

					//Check for collisions with the cameras bounding box. If a collision is detected then
					//return the side of the asset which was collided with.
					if(ga->DetectCollision(this->GetLeft(), this->GetRight(), this->GetTop(), this->GetBottom(), this->GetFront(), this->GetBack()) != NOCOLLISION){

						return ga->DetectCollision(this->GetLeft(), this->GetRight(), this->GetTop(), this->GetBottom(), this->GetFront(), this->GetBack());
					}
				}
			}
		}
	}

	return NOCOLLISION;
}

/**
 * Returns the cameras bounding box left side position.
 */
float Camera::GetLeft(){
	return camera_x_position - width/2;
}

/**
 * Returns the cameras bounding box right side position.
 */
float Camera::GetRight(){
	return camera_x_position + width/2;
}

/**
 * Returns the cameras bounding box top side position.
 */
float Camera::GetTop(){
	return camera_y_position + height/2;
}

/**
 * Returns the cameras bounding box bottom side position.
 */
float Camera::GetBottom(){
	return camera_y_position - height/2;
}

/**
 * Returns the cameras bounding box front side position.
 */
float Camera::GetFront(){
	return camera_z_position + depth/2;
}

/**
 * Returns the cameras bounding box front side position.
 */
float Camera::GetBack(){
	return camera_z_position - depth/2;
}
