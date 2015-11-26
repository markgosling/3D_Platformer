#include "PyramidAsset.h"

using namespace std;

/**
 * Constructor which sets the position of each
 * of the vertices required to create the pyramid,
 * stores them in a buffer then transfers them
 * to the GPU.
 */
PyramidAsset::PyramidAsset() {

  //Model coordinates with origin at centre.
  GLfloat vertex_buffer_data [] {

	//Position of vertices for the top of the pyramid.
	0, 1.0, 0,          //0

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
}

/**
 * Unused destructor.
 */
PyramidAsset::~PyramidAsset() {
}

#ifdef DEBUG
#define checkGLError() checkError(__FILE__, __LINE__)
#else
// define symbol to be nothing
#define checkGLError()
#endif

void PyramidAsset::checkError(string file, int line) {
  GLenum gl_error = glGetError();
  if(GL_NO_ERROR != gl_error) {
    cerr << "GL error in " << file << " at line " << line << " error: " << gl_error << endl;
    exit(-1);
  }
}

void PyramidAsset::Draw(GLuint program_token) {

  if(!glIsProgram(program_token)) {
    cerr << "Drawing Pyramid with invalid program" << endl;
    return;
  }

  GLint validation_ok;
  glValidateProgram(program_token);
  glGetProgramiv(program_token, GL_VALIDATE_STATUS, &validation_ok);

  if(!validation_ok) {
    GLint maxLength = 0;
    glGetProgramiv(program_token, GL_INFO_LOG_LENGTH, &maxLength);

    //The maxLength includes the NULL character
    vector<char> errorLog(maxLength);
    glGetProgramInfoLog(program_token, maxLength, &maxLength, &errorLog[0]);

    cerr << "Invalid program " << program_token << " with error code " << validation_ok << endl;
    for(auto c: errorLog) {
      cerr << c;
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

GameAsset::AssetType PyramidAsset::GetAssetType(){
	return assetType;
}
