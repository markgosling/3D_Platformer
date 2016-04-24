#include <boost/python.hpp>
#include "PythonBindings.h"
#include "GameAssetManager.h"
#include "CubeAsset.h"
#include "PyramidAsset.h"
#include "GameLoop.h"
#include "common.h"

using namespace boost::python;

/*
 * PythonBindings.cc
 *
 *  Created on: 20 Apr 2016
 *      Author: mark
 *
 * @section Description
 *
 * The PythonBindings class sets up the Python bindings, allowing methods
 * to be accessed and used from within the Python language.
 */

/**
 * Unused constructor.
 */
PythonBindings::PythonBindings(){

}

/**
 * Module which tells Python the name of the module and which exposes the correct classes.
 */
BOOST_PYTHON_MODULE(lib3dplatformer){

	class_<GameAssetManager>("GameAssetManager")
			.def("GetNumberOfAssets", &GameAssetManager::GetNumberOfAssets)
			.def("AddCube", &GameAssetManager::AddCube)
			.def("AddPyramid", &GameAssetManager::AddPyramid)
			.def("AddAnimationPathCoordinates", &GameAssetManager::AddAnimationPathCoordinates)
			.def("ClearAnimationPathCoordinates", &GameAssetManager::ClearAnimationPathCoordinates)
			.def("SetRotationParameters", &GameAssetManager::SetRotationParameters)
			.def("ClearRotationParameters", &GameAssetManager::ClearRotationParameters)
			.def("SetAnimationParameters", &GameAssetManager::SetAnimationParameters)
			.def("UpdateCameraPosition", &GameAssetManager::UpdateCameraPosition)
	;

	class_<GameLoop>("GameLoop")
			.def("Run", &GameLoop::Run)
	;
}
