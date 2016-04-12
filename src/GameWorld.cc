#include "GameWorld.h"
#include <string>

/**
 * @file GameWorld.cc
 * @version 1.0
 *
 * @section Description
 *
 * GameWorld separates the 'main' class from the 'GameAssetManager' class and acts
 * as a 'go-between' for them. The constructor is also used to create an instance
 * of GameAssetManager and add all the required assets required to create the 3D
 * game world.
 */

/**
 * Constructor which creates an instance of GameAssetManager and adds
 * the assets required to create the 3D world to it.
 */
GameWorld::GameWorld () {

	asset_manager = std::make_shared<GameAssetManager>();

	//Array to temporarily store the coordinates animated objects should move to.
	std::vector<glm::vec3> animation_coordinates;

	//Add the assets to make the game world.
	//The assets constructor parameters are in the form of: X pos, Y pos, Z pos, scale, X rot, Y rot, Z rot.

	//Animate new objects by calling 'SetAnimationParameters(array of type vec3 containing movement coordinates, movement speed,
																//vec3 with the coordinates set to 1 to indicate an axis to rotate around,
																//rotation speed, true\false indicating if the animation should loop);'

	//Add the blocks required to make the ground.
	asset_manager->AddAsset(std::make_shared<CubeAsset>(0, 0, 0, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(1, 0, 0, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(2, 0, 0, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(3, 0, 0, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(4, 0, 0, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(5, 0, 0, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(6, 0, 0, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(7, 0, 0, 1, 0, 0, 0));

	asset_manager->AddAsset(std::make_shared<CubeAsset>(0, 0, 1, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(1, 0, 1, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(2, 0, 1, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(3, 0, 1, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(4, 0, 1, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(5, 0, 1, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(6, 0, 1, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(7, 0, 1, 1, 0, 0, 0));

	asset_manager->AddAsset(std::make_shared<CubeAsset>(0, 0, 2, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(1, 0, 2, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(2, 0, 2, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(3, 0, 2, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(4, 0, 2, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(5, 0, 2, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(6, 0, 2, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(7, 0, 2, 1, 0, 0, 0));

	asset_manager->AddAsset(std::make_shared<CubeAsset>(0, 0, 3, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(1, 0, 3, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(2, 0, 3, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(3, 0, 3, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(4, 0, 3, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(5, 0, 3, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(6, 0, 3, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(7, 0, 3, 1, 0, 0, 0));

	asset_manager->AddAsset(std::make_shared<CubeAsset>(0, 0, 4, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(1, 0, 4, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(2, 0, 4, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(3, 0, 4, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(4, 0, 4, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(5, 0, 4, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(6, 0, 4, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(7, 0, 4, 1, 0, 0, 0));

	asset_manager->AddAsset(std::make_shared<CubeAsset>(0, 0, 5, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(1, 0, 5, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(2, 0, 5, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(3, 0, 5, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(4, 0, 5, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(5, 0, 5, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(6, 0, 5, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(7, 0, 5, 1, 0, 0, 0));

	asset_manager->AddAsset(std::make_shared<CubeAsset>(0, 0, 6, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(1, 0, 6, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(2, 0, 6, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(3, 0, 6, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(4, 0, 6, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(5, 0, 6, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(6, 0, 6, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(7, 0, 6, 1, 0, 0, 0));

	asset_manager->AddAsset(std::make_shared<CubeAsset>(0, 0, 7, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(1, 0, 7, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(2, 0, 7, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(3, 0, 7, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(4, 0, 7, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(5, 0, 7, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(6, 0, 7, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(7, 0, 7, 1, 0, 0, 0));

	asset_manager->AddAsset(std::make_shared<CubeAsset>(0, 0, 8, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(1, 0, 8, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(2, 0, 8, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(3, 0, 8, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(4, 0, 8, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(5, 0, 8, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(6, 0, 8, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(7, 0, 8, 1, 0, 0, 0));

	asset_manager->AddAsset(std::make_shared<CubeAsset>(0, 0, 9, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(1, 0, 9, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(3, 0, 9, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(4, 0, 9, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(5, 0, 9, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(6, 0, 9, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(7, 0, 9, 1, 0, 0, 0));

	asset_manager->AddAsset(std::make_shared<CubeAsset>(0, 0, 10, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(1, 0, 10, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(2, 0, 10, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(3, 0, 10, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(4, 0, 10, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(5, 0, 10, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(6, 0, 10, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(7, 0, 10, 1, 0, 0, 0));

	//Add a large cube at the end of the play field to represent a house...?
	asset_manager->AddAsset(std::make_shared<CubeAsset>(4, 2, 18, 4, 0, 45, 0));
	asset_manager->AddAsset(std::make_shared<PyramidAsset>(4, 6, 18, 4, 0, 45, 0));

	//Add the pillars on the screen position furtherest from the player.
	asset_manager->AddAsset(std::make_shared<CubeAsset>(1, 1, 10, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(6, 1, 10, 1, 0, 0, 0));

	asset_manager->AddAsset(std::make_shared<CubeAsset>(1, 2, 10, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(6, 2, 10, 1, 0, 0, 0));

	asset_manager->AddAsset(std::make_shared<PyramidAsset>(1, 3, 10, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<PyramidAsset>(6, 3, 10, 1, 0, 0, 0));

	//Add the pillars on the screen position closest to the player.
	asset_manager->AddAsset(std::make_shared<CubeAsset>(1, 1, 0, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(6, 1, 0, 1, 0, 0, 0));

	asset_manager->AddAsset(std::make_shared<CubeAsset>(1, 2, 0, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<CubeAsset>(6, 2, 0, 1, 0, 0, 0));

	asset_manager->AddAsset(std::make_shared<PyramidAsset>(1, 3, 0, 1, 0, 0, 0));
	asset_manager->AddAsset(std::make_shared<PyramidAsset>(6, 3, 0, 1, 0, 0, 0));

	//Add a pyramid to the middle/left side of the game world.
	asset_manager->AddAsset(std::make_shared<PyramidAsset>(0, 1, 5, 1, 0, 0, 0));

	//Set the first pyramid to rotate along the Y axis.
	asset_manager->SetAnimationParameters(animation_coordinates, 0.0, glm::vec3(0,1,0), 0.1);

	//Add a second pyramid to the middle\right side of the game world.
	asset_manager->AddAsset(std::make_shared<PyramidAsset>(7, 1, 5, 1, 0, 0, 0));

	//Set the second pyramid to rotate along the Y axis.
	asset_manager->SetAnimationParameters(animation_coordinates, 0.0, glm::vec3(0,1,0), -0.1);
}

/**
 * Method which calls the 'Draw' method in 'GameAssetManager'.
 */
void GameWorld::Draw() {
	asset_manager->Draw();
}

/**
 * Method which calls the 'UpdateCameraPosition' method in 'GameAssetManager'
 * with the correct parameters.
 *
 * @param input_direction - InputDirection - The input direction being entered by the player.
 * @param mouse_x - Integer - The mouse X coordinates.
 * @param mouse_y - Integer - The mouse Y coordinates.
 */
void GameWorld::UpdateCameraPosition(InputDirection input_direction, int mouse_x, int mouse_y){
	asset_manager->UpdateCameraPosition(input_direction, mouse_x, mouse_y);
}
