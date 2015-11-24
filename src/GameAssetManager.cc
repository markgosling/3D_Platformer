#include "GameAssetManager.h"

// Required to fix build issue on Windows and cygwin using 'make'
//which was returning "error: exit was not declared in this scope".
#include <cstdlib>

using namespace std;

/**
 * Creates a GameAssetManager to load the correct shaders based on the
 * ApplicationMode.
 */
GameAssetManager::GameAssetManager(ApplicationMode mode) {
  string vertex_shader("shaders/camera.vs");
  string fragment_shader_red("shaders/fragmentred.fs");
  string fragment_shader_green("shaders/fragmentgreen.fs");

  switch(mode) {
  case ROTATE:
    //vertex_shader = "shaders/rotate.vs";
    break;
  case SCALE:
  //  vertex_shader = "shaders/scale.vs";
    break;
  case TRANSFORM:
  default:
    break;
  };

  //The idea for using fragment shader programs for different colours came from
  //http://learnopengl.com/#!Getting-started/Hello-Triangle.
  program_token_red = CreateGLProgram(vertex_shader, fragment_shader_red);
  program_token_green = CreateGLProgram(vertex_shader, fragment_shader_green);

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

    ga->Draw(program_token_green);
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

/**
 * Deletes a GameAssetManager, in particular it will clean up any modifications
 * to the OpenGL state.
 */
GameAssetManager::~GameAssetManager() {
  glDeleteProgram(program_token_green);
  glDeleteProgram(program_token_red);
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
