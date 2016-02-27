#ifndef GAMEASSET_H
#define GAMEASSET_H

#include <iostream>
#include <GL/gl.h>
#include <vector>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "common.h"

/**
 * GameAsset is a superclass which forms the base for all 3D assets used
 * in the game. It has methods which are common to all objects, including
 * methods to implement collision detection, to find the asset type and
 * also to draw the asset on screen.
 */
class GameAsset {

public:
	enum AssetType {CUBE, PYRAMID};
	void Draw(GLuint);
	AssetType GetAssetType();
	bool DetectXCollision(float camera_left, float camera_right);
	bool DetectYCollision(float camera_top, float camera_bottom);
	bool DetectZCollision(float camera_front, float camera_back);
	CollisionType DetectCollision(float camera_left, float camera_right, float camera_top, float camera_bottom, float camera_front, float camera_back);

protected:
	AssetType assetType;
	GLuint element_buffer_length;
	GLuint vertex_buffer_token, element_buffer_token;
	float width;
	float depth;
	float height;
	float x_position;
	float y_position;
	float z_position;

	float left_side_test;
	float right_side_test;
	float top_side_test;
	float bottom_side_test;
	float front_side_test;
	float back_side_test;

private:
	void checkError(std::string file, int line);
};

#endif
