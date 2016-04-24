#include "GameWorld.h"
#include "PythonBindings.h"
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
	//The constructor to add a new asset is in the form of: X pos, Y pos, Z pos, scale, X rot, Y rot, Z rot.

	//Animate new objects by calling 'SetAnimationParameters(array of type vec3 containing movement coordinates, movement speed,
	//vec3 with the coordinates set to 1 to indicate an axis to rotate around, rotation speed);'

	//Add the blocks required to make the ground.
	asset_manager->AddCube(0, 0, 0, 1, 0, 0, 0);
	asset_manager->AddCube(1, 0, 0, 1, 0, 0, 0);
	asset_manager->AddCube(2, 0, 0, 1, 0, 0, 0);
	asset_manager->AddCube(3, 0, 0, 1, 0, 0, 0);
	asset_manager->AddCube(4, 0, 0, 1, 0, 0, 0);
	asset_manager->AddCube(5, 0, 0, 1, 0, 0, 0);
	asset_manager->AddCube(6, 0, 0, 1, 0, 0, 0);
	asset_manager->AddCube(7, 0, 0, 1, 0, 0, 0);

	asset_manager->AddCube(0, 0, 1, 1, 0, 0, 0);
	asset_manager->AddCube(1, 0, 1, 1, 0, 0, 0);
	asset_manager->AddCube(2, 0, 1, 1, 0, 0, 0);
	asset_manager->AddCube(3, 0, 1, 1, 0, 0, 0);
	asset_manager->AddCube(4, 0, 1, 1, 0, 0, 0);
	asset_manager->AddCube(5, 0, 1, 1, 0, 0, 0);
	asset_manager->AddCube(6, 0, 1, 1, 0, 0, 0);
	asset_manager->AddCube(7, 0, 1, 1, 0, 0, 0);

	asset_manager->AddCube(0, 0, 2, 1, 0, 0, 0);
	asset_manager->AddCube(1, 0, 2, 1, 0, 0, 0);
	asset_manager->AddCube(2, 0, 2, 1, 0, 0, 0);
	asset_manager->AddCube(3, 0, 2, 1, 0, 0, 0);
	asset_manager->AddCube(4, 0, 2, 1, 0, 0, 0);
	asset_manager->AddCube(5, 0, 2, 1, 0, 0, 0);
	asset_manager->AddCube(6, 0, 2, 1, 0, 0, 0);
	asset_manager->AddCube(7, 0, 2, 1, 0, 0, 0);

	asset_manager->AddCube(0, 0, 3, 1, 0, 0, 0);
	asset_manager->AddCube(1, 0, 3, 1, 0, 0, 0);
	asset_manager->AddCube(2, 0, 3, 1, 0, 0, 0);
	asset_manager->AddCube(3, 0, 3, 1, 0, 0, 0);
	asset_manager->AddCube(4, 0, 3, 1, 0, 0, 0);
	asset_manager->AddCube(5, 0, 3, 1, 0, 0, 0);
	asset_manager->AddCube(6, 0, 3, 1, 0, 0, 0);
	asset_manager->AddCube(7, 0, 3, 1, 0, 0, 0);

	asset_manager->AddCube(0, 0, 4, 1, 0, 0, 0);
	asset_manager->AddCube(1, 0, 4, 1, 0, 0, 0);
	asset_manager->AddCube(2, 0, 4, 1, 0, 0, 0);
	asset_manager->AddCube(3, 0, 4, 1, 0, 0, 0);
	asset_manager->AddCube(4, 0, 4, 1, 0, 0, 0);
	asset_manager->AddCube(5, 0, 4, 1, 0, 0, 0);
	asset_manager->AddCube(6, 0, 4, 1, 0, 0, 0);
	asset_manager->AddCube(7, 0, 4, 1, 0, 0, 0);

	asset_manager->AddCube(0, 0, 5, 1, 0, 0, 0);
	asset_manager->AddCube(1, 0, 5, 1, 0, 0, 0);
	asset_manager->AddCube(2, 0, 5, 1, 0, 0, 0);
	asset_manager->AddCube(3, 0, 5, 1, 0, 0, 0);
	asset_manager->AddCube(4, 0, 5, 1, 0, 0, 0);
	asset_manager->AddCube(5, 0, 5, 1, 0, 0, 0);
	asset_manager->AddCube(6, 0, 5, 1, 0, 0, 0);
	asset_manager->AddCube(7, 0, 5, 1, 0, 0, 0);

	asset_manager->AddCube(0, 0, 6, 1, 0, 0, 0);
	asset_manager->AddCube(1, 0, 6, 1, 0, 0, 0);
	asset_manager->AddCube(2, 0, 6, 1, 0, 0, 0);
	asset_manager->AddCube(3, 0, 6, 1, 0, 0, 0);
	asset_manager->AddCube(4, 0, 6, 1, 0, 0, 0);
	asset_manager->AddCube(5, 0, 6, 1, 0, 0, 0);
	asset_manager->AddCube(6, 0, 6, 1, 0, 0, 0);
	asset_manager->AddCube(7, 0, 6, 1, 0, 0, 0);

	asset_manager->AddCube(0, 0, 7, 1, 0, 0, 0);
	asset_manager->AddCube(1, 0, 7, 1, 0, 0, 0);
	asset_manager->AddCube(2, 0, 7, 1, 0, 0, 0);
	asset_manager->AddCube(3, 0, 7, 1, 0, 0, 0);
	asset_manager->AddCube(4, 0, 7, 1, 0, 0, 0);
	asset_manager->AddCube(5, 0, 7, 1, 0, 0, 0);
	asset_manager->AddCube(6, 0, 7, 1, 0, 0, 0);
	asset_manager->AddCube(7, 0, 7, 1, 0, 0, 0);

	asset_manager->AddCube(0, 0, 8, 1, 0, 0, 0);
	asset_manager->AddCube(1, 0, 8, 1, 0, 0, 0);
	asset_manager->AddCube(2, 0, 8, 1, 0, 0, 0);
	asset_manager->AddCube(3, 0, 8, 1, 0, 0, 0);
	asset_manager->AddCube(4, 0, 8, 1, 0, 0, 0);
	asset_manager->AddCube(5, 0, 8, 1, 0, 0, 0);
	asset_manager->AddCube(6, 0, 8, 1, 0, 0, 0);
	asset_manager->AddCube(7, 0, 8, 1, 0, 0, 0);

	asset_manager->AddCube(0, 0, 9, 1, 0, 0, 0);
	asset_manager->AddCube(1, 0, 9, 1, 0, 0, 0);
	asset_manager->AddCube(3, 0, 9, 1, 0, 0, 0);
	asset_manager->AddCube(4, 0, 9, 1, 0, 0, 0);
	asset_manager->AddCube(5, 0, 9, 1, 0, 0, 0);
	asset_manager->AddCube(6, 0, 9, 1, 0, 0, 0);
	asset_manager->AddCube(7, 0, 9, 1, 0, 0, 0);

	asset_manager->AddCube(0, 0, 10, 1, 0, 0, 0);
	asset_manager->AddCube(1, 0, 10, 1, 0, 0, 0);
	asset_manager->AddCube(2, 0, 10, 1, 0, 0, 0);
	asset_manager->AddCube(3, 0, 10, 1, 0, 0, 0);
	asset_manager->AddCube(4, 0, 10, 1, 0, 0, 0);
	asset_manager->AddCube(5, 0, 10, 1, 0, 0, 0);
	asset_manager->AddCube(6, 0, 10, 1, 0, 0, 0);
	asset_manager->AddCube(7, 0, 10, 1, 0, 0, 0);

	//Add a large cube\pyramid at the end of the play field to represent a house...?
	asset_manager->AddCube(4, 2, 18, 4, 0, 45, 0);
	asset_manager->AddPyramid(4, 6, 18, 4, 0, 45, 0);

	//Add the pillars on the screen position furtherest from the player.
	asset_manager->AddCube(1, 1, 10, 1, 0, 0, 0);
	asset_manager->AddCube(6, 1, 10, 1, 0, 0, 0);

	asset_manager->AddCube(1, 2, 10, 1, 0, 0, 0);
	asset_manager->AddCube(6, 2, 10, 1, 0, 0, 0);

	asset_manager->AddPyramid(1, 3, 10, 1, 0, 0, 0);
	asset_manager->AddPyramid(6, 3, 10, 1, 0, 0, 0);

	//Add the pillars on the screen position closest to the player.
	asset_manager->AddCube(1, 1, 0, 1, 0, 0, 0);
	asset_manager->AddCube(6, 1, 0, 1, 0, 0, 0);

	asset_manager->AddCube(1, 2, 0, 1, 0, 0, 0);
	asset_manager->AddCube(6, 2, 0, 1, 0, 0, 0);

	asset_manager->AddPyramid(1, 3, 0, 1, 0, 0, 0);
	asset_manager->AddPyramid(6, 3, 0, 1, 0, 0, 0);

	//Add a pyramid to the middle/left side of the game world.
	asset_manager->AddPyramid(0, 1, 5, 1, 0, 0, 0);

	//Set the first pyramid to rotate along the Y axis.
	asset_manager->SetAnimationParameters(animation_coordinates, 0.0, glm::vec3(0,1,0), 0.1);

	//Add a second pyramid to the middle\right side of the game world.
	asset_manager->AddPyramid(7, 1, 5, 1, 0, 0, 0);

	//Set the second pyramid to rotate along the Y axis.
	asset_manager->SetAnimationParameters(animation_coordinates, 0.0, glm::vec3(0,1,0), -0.1);

	//Add a half size cube above the game world to represent a moving platform.
	asset_manager->AddCube(0, 5, 10, 0.5, 0, 0, 0);

	//Animate the platform by setting coordinates which will cause it to move around the edge of the game world.
	animation_coordinates.push_back(glm::vec3(0,5,0));
	animation_coordinates.push_back(glm::vec3(7,5,0));
	animation_coordinates.push_back(glm::vec3(7,5,10));
	animation_coordinates.push_back(glm::vec3(0,5,10));

	//Pass the movement coordinates to the platform.
	asset_manager->SetAnimationParameters(animation_coordinates, 2.0, glm::vec3(0,0,0), 0);

	//Add a second small cube to the sky.
	asset_manager->AddCube(5, 8, 5, 0.6, 0, 0, 0);

	//Clear the target coordinates and then add new ones to the array to make the cube bounce
	//from the center of the world to one of the pillars, then back to the center before heading towards
	//the next pillar.
	animation_coordinates.clear();
	animation_coordinates.push_back(glm::vec3(1,4,0)); //Pillar 1.
	animation_coordinates.push_back(glm::vec3(5, 8, 5)); //Center.
	animation_coordinates.push_back(glm::vec3(6, 4, 0)); //Pillar 2.
	animation_coordinates.push_back(glm::vec3(5, 8, 5)); //Center.
	animation_coordinates.push_back(glm::vec3(6, 4, 10)); //Pillar 3.
	animation_coordinates.push_back(glm::vec3(5, 8, 5)); //Center.
	animation_coordinates.push_back(glm::vec3(1, 4, 10)); //Pillar 4.
	animation_coordinates.push_back(glm::vec3(5, 8, 5)); //Center.

	//Pass the movement coordinates to the cube with a movement speed of 1.
	//Also set it to rotate around all 3 axes at once with a rotation speed of 0.1.
	asset_manager->SetAnimationParameters(animation_coordinates, 4.0, glm::vec3(1,1,1), 0.1);

	//Add two large cubes to the left of the play field and a rotated pyramid to represent a windmill(?).
	asset_manager->AddCube(-8, 1, 5, 2, 0, 0, 0);
	asset_manager->AddCube(-8, 3, 5, 2, 0, 0, 0);
	asset_manager->AddPyramid(-6.5, 3, 5, 1.5, 0, 0, -1.6);

	//Clear the animation coordinates then call the method to rotate the pyramid around its X axis.
	animation_coordinates.clear();
	asset_manager->SetAnimationParameters(animation_coordinates, 0, glm::vec3(1,0,0), 0.1);
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
