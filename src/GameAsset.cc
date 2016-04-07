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



//new code
GameAsset::GameAsset(float x_position, float y_position, float z_position){


	boundingBox = std::make_shared<BoundingBox>(x_position, y_position, z_position);
	this->x_position = x_position;
	this->y_position = y_position;
	this->z_position = z_position;


}

glm::mat4 GameAsset::GetTranslationMatrix(){
	return boundingBox->GetTranslationMatrix();
}

/**
 * The 'DetectCollision' method is used to detect a collision between the camera and
 * the game object. It compares each side of the cameras bounding box to the sides of
 * the asset being checked to work out if a collision has occurred, then calculates which
 * side of the asset was collided with. It returns an Enum with the side of the asset where
 * the collision occurred.
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

	//Call the methods which check for collisions on the X, Y and Z coordinates of the asset.
	//If all three methods return true, then we know the camera has collided with
	//an object and we need to check which side of the asset has been collided with.
	if(DetectXCollision(camera_left, camera_right) &&
			DetectYCollision(camera_top, camera_bottom) &&
			DetectZCollision(camera_front, camera_back)){

		//Find the distance between the camera right side and the left side of the asset.
		left_side_test = camera_right - (x_position - (width/2));

		//Find the distance between the camera left side and the right side of the asset.
		right_side_test = (x_position + (width/2)) - camera_left;

		//Find the distance between the camera front side and the back side of the asset.
		back_side_test  = camera_front - (z_position - (depth/2));

		//Find the distance between the camera back side and the front side of the asset.
		front_side_test = (z_position + (depth/2)) - camera_back;

		//These tests are disabled as they are not currently required or properly implemented.
		//bottom_side_test = camera_y_position - (y_position - (height/2));
		//top_side_test  = camera_y_position - (y_position + (height/2));

		//Check to see which distance is shortest. The shortest distance between the sides
		//indicates which side of the asset was collided with. Return a value to indicate this.
		if(left_side_test < right_side_test && left_side_test < front_side_test && left_side_test < back_side_test){
			return LEFTSIDE;
		}else if(right_side_test < left_side_test && right_side_test < front_side_test && right_side_test < back_side_test){
			return RIGHTSIDE;
		}else if(front_side_test < left_side_test && front_side_test < right_side_test && front_side_test < back_side_test){
			return FRONTSIDE;
		}else if(back_side_test < front_side_test && back_side_test < left_side_test && back_side_test < right_side_test){
			return BACKSIDE;
		}else{
			return NOCOLLISION;
		}
	}
	return NOCOLLISION;
}

/**
 * Detects if the cameras boundary box is within the width of the asset.
 *
 * @param camera_left - float - The coordinate for the left side of the cameras boundary box.
 * @param camera_right - float - The coordinate for the right side of the cameras boundary box.
 *
 * @return true if a collision was detected, otherwise false.
 */
bool GameAsset::DetectXCollision(float camera_left, float camera_right){

	if(camera_right > x_position - (width/2) && camera_left < x_position + (width/2)){
		return true;
	}
	return false;
}

/**
 * Detects if the cameras boundary box is within the height of the asset.
 *
 * @param camera_top - float - The coordinate for the top side of the cameras boundary box.
 * @param camera_bottom - float - The coordinate for the bottom side of the cameras boundary box.
 *
 * @return true if a collision was detected, otherwise false.
 */
bool GameAsset::DetectYCollision(float camera_top, float camera_bottom){

	if(camera_top > y_position - (height/2) && camera_bottom < y_position + (height/2)){
		return true;
	}
	return false;
}

/**
 * Detects if the cameras boundary box is within the width of the asset.
 *
 * @param camera_front - float - The coordinate for the front side of the cameras boundary box.
 * @param camera_back - float - The coordinate for the back side of the cameras boundary box.
 *
 * @return true if a collision was detected, otherwise false.
 */
bool GameAsset::DetectZCollision(float camera_front, float camera_back){

	if(camera_front > z_position - (depth/2) && camera_back < z_position + (depth/2)){
		return true;
	}
	return false;
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
