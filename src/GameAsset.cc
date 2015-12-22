#include "GameAsset.h"
#include "GameAssetManager.h"

/*
 * GameAsset.cc
 *
 *  Created on: 21 Dec 2015
 *      Author: mark
 */

CollisionType GameAsset::DetectCollision(float camera_left, float camera_right, float camera_top, float camera_bottom, float camera_front, float camera_back){

	//If all three methods return true, then we know the camera has collided with
	//an object and we need to check which side of the asset has been collided with.
	//if(DetectXCollision(camera_x_position) &&
	//		DetectYCollision(camera_y_position) &&
	//		DetectZCollision(camera_z_position)){

		std::cout << "Camera left: " << camera_left << std::endl;
		std::cout << "Camera right: " << camera_right << std::endl;
		std::cout << "Camera top: " << camera_top << std::endl;
		std::cout << "Camera bottom: "<< camera_bottom << std::endl;
		std::cout << "Camera front: "<< camera_front << std::endl;
		std::cout << "Camera back: "<< camera_back << std::endl;

		float left_side_test;
		float right_side_test;
		float top_side_test;
		float bottom_side_test;
		float front_side_test;
		float back_side_test;

		//Find the distance between the camera X position and the left side of the cube.
		//left_side_test = camera_x_position - (x_position - (width/2));
		//std::cout << "left " << left_side_test << std::endl;

		//Find the distance between the camera X position and the right side of the cube.
		//right_side_test = camera_x_position - (x_position + (width/2));
		//std::cout << "right " << right_side_test << std::endl;

		//Find the distance between the camera Z position and the front side of the cube.
		//front_side_test  = camera_z_position - (z_position - (depth/2));
		//std::cout << "front " << front_side_test << std::endl;

		//Find the distance between the camera Z position and the back side of the cube.
		//back_side_test = camera_z_position - (z_position + (depth/2));
		//std::cout << "back " << back_side_test << std::endl;

		//These tests are disabled as they are not currently required.
		//bottom_side_test = camera_y_position - (y_position - (height/2));
		//top_side_test  = camera_y_position - (y_position + (height/2));

		if(left_side_test < right_side_test && left_side_test < front_side_test && left_side_test < back_side_test){
			//std::cout << "right side collision" << std::endl;
		}else if(right_side_test < left_side_test && right_side_test < front_side_test && right_side_test < back_side_test){
			//std::cout << "left side collision" << std::endl;
		}else if(front_side_test < left_side_test && front_side_test < right_side_test && front_side_test < back_side_test){
			//std::cout << "back side collision" << std::endl;
		}else if(back_side_test < front_side_test && back_side_test < left_side_test && back_side_test < right_side_test){
			//std::cout << "front side collision" << std::endl;
		}else{
			//std::cout << "no collision" << std::endl;
			return NOCOLLISION;
		}


	//}
	return NOCOLLISION;
}

bool GameAsset::DetectXCollision(float camera_x_position){
	//std::cout << "camera_x_position: " << camera_x_position << std::endl;
	//std::cout << "x_position: " << x_position << std::endl;
	//std::cout << "width/2: " << width/2 << std::endl;

	if(camera_x_position > x_position - (width/2) && camera_x_position < x_position + (width/2)){
		//std::cout << "X collision detected" << std::endl;
		return true;
	}
	return false;
}

bool GameAsset::DetectYCollision(float camera_y_position){
	//std::cout << "camera_y_position: " << camera_y_position << std::endl;
	//std::cout << "y_position: " << y_position << std::endl;
	if(camera_y_position >= y_position - (height/2) && camera_y_position <= y_position + (height/2)){
	    //std::cout << "y collision detected" << std::endl;
		return true;
	}
	return false;
}


bool GameAsset::DetectZCollision(float camera_z_position){
	//std::cout << "camera_z_position: " << camera_z_position << std::endl;
	//std::cout << "z_position: " << z_position << std::endl;
	if(camera_z_position > z_position - (depth/2) && camera_z_position < z_position + (depth/2)){
		//std::cout << "z collision detected" << std::endl;
		return true;
	}
	return false;
}

#ifdef DEBUG
#define checkGLError() checkError(__FILE__, __LINE__)
#else
// define symbol to be nothing
#define checkGLError()
#endif

void GameAsset::Draw(GLuint program_token) {

  if(!glIsProgram(program_token)) {
    std::cerr << "Drawing asset with invalid program" << std::endl;
    return;
  }

  GLint validation_ok;
  glValidateProgram(program_token);
  glGetProgramiv(program_token, GL_VALIDATE_STATUS, &validation_ok);

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

  GLuint position_attrib = glGetAttribLocation(program_token, "position");
  checkGLError();

  glUseProgram(program_token);
  checkGLError();

  // use the previously transferred buffer as the vertex array.  This way
  // we transfer the buffer once -- at construction -- not on every frame.
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

  checkGLError();

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

GameAsset::AssetType GameAsset::GetAssetType(){
	return assetType;
}



void checkError(std::string file, int line) {
  GLenum gl_error = glGetError();
  if(GL_NO_ERROR != gl_error) {
    std::cerr << "GL error in " << file << " at line " << line << " error: " << gl_error << std::endl;
    exit(-1);
  }
}
