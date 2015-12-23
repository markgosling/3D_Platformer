#include "GameAssetManager.h"

// Required to fix build issue on Windows and cygwin using 'make'
//which was returning "error: exit was not declared in this scope".
#include <cstdlib>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>


using namespace std;

//Define the size of the game_world array (i.e. the mazimum size of the block world).
#define HEIGHT 20
#define WIDTH 20
#define DEPTH 20

/**
 * Creates a GameAssetManager to load the correct shaders based on the
 * ApplicationMode.
 */
GameAssetManager::GameAssetManager() {
  string vertex_shader("shaders/camera.vs");
  string fragment_shader_red("shaders/fragmentshader.fs");

  //Create the shader program using the vertex and fragment shaders.
  program_token = CreateGLProgram(vertex_shader, fragment_shader_red);

  //Create links to the colour uniform values stored in the shaders.
  shape_red_value = glGetUniformLocation(program_token, "red");
  shape_green_value = glGetUniformLocation(program_token, "green");
  shape_blue_value = glGetUniformLocation(program_token, "blue");

  translate_matrix_link = glGetUniformLocation(program_token, "translate_matrix");
  view_matrix_link = glGetUniformLocation(program_token, "view_matrix");



  //Code to set up the 3d world array adapted from an example at
  //http://www.cplusplus.com/forum/articles/7459/
  world_array.resize(HEIGHT);
  for(int i = 0; i < HEIGHT; ++i){
	  world_array[i].resize(WIDTH);

	  for(int j = 0; j < WIDTH; ++j){
		  world_array[i][j].resize(DEPTH);
	  }
  }
}

/**
 * Adds a GameAsset to the scene graph.
 */
void GameAssetManager::AddAsset(shared_ptr<GameAsset> the_asset, int x, int y, int z) {

  world_array[x][y][z] = the_asset;

}

/**
 * Draws each GameAsset in the scene graph.
 */
void GameAssetManager::Draw() {

	//Update the uniform variables inside the shader program before
	//drawing the object.
	//view_matrix = glm::lookAt(glm::vec3(player_x_position, 0.0f, player_z_position),
	 //		                 glm::vec3(player_x_position, 0.0f, player_z_position + 2),
	 //					     glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(view_matrix_link, 1, GL_FALSE, &view_matrix[0][0]);

    for(int x = 0; x < world_array.size(); x++){

    	for(int y = 0; y < world_array[x].size(); y++){

    		for(int z = 0; z < world_array[x][y].size(); z++){

    			//Check that an object exists before attempting to draw it.
    			if(world_array[x][y][z] != NULL){

        			auto ga = world_array[x][y][z];

        			//Working glm::translate function code obtained from
        			//https://www.reddit.com/r/opengl/comments/2ztqjo/problem_with_glms_translate_matrix_call.
        			//Translate the shapes position on screen to match the position in the 3d array.
        			//The x coordinate is negated so objects are seen to be translated right instead of left.
        			translate_matrix = glm::translate(glm::mat4(), glm::vec3(-x, y, z));
        			glUniformMatrix4fv(translate_matrix_link, 1, GL_FALSE, &translate_matrix[0][0]);

        			//Check the asset type and draw it using the correct colour.
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

void GameAssetManager::UpdateCameraPosition(InputDirection inputDirection, int mouse_x, int mouse_y){

	//collision_type_detected = DetectCollisionWithAsset();

	//std::cout << " Collision type: " << collision_type_detected << endl;

   // cout << "X " << x_collision << endl;
   // cout << "Y " << y_collision << endl;
   // cout << "Z " << z_collision << endl;
    view_matrix = camera.UpdateCameraPosition(inputDirection, mouse_x, mouse_y, world_array);

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
