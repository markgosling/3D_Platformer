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
 * The PythonBindings class sets up the Python bindings, allowing methods
 * to be accessed and used from within the Python language.
 */

/**
 * Unused constructor.
 */
PythonBindings::PythonBindings(){

}


BOOST_PYTHON_MODULE(lib3dplatformer){


	class_<GameAssetManager>("GameAssetManager")
			.def("GetNumberOfAssets", &GameAssetManager::GetNumberOfAssets)
			.def("AddCube", &GameAssetManager::AddCube)
			.def("AddPyramid", &GameAssetManager::AddPyramid);
	;

	class_<GameLoop>("GameLoop")
			.def("Run", &GameLoop::Run)
	;

}

