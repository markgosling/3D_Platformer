#include "GameWorld.h"

using namespace std;

GameWorld::GameWorld (ApplicationMode mode) {
  asset_manager = make_shared<GameAssetManager>(mode);
  asset_manager->AddAsset(make_shared<CubeAsset>());
}

void GameWorld::Draw() {
  asset_manager->Draw();
}
