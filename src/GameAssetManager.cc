#include "GameAssetManager.h"

// Required to fix build issue on Windows and cygwin using 'make'
//which was returning "error: exit was not declared in this scope".
#include <cstdlib>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

/**
 * Creates a GameAssetManager to load the correct shaders based on the
 * ApplicationMode.
 */
GameAssetManager::GameAssetManager(ApplicationMode mode) {
  string vertex_shader("shaders/camera.vs");
  string fragment_shader_red("shaders/fragmentshader.fs");

  //Create the shader program using the vertex and fragment shaders.
  program_token = CreateGLProgram(vertex_shader, fragment_shader_red);

  //Create links to the colour uniform values stored in the fragment shader.
  shape_red_value = glGetUniformLocation(program_token, "red");
  shape_green_value = glGetUniformLocation(program_token, "green");
  shape_blue_value = glGetUniformLocation(program_token, "blue");

  camera_x_position = glGetUniformLocation(program_token, "camera_x_position");
 // camera_y_position = glGetUniformLocation(program_token_green, "camera_y_position");
 // camera_z_position = glGetUniformLocation(program_token_green, "camera_z_position");
  camera_z_position = glGetUniformLocation(program_token, "camera_z_position");

  player_x_position = 0.0f;
  player_z_position = -0.5f;

  //Set the camera starting position to the position of the player.
  glUniform1f(camera_z_position, player_z_position);

}

/**
 * Adds a GameAsset to the scene graph.
 */
void GameAssetManager::AddAsset(shared_ptr<GameAsset> the_asset) {


  draw_list.push_back(the_asset);

}

/**
 * Draws each GameAsset in the scene graph.
 */
void GameAssetManager::Draw() {


   for(auto ga: draw_list) {

     if(ga->GetAssetType() == GameAsset::CUBE){

    	 //Set the color to green before drawing the shape.
    	 glUniform1f(shape_red_value, 0.0f);
    	 glUniform1f(shape_green_value, 1.0f);
    	 glUniform1f(shape_blue_value, 0.0f);
    	 ga->Draw(program_token);

     }else if(ga->GetAssetType() == GameAsset::PYRAMID){

    	 //Set the color to red before drawing the shape.
    	 glUniform1f(shape_red_value, 1.0f);
    	 glUniform1f(shape_green_value, 0.0f);
    	 glUniform1f(shape_blue_value, 0.0f);
    	 ga->Draw(program_token);
     }
  }
}

/**
 * When given the contents of a vertex shader and fragment shader
 * GameAssetManager::CreateGLProgram will compile and link them.  This
 * implementation will exit with -1 error if an error is detected.
 *
 * @return the GL "token" referring to the gl program.
 */
GLuint GameAssetManager::CreateGLProgram(string & vertex_shader
                                         , string & fragment_shader) {
  auto v_shader_token = CreateGLESShader(GL_VERTEX_SHADER, vertex_shader);
  auto f_shader_token = CreateGLESShader(GL_FRAGMENT_SHADER, fragment_shader);

  GLint program_ok;

  GLuint program = glCreateProgram();

  glAttachShader(program, v_shader_token);
  glAttachShader(program, f_shader_token);
  glLinkProgram(program);

  glGetProgramiv(program, GL_LINK_STATUS, &program_ok);
  if (!program_ok) {
    cerr << "Failed to link shader program:" << endl;
    glDeleteProgram(program);
    exit(-1);
  }

  return program;
}

/**
 * When given a type of shader to construct and the contents of a shader,
 * GameAssetManager::CreateGLESShader will create the shader or exit with
 * error -1.
 *
 * @return the GL "token" for the requested shader.
 */
GLuint GameAssetManager::CreateGLESShader(GLenum type, string & shader) {
  GLuint shader_token;
  GLint shader_ok;
  auto source = ReadShader(shader);

  if (!source.first)
    return 0;

  shader_token = glCreateShader(type);
  glShaderSource(shader_token, 1, (const GLchar**)&source.first, &source.second);
  glCompileShader(shader_token);
  delete(source.first);

  glGetShaderiv(shader_token, GL_COMPILE_STATUS, &shader_ok);
  if (!shader_ok) {
    GLint maxLength = 0;
    glGetShaderiv(shader_token, GL_INFO_LOG_LENGTH, &maxLength);

    //The maxLength includes the NULL character
    vector<char> errorLog(maxLength);
    glGetShaderInfoLog(shader_token, maxLength, &maxLength, &errorLog[0]);

    //Provide the infolog in whatever manor you deem best.
    cerr << "Failed to compile " << shader << " with error code " << shader_ok << endl;
    for(auto c: errorLog) {
      cerr << c;
    }

    glDeleteShader(shader_token); //Don't leak the shader.
    exit(-1);
  }
  return shader_token;
}

/**
 * ReadShader reads the contents of a file and packs it into a null termintated
 * GLchar * which is suitable for sending to OpenGL.
 *
 * @return a pair consisting of the shader file contents and a holder for the
 *         OpenGL "token".
 */
pair<GLchar *, GLint> GameAssetManager::ReadShader(string & shader) {
  ifstream input_file;
  GLint length;
  input_file.open(shader, ios::in);

  input_file.seekg(0, ios::end);  // go to the end of the file
  length = input_file.tellg();    // get length of the file
  input_file.seekg(0, ios::beg);  // go to beginning of the file

  GLchar * buffer = new GLchar[length+1];
  input_file.read(buffer, length);
  buffer[length+1]='\0';  // Ensure null terminated

  input_file.close();
  return make_pair(buffer, length);
}

void GameAssetManager::UpdateCameraPosition(InputDirection inputDirection){

  //http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/

  cout << "Button press detected in asset manager";


  //Camera_z_position defined in constructor


  if(inputDirection == UP){
	  player_z_position += 0.1;
	  glUniform1f(camera_z_position, player_z_position);
  }else if(inputDirection == DOWN){
	  player_z_position -= 0.1;
	  glUniform1f(camera_z_position, player_z_position);
  }else if(inputDirection == LEFT){
	  player_x_position += 0.1;
	  glUniform1f(camera_x_position, player_x_position);
  }else if(inputDirection == RIGHT){
	  player_x_position -= 0.1;
	  glUniform1f(camera_x_position, player_x_position);
  }


  //glm::mat4 view = glm::lookAt(camera_position, camera_target, up_vector);

}

/**
 * Deletes a GameAssetManager, in particular it will clean up any modifications
 * to the OpenGL state.
 */
GameAssetManager::~GameAssetManager() {
  glDeleteProgram(program_token);
}


/**
 * Unimplemented assisgnment operator -- violates the expected semantics for
 * assignment in C++11.
 */
void GameAssetManager::operator=(GameAssetManager const& the_manager) {
  // TODO: implement this
}

/**
 * Unimplemented copy constructor -- this means that the GameAssetManager
 * may not work as you'd expect when being copied.
 */
GameAssetManager::GameAssetManager(GameAssetManager const& the_manager) {
  // TODO: implement this
}

/**
 * Unimplemented move constructor -- this unimplemented method violates the
 * C++11 move semantics for GameAssetManager.
 */
GameAssetManager::GameAssetManager(GameAssetManager const&& the_manager) {
  // TODO: implement this
}
