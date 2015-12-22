#include "GameWorld.h"
#include <string>

using namespace std;

GameWorld::GameWorld () {

  asset_manager = make_shared<GameAssetManager>();

  //Add the blocks to make the ground.
  asset_manager->AddAsset(make_shared<CubeAsset>(0, 0, 0), 0, 0, 0);
  asset_manager->AddAsset(make_shared<CubeAsset>(1, 0, 0), 1, 0, 0);
  asset_manager->AddAsset(make_shared<CubeAsset>(2, 0, 0), 2, 0, 0);
  asset_manager->AddAsset(make_shared<CubeAsset>(3, 0, 0), 3, 0, 0);
  asset_manager->AddAsset(make_shared<CubeAsset>(4, 0, 0), 4, 0, 0);
  asset_manager->AddAsset(make_shared<CubeAsset>(5, 0, 0), 5, 0, 0);
  asset_manager->AddAsset(make_shared<CubeAsset>(6, 0, 0), 6, 0, 0);
  asset_manager->AddAsset(make_shared<CubeAsset>(7, 0, 0), 7, 0, 0);

  asset_manager->AddAsset(make_shared<CubeAsset>(0, 0, 1), 0, 0, 1);
  asset_manager->AddAsset(make_shared<CubeAsset>(1, 0, 1), 1, 0, 1);
  asset_manager->AddAsset(make_shared<CubeAsset>(2, 0, 1), 2, 0, 1);
  asset_manager->AddAsset(make_shared<CubeAsset>(3, 0, 1), 3, 0, 1);
  asset_manager->AddAsset(make_shared<CubeAsset>(4, 0, 1), 4, 0, 1);
  asset_manager->AddAsset(make_shared<CubeAsset>(5, 0, 1), 5, 0, 1);
  asset_manager->AddAsset(make_shared<CubeAsset>(6, 0, 1), 6, 0, 1);
  asset_manager->AddAsset(make_shared<CubeAsset>(7, 0, 1), 7, 0, 1);

  asset_manager->AddAsset(make_shared<CubeAsset>(0, 0, 2), 0, 0, 2);
  asset_manager->AddAsset(make_shared<CubeAsset>(1, 0, 2), 1, 0, 2);
  asset_manager->AddAsset(make_shared<CubeAsset>(2, 0, 2), 2, 0, 2);
  asset_manager->AddAsset(make_shared<CubeAsset>(3, 0, 2), 3, 0, 2);
  asset_manager->AddAsset(make_shared<CubeAsset>(4, 0, 2), 4, 0, 2);
  asset_manager->AddAsset(make_shared<CubeAsset>(5, 0, 2), 5, 0, 2);
  asset_manager->AddAsset(make_shared<CubeAsset>(6, 0, 2), 6, 0, 2);
  asset_manager->AddAsset(make_shared<CubeAsset>(7, 0, 2), 7, 0, 2);

  asset_manager->AddAsset(make_shared<CubeAsset>(0, 0, 3), 0, 0, 3);
  asset_manager->AddAsset(make_shared<CubeAsset>(1, 0, 3), 1, 0, 3);
  asset_manager->AddAsset(make_shared<CubeAsset>(2, 0, 3), 2, 0, 3);
  asset_manager->AddAsset(make_shared<CubeAsset>(3, 0, 3), 3, 0, 3);
  asset_manager->AddAsset(make_shared<CubeAsset>(4, 0, 3), 4, 0, 3);
  asset_manager->AddAsset(make_shared<CubeAsset>(5, 0, 3), 5, 0, 3);
  asset_manager->AddAsset(make_shared<CubeAsset>(6, 0, 3), 6, 0, 3);
  asset_manager->AddAsset(make_shared<CubeAsset>(7, 0, 3), 7, 0, 3);

  asset_manager->AddAsset(make_shared<CubeAsset>(0, 0, 4), 0, 0, 4);
  asset_manager->AddAsset(make_shared<CubeAsset>(1, 0, 4), 1, 0, 4);
  asset_manager->AddAsset(make_shared<CubeAsset>(2, 0, 4), 2, 0, 4);
  asset_manager->AddAsset(make_shared<CubeAsset>(3, 0, 4), 3, 0, 4);
  asset_manager->AddAsset(make_shared<CubeAsset>(4, 0, 4), 4, 0, 4);
  asset_manager->AddAsset(make_shared<CubeAsset>(5, 0, 4), 5, 0, 4);
  asset_manager->AddAsset(make_shared<CubeAsset>(6, 0, 4), 6, 0, 4);
  asset_manager->AddAsset(make_shared<CubeAsset>(7, 0, 4), 7, 0, 4);

  asset_manager->AddAsset(make_shared<CubeAsset>(0, 0, 5), 0, 0, 5);
  asset_manager->AddAsset(make_shared<CubeAsset>(1, 0, 5), 1, 0, 5);
  asset_manager->AddAsset(make_shared<CubeAsset>(2, 0, 5), 2, 0, 5);
  asset_manager->AddAsset(make_shared<CubeAsset>(3, 0, 5), 3, 0, 5);
  asset_manager->AddAsset(make_shared<CubeAsset>(4, 0, 5), 4, 0, 5);
  asset_manager->AddAsset(make_shared<CubeAsset>(5, 0, 5), 5, 0, 5);
  asset_manager->AddAsset(make_shared<CubeAsset>(6, 0, 5), 6, 0, 5);
  asset_manager->AddAsset(make_shared<CubeAsset>(7, 0, 5), 7, 0, 5);

  asset_manager->AddAsset(make_shared<CubeAsset>(0, 0, 6), 0, 0, 6);
  asset_manager->AddAsset(make_shared<CubeAsset>(1, 0, 6), 1, 0, 6);
  asset_manager->AddAsset(make_shared<CubeAsset>(2, 0, 6), 2, 0, 6);
  asset_manager->AddAsset(make_shared<CubeAsset>(3, 0, 6), 3, 0, 6);
  asset_manager->AddAsset(make_shared<CubeAsset>(4, 0, 6), 4, 0, 6);
  asset_manager->AddAsset(make_shared<CubeAsset>(5, 0, 6), 5, 0, 6);
  asset_manager->AddAsset(make_shared<CubeAsset>(6, 0, 6), 6, 0, 6);
  asset_manager->AddAsset(make_shared<CubeAsset>(7, 0, 6), 7, 0, 6);

  asset_manager->AddAsset(make_shared<CubeAsset>(0, 0, 7), 0, 0, 7);
  asset_manager->AddAsset(make_shared<CubeAsset>(1, 0, 7), 1, 0, 7);
  asset_manager->AddAsset(make_shared<CubeAsset>(2, 0, 7), 2, 0, 7);
  asset_manager->AddAsset(make_shared<CubeAsset>(3, 0, 7), 3, 0, 7);
  asset_manager->AddAsset(make_shared<CubeAsset>(4, 0, 7), 4, 0, 7);
  asset_manager->AddAsset(make_shared<CubeAsset>(5, 0, 7), 5, 0, 7);
  asset_manager->AddAsset(make_shared<CubeAsset>(6, 0, 7), 6, 0, 7);
  asset_manager->AddAsset(make_shared<CubeAsset>(7, 0, 7), 7, 0, 7);

  asset_manager->AddAsset(make_shared<CubeAsset>(0, 0, 8), 0, 0, 8);
  asset_manager->AddAsset(make_shared<CubeAsset>(1, 0, 8), 1, 0, 8);
  asset_manager->AddAsset(make_shared<CubeAsset>(2, 0, 8), 2, 0, 8);
  asset_manager->AddAsset(make_shared<CubeAsset>(3, 0, 8), 3, 0, 8);
  asset_manager->AddAsset(make_shared<CubeAsset>(4, 0, 8), 4, 0, 8);
  asset_manager->AddAsset(make_shared<CubeAsset>(5, 0, 8), 5, 0, 8);
  asset_manager->AddAsset(make_shared<CubeAsset>(6, 0, 8), 6, 0, 8);
  asset_manager->AddAsset(make_shared<CubeAsset>(7, 0, 8), 7, 0, 8);

  asset_manager->AddAsset(make_shared<CubeAsset>(0, 0, 9), 0, 0, 9);
  asset_manager->AddAsset(make_shared<CubeAsset>(1, 0, 9), 1, 0, 9);
  asset_manager->AddAsset(make_shared<CubeAsset>(2, 0, 9), 2, 0, 9);
  asset_manager->AddAsset(make_shared<CubeAsset>(3, 0, 9), 3, 0, 9);
  asset_manager->AddAsset(make_shared<CubeAsset>(4, 0, 9), 4, 0, 9);
  asset_manager->AddAsset(make_shared<CubeAsset>(5, 0, 9), 5, 0, 9);
  asset_manager->AddAsset(make_shared<CubeAsset>(6, 0, 9), 6, 0, 9);
  asset_manager->AddAsset(make_shared<CubeAsset>(7, 0, 9), 7, 0, 9);

  asset_manager->AddAsset(make_shared<CubeAsset>(0, 0, 10), 0, 0, 10);
  asset_manager->AddAsset(make_shared<CubeAsset>(1, 0, 10), 1, 0, 10);
  asset_manager->AddAsset(make_shared<CubeAsset>(2, 0, 10), 2, 0, 10);
  asset_manager->AddAsset(make_shared<CubeAsset>(3, 0, 10), 3, 0, 10);
  asset_manager->AddAsset(make_shared<CubeAsset>(4, 0, 10), 4, 0, 10);
  asset_manager->AddAsset(make_shared<CubeAsset>(5, 0, 10), 5, 0, 10);
  asset_manager->AddAsset(make_shared<CubeAsset>(6, 0, 10), 6, 0, 10);
  asset_manager->AddAsset(make_shared<CubeAsset>(7, 0, 10), 7, 0, 10);

  //Add the pillars in the screen position furtherest from the player.
  asset_manager->AddAsset(make_shared<CubeAsset>(1, 1, 10), 1, 1, 10);
  asset_manager->AddAsset(make_shared<CubeAsset>(6, 1, 10), 6, 1, 10);

  asset_manager->AddAsset(make_shared<CubeAsset>(1, 2, 10), 1, 2, 10);
  asset_manager->AddAsset(make_shared<CubeAsset>(6, 2, 10), 6, 2, 10);

  asset_manager->AddAsset(make_shared<PyramidAsset>(1, 3, 10), 1, 3, 10);
  asset_manager->AddAsset(make_shared<PyramidAsset>(6, 3, 10), 6, 3, 10);

  //Add the pillars in the screen position closest to the player.
  asset_manager->AddAsset(make_shared<CubeAsset>(1, 1, 0), 1, 1, 0);
  asset_manager->AddAsset(make_shared<CubeAsset>(6, 1, 0), 6, 1, 0);

  asset_manager->AddAsset(make_shared<CubeAsset>(1, 2, 0), 1, 2, 0);
  asset_manager->AddAsset(make_shared<CubeAsset>(6, 2, 0), 6, 2, 0);

  asset_manager->AddAsset(make_shared<PyramidAsset>(1, 3, 0), 1, 3, 0);
  asset_manager->AddAsset(make_shared<PyramidAsset>(6, 3, 0), 6, 3, 0);

  //Add the two pyramids in the middle/sides of the game world.
  asset_manager->AddAsset(make_shared<PyramidAsset>(0, 1, 5), 0, 1, 5);
  asset_manager->AddAsset(make_shared<PyramidAsset>(7, 1, 5), 7, 1, 5);

}

void GameWorld::Draw() {
  asset_manager->Draw();
}

void GameWorld::UpdateCameraPosition(InputDirection input_direction, int mouse_x, int mouse_y){

 asset_manager->UpdateCameraPosition(input_direction, mouse_x, mouse_y);

}



