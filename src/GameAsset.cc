#include <GameAsset.h>

/*
 * GameAsset.cc
 *
 *  Created on: 21 Dec 2015
 *      Author: mark
 */

bool GameAsset::DetectCollision(float camera_x_position, float camera_y_position, float camera_z_position){

	if(DetectXCollision(camera_x_position) &&
			DetectYCollision(camera_y_position) &&
			DetectZCollision(camera_z_position)){
		return true;
	}
	return false;
}

bool GameAsset::DetectXCollision(float camera_x_position){
	//std::cout << "camera_x_position: " << camera_x_position << std::endl;
	//std::cout << "x_position: " << x_position << std::endl;
	//std::cout << "width/2: " << width/2 << std::endl;

	if(camera_x_position >= x_position - (width/2) && camera_x_position <= x_position + (width/2)){
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
	if(camera_z_position >= z_position - (depth/2) && camera_z_position <= z_position + (depth/2)){
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
    std::cerr << "Drawing Cube with invalid program" << std::endl;
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
