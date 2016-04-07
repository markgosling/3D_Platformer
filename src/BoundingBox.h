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

class BoundingBox{

public:
	//BoundingBox() : model_matrix(std::make_shared(1.0));
	//std_shared_prglm::mat4 model_matrix;

	BoundingBox(float, float, float);
	void Translate();
	void Scale();
	void RotateX();
	void RotateY();
	void RotateZ();

private:
	float x_position;
	float y_position;
	float z_position;

	/**float GetX();
	float GetY();
	float GetZ();

	float GetSize();

	float GetLeft();
	float GetRight();
	float GetTop();
	float GetBottom();
	float GetFront();
	float GetBack();

	void SetX(float);
	void SetY(float);
	void SetZ(float);

	void SetSize(float);

	bool DetectXCollision(float, float, float, float, float);
	bool DetectYCollision(float, float, float, float, float);
	bool DetectZCollision(float, float, float, float, float);

	glm::vec3 center;
	float size;**/

};


#endif /* SRC_BOUNDINGBOX_H_ */
