/*
 * BoundingBox.cpp
 *
 *  Created on: 14 Mar 2016
 *      Author: mark
 */

#include "BoundingBox.h"
#include <iostream>
#include <glm/ext.hpp>

/**
 * Constructor which sets the starting positional information for the bounding box, e.g.
 * the position, scale and rotation around the X, Y and Z axis.
 *
 * @param x_position - float - The X position for the bounding box.
 * @param y_position - float - The Y position for the bounding box.
 * @param z_position - float - The Z position for the bounding box.
 * @param scale - float - The scaling size of the bounding box.
 * @param x_rotation - float - The rotation amount in degrees around the X axis.
 * @param y_rotation - float - The rotation amount in degrees around the Y axis.
 * @param z_rotation - float - The rotation amount in degrees around the Z axis.
 */
BoundingBox::BoundingBox(float x_position, float y_position, float z_position, float scale,
		float x_rotation, float y_rotation, float z_rotation){

	this->x_position = x_position;
	this->y_position = y_position;
	this->z_position = z_position;

	this->scale = scale;
	this->x_rotation = x_rotation;
	this->y_rotation = y_rotation;
	this->z_rotation = z_rotation;
}

/**
 * Method which calculates a matrix containing the models translation, scaling and
 * rotation and returns it so it can be used in the shader program. It also calculates
 * the center position of the model so it can be used for performing collision detection.
 *
 * @return a mat4 matrix containing all the models positional information.
 */
glm::mat4 BoundingBox::GetCompleteModelTransformationMatrix(){

	//First create a scale matrix.
	glm::mat4 scale_matrix = glm::scale(glm::vec3(scale, scale, scale));

	//Now create a translation matrix to move the model to the correct world coordinates.
	glm::mat4 translate_matrix = glm::translate(glm::mat4(), glm::vec3(-x_position, y_position, z_position));

	//Multiply the matrices together to set the final model position and scale.
	model_transformation_matrix = translate_matrix * scale_matrix;

	//Rotate using GLM along the X, Y, Z coordinates.
	model_transformation_matrix = glm::rotate(model_transformation_matrix, x_rotation, glm::vec3(1, 0, 0));
	model_transformation_matrix = glm::rotate(model_transformation_matrix, y_rotation, glm::vec3(0, 1, 0));
	model_transformation_matrix = glm::rotate(model_transformation_matrix, z_rotation, glm::vec3(0, 0, 1));

	//Store the center of the model in a vec3 (for use with collision detection).
	model_center = glm::vec3((model_transformation_matrix * glm::vec4(0.0f,0.0f,0.0f,1.0f)));

	return model_transformation_matrix;
}

/**
 * The 'DetectCollision' method is used to detect a collision between the camera and
 * the game object. It compares each side of the cameras bounding box to the sides of
 * the bounding box to work out if a collision has occurred. It then calculates which
 * side of the asset was collided with. It returns an Enum with the side of the asset where
 * the collision occurred.
 *
 * @param camera_left - float - The left side of the cameras boundary box.
 * @param camera_right- float - The right side of the cameras boundary box.
 * @param camera_top- float - The top side of the cameras boundary box.
 * @param camera_bottom- float - The bottom side of the cameras boundary box.
 * @param camera_front- float - The front side of the cameras boundary box.
 * @param camera_back- float - The back side of the cameras boundary box.
 *
 * @return an Enum indicating which side of the asset was collided with. Return 'NOCOLLISION'
 * 	if no collision was detected.
 */
