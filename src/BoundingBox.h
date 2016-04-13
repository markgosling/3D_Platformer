/*
 * BoundingBox.h
 *
 *  Created on: 14 Mar 2016
 *      Author: mark
 */

#ifndef SRC_BOUNDINGBOX_H_
#define SRC_BOUNDINGBOX_H_

#include <memory.h>
#include <glm/glm.hpp>
#include "common.h"
#include <vector>

class BoundingBox{

public:
	//BoundingBox() : model_matrix(std::make_shared(1.0));
	//std_shared_prglm::mat4 model_matrix;

	BoundingBox(float, float, float, float, float, float, float);
	glm::mat4 GetCompleteModelTransformationMatrix();
	glm::mat4 Translate();
	CollisionType DetectCollision(float, float, float, float, float, float);
	void SetAnimationParameters(std::vector<glm::vec3>, float, glm::vec3, float);
	void Animate();

	bool DetectXCollision(float, float);
	bool DetectYCollision(float, float);
	bool DetectZCollision(float, float);

	float GetLeft();
	float GetRight();
	float GetTop();
	float GetBottom();
	float GetFront();
	float GetBack();

	void Scale();
	void RotateX();
	void RotateY();
	void RotateZ();

private:
	glm::vec3 position; //X, Y and Z starting coordinates.

	float scale;
	float x_rotation;
	float y_rotation;
	float z_rotation;

	std::vector<glm::vec3> target_coordinates_array;
	float movement_speed;
	glm::vec3 rotation_axis;
	float rotation_speed;
	bool is_animated;
	float distance; //Distance between the start point and target point when animating the object.
	glm::vec3 direction;
	bool target_reached;
	int coordinates_array_position;

	float left_side_test;
	float right_side_test;
	float top_side_test;
	float bottom_side_test;
	float front_side_test;
	float back_side_test;

	glm::vec3 model_center;

	glm::mat4 model_transformation_matrix; //The matrix produced after the model has been translated, rotated and scaled.
};


#endif /* SRC_BOUNDINGBOX_H_ */
