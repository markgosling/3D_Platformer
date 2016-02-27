#include "GameAssetManager.h"
#include <cstdlib>// Required to fix build issue on Windows and cygwin using 'make'.
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

/**
 * @file GameAssetManager.cc
 * @version 1.0
 *
 * @section Description
 *
 * GameAssetManager is used to store and control assets for the game.
 * It contains functions to load shaders and to create a shader program.
 * It also stores a 3D array to hold the assets which make up the game
 * world, has functions allowing new objects to be added to this array
 * and to translate them into the correct position on screen before calling
 * another method to draw them. It also communicates with the camera class
 * and sends it parameters allowing the camera position to be updated.
 */

//Define the size of the game_world array (i.e. the mazimum size of the block world).
#define HEIGHT 20
#define WIDTH 20
#define DEPTH 20

/**
 * Constructor which sets the location of the shader programs and calls the
 * methods to construct them into a shader program. It also sets the uniform
 * variables needed to communicate with the shaders, sets up the projection
 * matrix and sets the size of the 3D array used to store game assets.
 */
GameAssetManager::GameAssetManager() {

	//Set the location of the vertex and fragment shader programs.
	std::string vertex_shader("shaders/camera.vs");
	std::string fragment_shader_red("shaders/fragmentshader.fs");

	//Create the shader program using the vertex and fragment shaders.
	program_token = CreateGLProgram(vertex_shader, fragment_shader_red);

	//Create links to the uniform values stored in the shaders.
	shape_red_value = glGetUniformLocation(program_token, "red");
	shape_green_value = glGetUniformLocation(program_token, "green");
	shape_blue_value = glGetUniformLocation(program_token, "blue");

	projection_matrix_link = glGetUniformLocation(program_token, "projection_matrix");
	translate_matrix_link = glGetUniformLocation(program_token, "translate_matrix");
	view_matrix_link = glGetUniformLocation(program_token, "view_matrix");

	//Create the projection matrix based on the size of the game window.
	projection_matrix = glm::perspective(glm::radians(45.0f), (float) 640 / (float) 480, 0.1f, 1000.0f);

	//Set the size of the 3D array.
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
 * AddAsset allows a GameAsset to be added to the 3D array.
 *
 * @param the_asset - shared_ptr - A pointer to the game asset to be added.
 * @param x - Integer - The X position which the asset should be placed on screen.
 * @param y - Integer - The Y position which the asset should be placed on screen.
 * @param z - Integer - The Z position which the asset should be placed on screen.
 */
void GameAssetManager::AddAsset(std::shared_ptr<GameAsset> the_asset, int x, int y, int z) {

	world_array[x][y][z] = the_asset;

}

/**
 * The 'Draw' method sets the value of the uniform variables in the shader program
 * then loops through the 3D array to find assets to draw. It then translates them
 * to the correct position on screen, then sets the draw colour based on the type
 * of asset being drawn. Finally it calls the assets 'Draw' method to draw it on screen.
 */
void GameAssetManager::Draw() {

	//Update the uniform variables inside the shader program before drawing the object.
	glUniformMatrix4fv(projection_matrix_link, 1, GL_FALSE, &projection_matrix[0][0]);
	glUniformMatrix4fv(view_matrix_link, 1, GL_FALSE, &view_matrix[0][0]);

	//Loop through the entire 3D array to find assets to draw.
	for(int x = 0; x < world_array.size(); x++){

		for(int y = 0; y < world_array[x].size(); y++){

			for(int z = 0; z < world_array[x][y].size(); z++){

				//Check that an object exists before attempting to draw it.
				if(world_array[x][y][z] != NULL){

					//Create a new variable to store the pointer of the current asset.
					auto ga = world_array[x][y][z];

					//Translate the shapes position on screen to match the position in the 3d array.
					//The x coordinate is negated so objects are translated to the right instead of left.
					//Working glm::translate function code obtained from https://www.reddit.com/r/opengl/comments/2ztqjo/problem_with_glms_translate_matrix_call.
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
 * @param vertex_shader - String - The location of the vertex shader program.
 * @param fragment_shader - String - The location of the fragment shader.
 *
 * @return the GL "token" referring to the gl program.
 */
GLuint GameAssetManager::CreateGLProgram(std::string & vertex_shader, std::string & fragment_shader) {

	//Create tokens based on each shader program location and type.
	auto v_shader_token = CreateGLESShader(GL_VERTEX_SHADER, vertex_shader);
	auto f_shader_token = CreateGLESShader(GL_FRAGMENT_SHADER, fragment_shader);

	GLint program_ok;
	GLuint program = glCreateProgram();

	//Attach the shader programs to openGL and link them together.
	glAttachShader(program, v_shader_token);
	glAttachShader(program, f_shader_token);
	glLinkProgram(program);

	//Check that the shader programs were sucessfully linked.
	glGetProgramiv(program, GL_LINK_STATUS, &program_ok);
	if (!program_ok) {
		std::cerr << "Failed to link shader program:" << std::endl;
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
 * @param type - ELenum - The type of shader token to create.
 * @param shader - String - The location of the shader program.
 *
 * @return the GL "token" for the requested shader.
 */
GLuint GameAssetManager::CreateGLESShader(GLenum type, std::string & shader) {
	GLuint shader_token;
	GLint shader_ok;
	auto source = ReadShader(shader);

	if (!source.first)
		return 0;

	//Compile the shader program.
	shader_token = glCreateShader(type);
	glShaderSource(shader_token, 1, (const GLchar**)&source.first, &source.second);
	glCompileShader(shader_token);
	delete(source.first);

	glGetShaderiv(shader_token, GL_COMPILE_STATUS, &shader_ok);
	if (!shader_ok) {
		GLint maxLength = 0;
		glGetShaderiv(shader_token, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character.
		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(shader_token, maxLength, &maxLength, &errorLog[0]);

		//Provide the infolog in whatever manor you deem best.
		std::cerr << "Failed to compile " << shader << " with error code " << shader_ok << std::endl;
		for(auto c: errorLog) {
			std::cerr << c;
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
 * @param shader - String - The location of the shader program to read.
 *
 * @return a pair consisting of the shader file contents and a holder for the OpenGL "token".
 */
std::pair<GLchar *, GLint> GameAssetManager::ReadShader(std::string & shader) {
	std::ifstream input_file;
	GLint length;
	input_file.open(shader, std::ios::in);

	input_file.seekg(0, std::ios::end);  // go to the end of the file
	length = input_file.tellg();    // get length of the file
	input_file.seekg(0, std::ios::beg);  // go to beginning of the file

	GLchar * buffer = new GLchar[length+1];
	input_file.read(buffer, length);
	buffer[length+1]='\0';  // Ensure null terminated

	input_file.close();
	return std::make_pair(buffer, length);
}

/**
 * UpdateCameraPosition acts as a pass through method allowing the camera class
 * to be called to update the camera position by returning an updated view matrix.
 *
 * @param inputDirection - InputDirection - An Enum containing the input direction being entered by the player.
 * @param mouse_x - Integer - The x coordinate of the mouse pointer.
 * @param mouse_y - Integer - The y coordinate of the mouse pointer.
 */
void GameAssetManager::UpdateCameraPosition(InputDirection input_direction, int mouse_x, int mouse_y){

	//Use the camera class to update the view matrix.
	view_matrix = camera.UpdateCameraPosition(input_direction, mouse_x, mouse_y, world_array);
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
