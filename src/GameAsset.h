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
 * in the game. Its main job is to draw the object on screen. It also holds
 * an instance of the BoundaryBox class which it passes data to so that collision
 * detection and the object position and orientation can be handled.
 */
class GameAsset {

public:
	GameAsset(float, float, float, float, float, float, float);
	enum AssetType {CUBE, PYRAMID, UNKNOWN};
	void Draw(GLuint);
	AssetType GetAssetType();
	std::shared_ptr<BoundingBox> bounding_box;
	void SetAnimationParameters(std::vector<glm::vec3>, float, glm::vec3, float);
	CollisionType DetectCollision(float camera_left, float camera_right, float camera_top, float camera_bottom, float camera_front, float camera_back);
	glm::mat4 GetCompleteModelTransformationMatrix();

protected:
	AssetType assetType;
	GLuint element_buffer_length;
	GLuint vertex_buffer_token, element_buffer_token;

private:
	void checkError(std::string file, int line);
};

#endif