CollisionType BoundingBox::DetectCollision(float camera_left, float camera_right, float camera_top,
		float camera_bottom, float camera_front, float camera_back){

	//Call the methods which check for collisions on the X, Y and Z coordinates of the asset.
	//If all three methods return true, then we know the camera has collided with
	//an object and we need to check which side of the asset has been collided with.
	if(DetectXCollision(camera_left, camera_right) &&
			DetectYCollision(camera_top, camera_bottom) &&
			DetectZCollision(camera_front, camera_back)){

		//Find the distance between the camera right side and the left side of the asset.
		left_side_test = camera_right - GetLeft();

		//Find the distance between the camera left side and the right side of the asset.
		right_side_test = GetRight() - camera_left;

		//Find the distance between the camera front side and the back side of the asset.
		back_side_test  = camera_front - GetBack();

		//Find the distance between the camera back side and the front side of the asset.
		front_side_test = GetFront() - camera_back;

		//These tests are disabled as they are not currently required or properly implemented.
		//bottom_side_test = camera_y_position - (y_position - (height/2));
		//top_side_test  = camera_y_position - (y_position + (height/2));

		//Check to see which distance is shortest. The shortest distance between the sides
		//indicates which side of the asset was collided with. Return a value to indicate this.
		if(left_side_test < right_side_test && left_side_test < front_side_test && left_side_test < back_side_test){
			return LEFTSIDE;
		}else if(right_side_test < left_side_test && right_side_test < front_side_test && right_side_test < back_side_test){
			return RIGHTSIDE;
		}else if(front_side_test < left_side_test && front_side_test < right_side_test && front_side_test < back_side_test){
			return FRONTSIDE;
		}else if(back_side_test < front_side_test && back_side_test < left_side_test && back_side_test < right_side_test){
			return BACKSIDE;
		}else{
			return NOCOLLISION;
		}
	}
	return NOCOLLISION;
}


/**
 * Detects if the cameras boundary box is within the width of the asset.
 *
 * @param camera_left - float - The coordinate for the left side of the cameras boundary box.
 * @param camera_right - float - The coordinate for the right side of the cameras boundary box.
 *
 * @return true if a collision was detected, otherwise false.
 */
bool BoundingBox::DetectXCollision(float camera_left, float camera_right){

	if(GetRight() > camera_left && GetLeft() < camera_right){
		return true;
	}

	return false;
}

/**
 * Detects if the cameras boundary box is within the height of the asset.
 *
 * @param camera_top - float - The coordinate for the top side of the cameras boundary box.
 * @param camera_bottom - float - The coordinate for the bottom side of the cameras boundary box.
 *
 * @return true if a collision was detected, otherwise false.
 */
bool BoundingBox::DetectYCollision(float camera_top, float camera_bottom){

	std::cout << "test" << std::endl;
	if(GetTop() > camera_bottom && GetBottom() < camera_top){
		return true;
	}

	return false;
}

/**
 * Detects if the cameras boundary box is within the width of the asset.
 *
 * @param camera_front - float - The coordinate for the front side of the cameras boundary box.
 * @param camera_back - float - The coordinate for the back side of the cameras boundary box.
 *
 * @return true if a collision was detected, otherwise false.
 */
bool BoundingBox::DetectZCollision(float camera_front, float camera_back){

	if(GetBack() < camera_front && GetFront() > camera_back){
		return true;
	}

	return false;
}

/**
 * Method to get the left side position of the bounding box.
 *
 * @return a float containing the left side position.
 */
float BoundingBox::GetLeft(){

	return (-model_center[0]) - (scale * 0.5);
}


/**
 * Method to get the right side position of the bounding box.
 *
 * @return a float containing the right side position.
 */
float BoundingBox::GetRight(){

	return (-model_center[0]) + (scale * 0.5);
}


/**
 * Method to get the top side position of the bounding box.
 *
 * @return a float containing the top side position.
 */
float BoundingBox::GetTop(){

	return model_center[1] + (scale * 0.5);
}


/**
 * Method to get the bottom side position of the bounding box.
 *
 * @return a float containing the bottom side position.
 */
float BoundingBox::GetBottom(){

	return model_center[1] - (scale * 0.5);
}

/**
 * Method to get the front side position of the bounding box.
 *
 * @return a float containing the front side position.
 */
float BoundingBox::GetFront(){
	std::cout << "asset front = " << (model_center[2] - (scale * 0.5)) << std::endl;
	return model_center[2] + (scale * 0.5);
}


/**
 * Method to get the back side position of the bounding box.
 *
 * @return a float containing the back side position.
 */
float BoundingBox::GetBack(){
	std::cout << "asset back = " << (model_center[2] + (scale * 0.5)) << std::endl;
	return model_center[2] - (scale * 0.5);
}
