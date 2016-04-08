/*
 * BoundingBox.cpp
 *
 *  Created on: 14 Mar 2016
 *      Author: mark
 */

#include "BoundingBox.h"
#include <iostream>
#include <glm/ext.hpp>


BoundingBox::BoundingBox(float x_position, float y_position, float z_position, float scale,
		float x_rotation, float y_rotation, float z_rotation){

	this->x_position = x_position;
	this->y_position = y_position;
	this->z_position = z_position;

	this->scale = scale;
	this->x_rotation = x_rotation;
	this->y_rotation = y_rotation;
	this->z_rotation = z_rotation;

	std::cout << "test" << std::endl;
	std::cout << x_position << std::endl;
	std::cout << y_position << std::endl;
	std::cout << z_position << std::endl;


}


glm::mat4 BoundingBox::GetCompleteModelTransformationMatrix(){

	//First create a scale matrix.
	glm::mat4 scale_matrix = glm::scale(glm::vec3(scale, scale, scale));

	//Now create a translation matrix to move the model to the correct world coordinates.
	glm::mat4 translate_matrix = glm::translate(glm::mat4(), glm::vec3(-x_position, y_position, z_position));

	//Multiply the matrices together to set the final model position and scale.
	model_transformation_matrix = translate_matrix * scale_matrix;

	//Finally rotate using GLM along the X, Y, Z coordinates and return the matrix.
	model_transformation_matrix = glm::rotate(model_transformation_matrix, x_rotation, glm::vec3(1, 0, 0));
	model_transformation_matrix = glm::rotate(model_transformation_matrix, y_rotation, glm::vec3(0, 1, 0));
	model_transformation_matrix = glm::rotate(model_transformation_matrix, z_rotation, glm::vec3(0, 0, 1));

	return model_transformation_matrix;
}

//glm::mat4 BoundingBox::Translate(){

	//Translate the shapes position on screen to match the XYZ coordinates. The x coordinate is negated so the objects is translated to the right instead of left.
	//Working glm::translate function code obtained from https://www.reddit.com/r/opengl/comments/2ztqjo/problem_with_glms_translate_matrix_call.
	//translate_matrix = glm::translate(glm::mat4(), glm::vec3(-x_position, y_position, z_position));

	//return translate_matrix;
//}


/**
bool DetectXCollision(float leftA, float rightA, float leftB,  float rightB){


	if(rightB > leftA && leftB < rightA){
		return true;
	}

	cout << "x collision detected " << endl;
	return false;
}

bool DetectYCollision(float topA, float bottomA, float topB, float bottomB){

	if(topB > bottomA && bottomB < topA){
		return true;
	}

	cout << "y collision detected " << endl;
	return false;
}


bool DetectZCollision(float frontA, float backA, float frontB, float backB){

	if(backB > frontA && frontB < backA && ){
		return true;
	}
	cout << "z collision detected " << endl;
	return false;
}
**/

