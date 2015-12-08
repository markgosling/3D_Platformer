#include "GameWorld.h"
#include <string>

using namespace std;

GameWorld::GameWorld (ApplicationMode mode) {

  asset_manager = make_shared<GameAssetManager>(mode);

  asset_manager->AddAsset(make_shared<CubeAsset>());

  asset_manager->AddAsset(make_shared<PyramidAsset>());

}

void GameWorld::Draw() {
  asset_manager->Draw();
}

void GameWorld::UpdateCameraPosition(InputDirection input_direction, int mouse_x, int mouse_y){

 asset_manager->UpdateCameraPosition(input_direction, mouse_x, mouse_y);

}

