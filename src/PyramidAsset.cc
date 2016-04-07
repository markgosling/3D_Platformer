#include "PyramidAsset.h"

/**
 * @file PyramidAsset.cc
 * @version 1.0
 *
 * @section Description
 *
 * PyramidAsset extends GameAsset with variables and methods which
 * are used to draw a pyramid object on screen. It also stores the
 * bounding box for the pyramid, sets the asset type and passes the
 * vertices to the GPU.
 */

/**
 * Constructor which sets the position of each of the vertices required to create the pyramid,
 * stores them in a buffer then transfers them to the GPU. It also stores the type of asset
 * and the size of the bounding box.
 *
 * @param x_position - float - The center X position of the asset.
 * @param y_position - float - The center Y position of the asset.
 * @param z_position - float - The center Z position of the asset.
 */
PyramidAsset::PyramidAsset(float x_position, float y_position, float z_position) : GameAsset(x_position, y_position, z_position) {

	//Model coordinates with origin at centre.
	GLfloat vertex_buffer_data [] {

			//Position of vertices for the top of the pyramid.
			0, 0.5, 0,          //0

			//Position of vertices for the bottom front of the pyramid.
			-0.5, -0.5, 0.5,   //1
			0.5, -0.5, 0.5,    //2

			//Position of vertices for the bottom back of the pyramid.
			-0.5, -0.5, -0.5,  //3
			0.5, -0.5, -0.5,   //4

	};

	element_buffer_length = 12;
	GLuint element_buffer []  {

			//Put pyramid front side vertices in element buffer.
			0, 1, 2, //Pyramid front.
			0, 3, 4, //Pyramid back.
			0, 1, 3, //Pyramid left side.
			0, 2, 4  //Pyramid right side.
	};

	//Transfer buffers to the GPU.

	//Create buffer.
	glGenBuffers(1, &vertex_buffer_token);

	//Immediately bind the buffer and transfer the data.
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_token);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 15, vertex_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &element_buffer_token);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_token);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * element_buffer_length, element_buffer, GL_STATIC_DRAW);

	///Set the asset type. This is required to determine the object type
	//when deciding which shader program to use to colour the object.
	assetType = PYRAMID;

	//Set values used to create the bounding box around the asset.
	this->width = 1;
	this->depth = 1;
	this->height = 1;
}

/**
 * Unused destructor.
 */
PyramidAsset::~PyramidAsset() {
}

