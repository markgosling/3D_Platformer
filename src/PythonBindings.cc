#include <boost/python.hpp>
#include "PythonBindings.h"
#include "GameAssetManager.h"

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

BOOST_PYTHON_MODULE(libpy3dplatformer){

	class_<PythonBindings>("PythonBindings")
	.def("greet", &PythonBindings::greet);

}

char const* PythonBindings::greet()
{
   return "hello, world";
}


