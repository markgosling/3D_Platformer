#include "GameWorld.h"
#include <string>

using namespace std;

GameWorld::GameWorld () {

  asset_manager = make_shared<GameAssetManager>();

  //Add the blocks to make the ground.
  asset_manager->AddAsset(make_shared<CubeAsset>(), 0, 0, 0);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 1, 0, 0);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 2, 0, 0);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 3, 0, 0);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 4, 0, 0);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 5, 0, 0);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 6, 0, 0);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 7, 0, 0);

  asset_manager->AddAsset(make_shared<CubeAsset>(), 0, 0, 1);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 1, 0, 1);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 2, 0, 1);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 3, 0, 1);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 4, 0, 1);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 5, 0, 1);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 6, 0, 1);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 7, 0, 1);

  asset_manager->AddAsset(make_shared<CubeAsset>(), 0, 0, 2);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 1, 0, 2);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 2, 0, 2);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 3, 0, 2);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 4, 0, 2);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 5, 0, 2);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 6, 0, 2);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 7, 0, 2);

  asset_manager->AddAsset(make_shared<CubeAsset>(), 0, 0, 3);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 1, 0, 3);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 2, 0, 3);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 3, 0, 3);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 4, 0, 3);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 5, 0, 3);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 6, 0, 3);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 7, 0, 3);

  asset_manager->AddAsset(make_shared<CubeAsset>(), 0, 0, 4);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 1, 0, 4);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 2, 0, 4);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 3, 0, 4);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 4, 0, 4);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 5, 0, 4);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 6, 0, 4);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 7, 0, 4);

  asset_manager->AddAsset(make_shared<CubeAsset>(), 0, 0, 5);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 1, 0, 5);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 2, 0, 5);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 3, 0, 5);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 4, 0, 5);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 5, 0, 5);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 6, 0, 5);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 7, 0, 5);

  asset_manager->AddAsset(make_shared<CubeAsset>(), 0, 0, 6);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 1, 0, 6);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 2, 0, 6);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 3, 0, 6);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 4, 0, 6);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 5, 0, 6);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 6, 0, 6);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 7, 0, 6);

  asset_manager->AddAsset(make_shared<CubeAsset>(), 0, 0, 7);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 1, 0, 7);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 2, 0, 7);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 3, 0, 7);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 4, 0, 7);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 5, 0, 7);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 6, 0, 7);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 7, 0, 7);

  asset_manager->AddAsset(make_shared<CubeAsset>(), 0, 0, 8);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 1, 0, 8);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 2, 0, 8);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 3, 0, 8);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 4, 0, 8);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 5, 0, 8);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 6, 0, 8);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 7, 0, 8);

  asset_manager->AddAsset(make_shared<CubeAsset>(), 0, 0, 9);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 1, 0, 9);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 2, 0, 9);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 3, 0, 9);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 4, 0, 9);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 5, 0, 9);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 6, 0, 9);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 7, 0, 9);

  asset_manager->AddAsset(make_shared<CubeAsset>(), 0, 0, 10);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 1, 0, 10);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 2, 0, 10);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 3, 0, 10);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 4, 0, 10);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 5, 0, 10);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 6, 0, 10);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 7, 0, 10);

  //Add the pillars in the screen position furtherest from the player.
  asset_manager->AddAsset(make_shared<CubeAsset>(), 1, 1, 10);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 6, 1, 10);

  asset_manager->AddAsset(make_shared<CubeAsset>(), 1, 2, 10);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 6, 2, 10);

  asset_manager->AddAsset(make_shared<PyramidAsset>(), 1, 3, 10);
  asset_manager->AddAsset(make_shared<PyramidAsset>(), 6, 3, 10);

  //Add the pillars in the screen position closest to the player.
  asset_manager->AddAsset(make_shared<CubeAsset>(), 1, 1, 0);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 6, 1, 0);

  asset_manager->AddAsset(make_shared<CubeAsset>(), 1, 2, 0);
  asset_manager->AddAsset(make_shared<CubeAsset>(), 6, 2, 0);

  asset_manager->AddAsset(make_shared<PyramidAsset>(), 1, 3, 0);
  asset_manager->AddAsset(make_shared<PyramidAsset>(), 6, 3, 0);

  //Add the two pyramids in the middle/sides of the game world.
  asset_manager->AddAsset(make_shared<PyramidAsset>(), 0, 1, 5);
  asset_manager->AddAsset(make_shared<PyramidAsset>(), 7, 1, 5);

}

void GameWorld::Draw() {
  asset_manager->Draw();
}

void GameWorld::UpdateCameraPosition(InputDirection input_direction, int mouse_x, int mouse_y){

 asset_manager->UpdateCameraPosition(input_direction, mouse_x, mouse_y);

}



