#include "common.h"
#include "GameAssetManager.h"
#include <memory>

/*
* PythonBindings.h
 *
 *  Created on: 20 Apr 2016
 *      Author: mark
 *
 * The PythonBindings class creates a module which can be imported into Python to give it access
 * to the c++ code functions. It also contains helper methods which are used to create an API for
 * the Python module.
 */

#ifndef SRC_PYTHONBINDINGS_H_
#define SRC_PYTHONBINDINGS_H_

class PythonBindings{

public:
	PythonBindings();
	void SetAssetManagerPointer(std::shared_ptr<GameAssetManager>);
	void AddCube(float, float, float, float, float, float, float);
	void AddPyramid(float, float, float, float, float, float, float);

private:
	std::shared_ptr<GameAssetManager> asset_manager;

};



#endif /* SRC_PYTHONBINDINGS_H_ */
