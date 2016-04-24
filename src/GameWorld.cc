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

	//Add the assets to make the game world.
	//The constructor to add a new asset is in the form of: X pos, Y pos, Z pos, scale, X rot, Y rot, Z rot.

	//To set the target animation coordinates call asset_manager->AddAnimationPathCoordinates(float x_target, float y_target, float z_target).
	//This method should be called once for each set of targets an object should follow. The coordinates can be cleared using asset_manager->ClearAnimationPathCoordinates().

	//To set the rotation parameters call asset_manager->SetRotationParameters(float x_rotation, float y_rotation, float z_rotation, float rotation_speed).
	//These settings can be cleared by calling asset_manager->ClearRotationParameters().

	//To animate an object with the specified parameters, call asset_manager->SetAnimationParameters(float movement_speed).
	//The movement speed only sets the speed the object moves towards the target speed. Rotation speed is specified separately.

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

	//Set the first pyramid to rotate along the Y axis at a speed of 0.1 and movement speed of 0 (to keep it stationary).
	asset_manager->SetRotationParameters(0, 1, 0, 0.1);
	asset_manager->SetAnimationParameters(0.0);

	//Add a second pyramid to the middle\right side of the game world.
	asset_manager->AddPyramid(7, 1, 5, 1, 0, 0, 0);

	//Set the second pyramid to rotate along the Y axis in the oppositte direction to the first by setting the rotation speed to -0.1.
	asset_manager->SetRotationParameters(0, 1, 0, -0.1);
	asset_manager->SetAnimationParameters(0.0);

	//Add a half size cube above the game world to represent a moving platform.
	asset_manager->AddCube(0, 5, 10, 0.5, 0, 0, 0);

	//Animate the platform by setting coordinates which will cause it to move around the edge of the game world.
	asset_manager->ClearRotationParameters(); //Reset the rotation paramaters set previously.
	asset_manager->AddAnimationPathCoordinates(0,5,0);
	asset_manager->AddAnimationPathCoordinates(7,5,0);
	asset_manager->AddAnimationPathCoordinates(7,5,10);
	asset_manager->AddAnimationPathCoordinates(0,5,10);

	//Set the target coordinates of the platform with a movement speed of 2.
	asset_manager->SetAnimationParameters(2.0);

	//Add a second small cube to the sky.
	asset_manager->AddCube(5, 8, 5, 0.6, 0, 0, 0);

	//Clear the target coordinates and then add new ones to make the cube bounce
	//from the center of the world to one of the pillars, then back to the center before heading towards
	//the next pillar.
	asset_manager->ClearAnimationPathCoordinates();
	asset_manager->AddAnimationPathCoordinates(1,4,0); //Pillar 1.
	asset_manager->AddAnimationPathCoordinates(5, 8, 5); //Center.
	asset_manager->AddAnimationPathCoordinates(6, 4, 0); //Pillar 2.
	asset_manager->AddAnimationPathCoordinates(5, 8, 5); //Center.
	asset_manager->AddAnimationPathCoordinates(6, 4, 10); //Pillar 3.
	asset_manager->AddAnimationPathCoordinates(5, 8, 5); //Center.
	asset_manager->AddAnimationPathCoordinates(1, 4, 10); //Pillar 4.
	asset_manager->AddAnimationPathCoordinates(5, 8, 5); //Center.

	//Set the asset to rotate around all 3 axis at once then
	//pass it the target coordinates with a movement speed of 4.
	asset_manager->SetRotationParameters(1, 1, 1, 0.1);
	asset_manager->SetAnimationParameters(4.0);

	//Add two large cubes to the left of the play field and a rotated pyramid to represent a windmill(?).
	asset_manager->AddCube(-8, 1, 5, 2, 0, 0, 0);
	asset_manager->AddCube(-8, 3, 5, 2, 0, 0, 0);
	asset_manager->AddPyramid(-6.5, 3, 5, 1.5, 0, 0, -1.6);

	//Clear the animation coordinates then call the methods required to rotate the pyramid around its X axis.
	asset_manager->ClearAnimationPathCoordinates();
	asset_manager->SetRotationParameters(1, 0, 0, 0.1);
	asset_manager->SetAnimationParameters(0.0);
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
