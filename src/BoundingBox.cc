/*
 * BoundingBox.cpp
 *
 *  Created on: 14 Mar 2016
 *      Author: mark
 */

#include "BoundingBox.h"
#include <iostream>
#include <glm/ext.hpp>


BoundingBox::BoundingBox(float x_position, float y_position, float z_position){

	this->x_position = x_position;
	this->y_position = y_position;
	this->z_position = z_position;

	std::cout << "test" << std::endl;
	std::cout << x_position << std::endl;
	std::cout << y_position << std::endl;
	std::cout << z_position << std::endl;


}

void BoundingBox::Translate(){
	//model_matrix = glm:::translate()
}

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

