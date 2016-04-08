#ifndef GAMEASSET_H
#define GAMEASSET_H

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#ifdef _WIN32
  #include <windows.h>
#endif
#include <GL/gl.h>
#endif

#include <memory>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "common.h"
#include "BoundingBox.h"

/**
 * GameAsset is a superclass which forms the base for all 3D assets used
 * in the game. It has methods which are common to all objects, including
 * methods to implement collision detection, to find the asset type and
 * also to draw the asset on screen.
 */
class GameAsset {

public:
	GameAsset(float, float, float, float, float, float, float);
	enum AssetType {CUBE, PYRAMID};
	void Draw(GLuint);
	AssetType GetAssetType();
	std::shared_ptr<BoundingBox> boundingBox;
	bool DetectXCollision(float camera_left, float camera_right);
	bool DetectYCollision(float camera_top, float camera_bottom);
	bool DetectZCollision(float camera_front, float camera_back);
	CollisionType DetectCollision(float camera_left, float camera_right, float camera_top, float camera_bottom, float camera_front, float camera_back);
	glm::mat4 GetCompleteModelTransformationMatrix();

protected:
	AssetType assetType;
	GLuint element_buffer_length;
	GLuint vertex_buffer_token, element_buffer_token;
	float width;
	float depth;
	float height;

	float left_side_test;
	float right_side_test;
	float top_side_test;
	float bottom_side_test;
	float front_side_test;
	float back_side_test;

	float x_position;
	float y_position;
	float z_position;

private:
	void checkError(std::string file, int line);
};

#endif
