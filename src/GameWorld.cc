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

	//Add the assets to make the game world. The X, Y, Z coordinates are passed
	//to both the constructor of the asset upon creation and also to the
	//'AddAsset' method of 'GameAssetManager'.

	//Add the blocks required to make the ground.
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(0, 0, 0), 0, 0, 0);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(1, 0, 0), 1, 0, 0);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(2, 0, 0), 2, 0, 0);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(3, 0, 0), 3, 0, 0);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(4, 0, 0), 4, 0, 0);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(5, 0, 0), 5, 0, 0);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(6, 0, 0), 6, 0, 0);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(7, 0, 0), 7, 0, 0);

	//asset_manager->AddAsset(std::make_shared<CubeAsset>(0, 0, 1), 0, 0, 1);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(1, 0, 1), 1, 0, 1);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(2, 0, 1), 2, 0, 1);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(3, 0, 1), 3, 0, 1);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(4, 0, 1), 4, 0, 1);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(5, 0, 1), 5, 0, 1);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(6, 0, 1), 6, 0, 1);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(7, 0, 1), 7, 0, 1);

	//asset_manager->AddAsset(std::make_shared<CubeAsset>(0, 0, 2), 0, 0, 2);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(1, 0, 2), 1, 0, 2);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(2, 0, 2), 2, 0, 2);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(3, 0, 2), 3, 0, 2);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(4, 0, 2), 4, 0, 2);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(5, 0, 2), 5, 0, 2);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(6, 0, 2), 6, 0, 2);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(7, 0, 2), 7, 0, 2);

	//asset_manager->AddAsset(std::make_shared<CubeAsset>(0, 0, 3), 0, 0, 3);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(1, 0, 3), 1, 0, 3);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(2, 0, 3), 2, 0, 3);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(3, 0, 3), 3, 0, 3);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(4, 0, 3), 4, 0, 3);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(5, 0, 3), 5, 0, 3);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(6, 0, 3), 6, 0, 3);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(7, 0, 3), 7, 0, 3);

	//asset_manager->AddAsset(std::make_shared<CubeAsset>(0, 0, 4), 0, 0, 4);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(1, 0, 4), 1, 0, 4);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(2, 0, 4), 2, 0, 4);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(3, 0, 4), 3, 0, 4);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(4, 0, 4), 4, 0, 4);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(5, 0, 4), 5, 0, 4);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(6, 0, 4), 6, 0, 4);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(7, 0, 4), 7, 0, 4);

	//asset_manager->AddAsset(std::make_shared<CubeAsset>(0, 0, 5), 0, 0, 5);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(1, 0, 5), 1, 0, 5);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(2, 0, 5), 2, 0, 5);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(3, 0, 5), 3, 0, 5);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(4, 0, 5), 4, 0, 5);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(5, 0, 5), 5, 0, 5);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(6, 0, 5), 6, 0, 5);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(7, 0, 5), 7, 0, 5);

	//asset_manager->AddAsset(std::make_shared<CubeAsset>(0, 0, 6), 0, 0, 6);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(1, 0, 6), 1, 0, 6);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(2, 0, 6), 2, 0, 6);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(3, 0, 6), 3, 0, 6);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(4, 0, 6), 4, 0, 6);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(5, 0, 6), 5, 0, 6);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(6, 0, 6), 6, 0, 6);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(7, 0, 6), 7, 0, 6);

	//asset_manager->AddAsset(std::make_shared<CubeAsset>(0, 0, 7), 0, 0, 7);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(1, 0, 7), 1, 0, 7);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(3, 0, 7), 3, 0, 7);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(4, 0, 7), 4, 0, 7);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(5, 0, 7), 5, 0, 7);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(6, 0, 7), 6, 0, 7);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(7, 0, 7), 7, 0, 7);

	//asset_manager->AddAsset(std::make_shared<CubeAsset>(0, 0, 8), 0, 0, 8);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(1, 0, 8), 1, 0, 8);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(2, 0, 8), 2, 0, 8);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(3, 0, 8), 3, 0, 8);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(4, 0, 8), 4, 0, 8);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(5, 0, 8), 5, 0, 8);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(6, 0, 8), 6, 0, 8);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(7, 0, 8), 7, 0, 8);

	//asset_manager->AddAsset(std::make_shared<CubeAsset>(0, 0, 9), 0, 0, 9);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(1, 0, 9), 1, 0, 9);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(3, 0, 9), 3, 0, 9);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(4, 0, 9), 4, 0, 9);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(5, 0, 9), 5, 0, 9);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(6, 0, 9), 6, 0, 9);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(7, 0, 9), 7, 0, 9);

	//asset_manager->AddAsset(std::make_shared<CubeAsset>(0, 0, 10), 0, 0, 10);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(1, 0, 10), 1, 0, 10);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(2, 0, 10), 2, 0, 10);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(3, 0, 10), 3, 0, 10);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(4, 0, 10), 4, 0, 10);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(5, 0, 10), 5, 0, 10);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(6, 0, 10), 6, 0, 10);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(7, 0, 10), 7, 0, 10);

	//Add the pillars on the screen position furtherest from the player.
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(1, 1, 10), 1, 1, 10);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(6, 1, 10), 6, 1, 10);

	//asset_manager->AddAsset(std::make_shared<CubeAsset>(1, 2, 10), 1, 2, 10);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(6, 2, 10), 6, 2, 10);

	//asset_manager->AddAsset(std::make_shared<PyramidAsset>(1, 3, 10), 1, 3, 10);
	//asset_manager->AddAsset(std::make_shared<PyramidAsset>(6, 3, 10), 6, 3, 10);

	//Add the pillars on the screen position closest to the player.
	asset_manager->AddAsset(std::make_shared<CubeAsset>(1, 1, 0, 1, 0, 0, 0)); //X pos, Y pos, Z pos, scale, X rot, Y rot, Z rot.
	asset_manager->AddAsset(std::make_shared<CubeAsset>(6, 1, 0, 1, 0, 0, 0));

	//asset_manager->AddAsset(std::make_shared<CubeAsset>(1, 2, 0), 1, 2, 0);
	//asset_manager->AddAsset(std::make_shared<CubeAsset>(6, 2, 0), 6, 2, 0);

	//asset_manager->AddAsset(std::make_shared<PyramidAsset>(1, 3, 0), 1, 3, 0);
	//asset_manager->AddAsset(std::make_shared<PyramidAsset>(6, 3, 0), 6, 3, 0);

	//Add the two pyramids in the middle/sides of the game world.
	//asset_manager->AddAsset(std::make_shared<PyramidAsset>(0, 1, 5), 0, 1, 5);
	//asset_manager->AddAsset(std::make_shared<PyramidAsset>(7, 1, 5), 7, 1, 5);
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
