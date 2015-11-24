#include "GameWorld.h"
#include <string>

using namespace std;

GameWorld::GameWorld (ApplicationMode mode) {
 // string vertex_shader1 = "shaders/camera.vs";
 // string vertex_shader2 = "shaders/camera.vs";
 // string fragment_shader = "shaders/fragment.fs";

  asset_manager = make_shared<GameAssetManager>(mode);

 // asset_manager-> CreateGLProgram(vertex_shader1, fragment_shader);

  asset_manager->AddAsset(make_shared<CubeAsset>());

 // asset_manager-> CreateGLProgram(vertex_shader2, fragment_shader);

  asset_manager->AddAsset(make_shared<PyramidAsset>());
}

void GameWorld::Draw() {
  asset_manager->Draw();
}
