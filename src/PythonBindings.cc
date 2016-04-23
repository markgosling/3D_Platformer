#include <boost/python.hpp>
#include "PythonBindings.h"
#include "GameAssetManager.h"
#include "CubeAsset.h"
#include "PyramidAsset.h"
#include "common.h"

using namespace boost::python;

/*
 * PythonBindings.cc
 *
 *  Created on: 20 Apr 2016
 *      Author: mark
 *
 * The PythonBindings class sets up the Python Bindings allowing various methods
 * to be accessed and used from within the Python language.
 */

/**
 * Unused constructor.
 */
PythonBindings::PythonBindings(){

}

/**
 * Method which is called to allow a shared pointer to GameAssetManager to be set.
 *
 * @param asset_manager - shared_ptr - A shared pointer to GameAssetManager.
 */
void PythonBindings::SetAssetManagerPointer(std::shared_ptr<GameAssetManager> asset_manager){
	this->asset_manager = asset_manager;
}

BOOST_PYTHON_MODULE(lib3dplatformer){

	class_<PythonBindings>("PythonBindings")
			//.def("AddCube", &PythonBindings::AddCube)
			.def("AddPyramid", &PythonBindings::AddPyramid)
	;

	class_<GameAssetManager>("GameAssetManager")
			//.def("AddCube", &PythonBindings::AddCube)
			.def("AddCube", &GameAssetManager::AddCube)
			.def("GetNumberOfAssets", &GameAssetManager::GetNumberOfAssets)
	;


}

void PythonBindings::AddCube(float x_pos, float y_pos, float z_pos, float scale, float x_rot, float y_rot, float z_rot){

	asset_manager->AddAsset(std::make_shared<CubeAsset>(x_pos, y_pos, z_pos, scale, x_rot, y_rot, z_rot));

}

void PythonBindings::AddPyramid(float x_pos, float y_pos, float z_pos, float scale, float x_rot, float y_rot, float z_rot){

	asset_manager->AddAsset(std::make_shared<PyramidAsset>(x_pos, y_pos, z_pos, scale, x_rot, y_rot, z_rot));

}
/**
void PythonBindings::SetAnimationParameters(std::vector<glm::vec3> target_coordinates_array,
		float movement_speed, glm::vec3 rotation_axis, float rotation_speed){

}
**/

