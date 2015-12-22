#include <GameAsset.h>

/*
 * GameAsset.cc
 *
 *  Created on: 21 Dec 2015
 *      Author: mark
 */

bool DetectXCollision(){
	return 0;
}


bool DetectZCollision(){
	return 0;
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
