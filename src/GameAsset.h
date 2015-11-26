#ifndef GAMEASSET_H
#define GAMEASSET_H

#include <iostream>

#include <GL/gl.h>

class GameAsset {

 public:
  enum AssetType {CUBE, PYRAMID};
  virtual void Draw(GLuint) = 0;
  virtual AssetType GetAssetType() = 0;


 protected:
  AssetType assetType;

};

#endif
