#include "GameAsset.h"
#include "GameAssetManager.h"

#include "BoundingBox.h"
#include <memory>

/**
 * @file GameAsset.cc
 * @version 1.0
 *
 * @section Description
 *
 * GameAsset is a superclass which forms the base for all 3D assets used
 * in the game. It has methods which are common to all objects, including
 * methods to implement collision detection, to find the asset type and
 * also to draw the asset on screen.
 */



/**
 * Constructor which takes in the X, Y, Z position of the asset along with the scaling amount. It also
 * takes in the rotation in degrees around the X, Y and Z axis. It then creates an instance of a bounding
 * box and passes it information about the assets position.
 *
 * @param x_position - float - The center X position of the asset.
 * @param y_position - float - The center Y position of the asset.
 * @param z_position - float - The center Z position of the asset.
 * @param scale - float - The amount the asset should be scaled by.
 * @param x_rotation - float - The amount in degrees in which to rotate around the X axis.
 * @param y_rotation - float - The amount in degrees in which to rotate around the Y axis.
 * @param z_rotation - float - The amount in degrees in which to rotate around the Z axis.
 */
GameAsset::GameAsset(float x_position, float y_position, float z_position, float scale,
		float x_rotation, float y_rotation, float z_rotation){

	boundingBox = std::make_shared<BoundingBox>(x_position, y_position, z_position, scale, x_rotation, y_rotation, z_rotation);
}


/**
 * Method which calls a method in the bounding box and returns a matrix containing the final
 * information about the models position, scale and rotation.
 *
 * @return a mat4 matrix containing the complete model position transformation.
 */
glm::mat4 GameAsset::GetCompleteModelTransformationMatrix(){
	return boundingBox->GetCompleteModelTransformationMatrix();
}


/**
 * The 'DetectCollision' method acts as a pass-through to send the position of the sides
 * of the cameras bounding box to the bounding box of the asset. It returns an Enum containing
 * the side of the asset where the camera and asset collided, if at all.
 *
 * @param camera_left - float - The left side of the cameras boundary box.
 * @param camera_right- float - The right side of the cameras boundary box.
 * @param camera_top- float - The top side of the cameras boundary box.
 * @param camera_bottom- float - The bottom side of the cameras boundary box.
 * @param camera_front- float - The front side of the cameras boundary box.
 * @param camera_back- float - The back side of the cameras boundary box.
 *
 * @return an Enum indicating which side of the asset was collided with. Return 'NOCOLLISION'
 * 	if no collision was detected.
 */
CollisionType GameAsset::DetectCollision(float camera_left, float camera_right, float camera_top,
		float camera_bottom, float camera_front, float camera_back){

	return boundingBox->DetectCollision(camera_left, camera_right, camera_top, camera_bottom, camera_front, camera_back);
}


//Define a 'checkGLError' method if not already defined.
#ifdef DEBUG
#define checkGLError() checkError(__FILE__, __LINE__)
#else
// define symbol to be nothing
#define checkGLError()
#endif


/**
 * The 'Draw' method is used to draw each asset individually using the shader
 * program passed as a parameter.
 *
 * @param program_token - GLuint - A token used to access the shader program.
 */
void GameAsset::Draw(GLuint program_token) {

	//Check that the program token points to a valid shader program.
	if(!glIsProgram(program_token)) {
		std::cerr << "Drawing asset with invalid program" << std::endl;
		return;
	}

	//Validate the shader program.
	GLint validation_ok;
	glValidateProgram(program_token);
	glGetProgramiv(program_token, GL_VALIDATE_STATUS, &validation_ok);

	//If validation fails then display an error and return -1.
	if(!validation_ok) {
		GLint maxLength = 0;
		glGetProgramiv(program_token, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<char> errorLog(maxLength);
		glGetProgramInfoLog(program_token, maxLength, &maxLength, &errorLog[0]);

		std::cerr << "Invalid program " << program_token << " with error code " << validation_ok << std::endl;
		for(auto c: errorLog) {
			std::cerr << c;
		}
		exit(-1);
	}

	//Link to the 'position' variable inside the shader program.
	GLuint position_attrib = glGetAttribLocation(program_token, "position");
	checkGLError();

	//Tell openGL that we are using this shader program.
	glUseProgram(program_token);
	checkGLError();

	//Use the previously transferred buffer as the vertex array.  This way
	//we transfer the buffer once -- at construction -- not on every frame.
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_token);
	glVertexAttribPointer(
			position_attrib,               /* attribute */
			3,                             /* size */
			GL_FLOAT,                      /* type */
			GL_FALSE,                      /* normalized? */
			0,                             /* stride */
			(void*)0                       /* array buffer offset */
	);
	glEnableVertexAttribArray(position_attrib);

	//Check for problems.
	checkGLError();

	//Draw the triangles stored in the element buffer on screen.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_token);
	glDrawElements(
			GL_TRIANGLES,
			element_buffer_length,
			GL_UNSIGNED_INT,
			(GLvoid*) 0
	);

	checkGLError();

	glDisableVertexAttribArray(position_attrib);
}

/**
 * Return the Enum containing the type of asset (CUBE, PYRAMID, etc).
 *
 * @return the AssetType with the value indicating the type of asset.
 */
GameAsset::AssetType GameAsset::GetAssetType(){
	return assetType;
}

/**
 * Checks for errors and displays the error message on the console.
 *
 * @param file - String - The location of the file to check for errors.
 * @param line - Integer - The line to check for errors.
 */
void checkError(std::string file, int line) {
	GLenum gl_error = glGetError();
	if(GL_NO_ERROR != gl_error) {
		std::cerr << "GL error in " << file << " at line " << line << " error: " << gl_error << std::endl;
		exit(-1);
	}
}
