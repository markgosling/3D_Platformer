#ifndef SRC_CAMERA_H_
#define SRC_CAMERA_H_

#include <glm/ext.hpp>
#include "common.h"
#include <vector>
#include <memory>
#include "GameAsset.h"

/**
 * The Camera class is used to store the position of the camera and define a
 * boundary box around it. It is also used to generate a view matrix based on
 * the cameras current position and also checks for collisions with assets to
 * prevent the cameras position being moved if it is colliding with another object.
 */
class Camera{

public:
	Camera();
	glm::mat4 UpdateCameraPosition(InputDirection input_direction, int mouse_x, int mouse_y, std::vector<std::shared_ptr<GameAsset>> &world_array);
	float GetLeft();
	float GetRight();
	float GetTop();
	float GetBottom();
	float GetFront();
	float GetBack();

	CollisionType DetectCollisionWithAsset(std::vector<std::shared_ptr<GameAsset>> &world_array);

private:

	float camera_x_position;
	float camera_y_position;
	float camera_z_position;
	float camera_old_x_position;
	float camera_old_y_position;
	float camera_old_z_position;

	float width;
	float depth;
	float height;

	glm::vec3 camera_position;
	glm::vec3 camera_old_position;

	glm::vec3 direction;
	glm::vec3 right;
	glm::vec3 up;

	float horizontal_angle;
	float vertical_angle;

	float mouse_delta_x;
	float mouse_delta_y;

	float camera_movement_speed;
	CollisionType collision_type;
};

#endif /* SRC_CAMERA_H_ */
