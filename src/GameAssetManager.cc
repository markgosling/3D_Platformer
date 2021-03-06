#include "GameAssetManager.h"
#include <cstdlib>// Required to fix build issue on Windows and cygwin using 'make'.
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "CubeAsset.h"
#include "PyramidAsset.h"

/**
 * @file GameAssetManager.cc
 * @version 1.1
 *
 * @section Description
 *
 * GameAssetManager is used to store and control assets for the game.
 * It contains functions to load shaders and to create a shader program.
 * It also stores an array to hold the assets which make up the game
 * world, has functions allowing new objects to be added to this array
 * and functions to animate them. It also communicates with the camera class
 * and sends it parameters allowing the camera position to be updated.
 */


/**
 * Constructor which sets the location of the shader programs and calls the
 * methods to construct them into a shader program. It also sets the uniform
 * variables needed to communicate with the shaders and sets up the projection
 * matrix.
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
	model_transformation_matrix_link = glGetUniformLocation(program_token, "model_transformation_matrix");
	view_matrix_link = glGetUniformLocation(program_token, "view_matrix");

	//Create the projection matrix based on the size of the game window.
	projection_matrix = glm::perspective(glm::radians(45.0f), (float) 640 / (float) 480, 0.1f, 1000.0f);
	
	rotation_speed = 0;
}


/**
 * Method which adds a cube asset to the game world.
 *
 * @param x_pos - float - The starting X position of the asset.
 * @param y_pos - float - The starting Y position of the asset.
 * @param z_pos - float - The starting X position of the asset.
 * @param scale - float - The amount to scale the object up by.
 * @param x_rot - float - The starting amount of rotation on the X axis.
 * @param y_rot - float - The starting amount of rotation on the Y axis.
 * @param z_rot - float - The starting amount of rotation on the Z axis.
 */
void GameAssetManager::AddCube(float x_pos, float y_pos, float z_pos, float scale, float x_rot, float y_rot, float z_rot){
	this->AddAsset(std::make_shared<CubeAsset>(x_pos, y_pos, z_pos, scale, x_rot, y_rot, z_rot));
}


/**
 * Method which adds a pyramid asset to the game world.
 *
 * @param x_pos - float - The starting X position of the asset.
 * @param y_pos - float - The starting Y position of the asset.
 * @param z_pos - float - The starting X position of the asset.
 * @param scale - float - The amount to scale the object up by.
 * @param x_rot - float - The starting amount of rotation on the X axis.
 * @param y_rot - float - The starting amount of rotation on the Y axis.
 * @param z_rot - float - The starting amount of rotation on the Z axis.
 */
void GameAssetManager::AddPyramid(float x_pos, float y_pos, float z_pos, float scale, float x_rot, float y_rot, float z_rot){
	this->AddAsset(std::make_shared<PyramidAsset>(x_pos, y_pos, z_pos, scale, x_rot, y_rot, z_rot));
}


/**
 * AddAsset adds a pointer to a GameAsset to the world_array.
 *
 * @param the_asset - shared_ptr - A pointer to a game asset.
 */
void GameAssetManager::AddAsset(std::shared_ptr<GameAsset> the_asset) {
	world_array.push_back(the_asset);
}


/**
 * Method which stores X, Y and Z coordinates in an array that is used to make a
 * game asset follow those coordinates when animating. This method should be called
 * for each set of coordinates to be added to the array.
 *
 * @param x_target - float - The target X position the asset should move towards.
 * @param y_target - float - The target Y position the asset should move towards.
 * @param z_target - float - The target Z position the asset should move towards.
 */
void GameAssetManager::AddAnimationPathCoordinates(float x_target, float y_target, float z_target){
	animation_target_coordinates.push_back(glm::vec3(x_target, y_target, z_target));
}

/**
 * Method which clears the list of animation coordinates.
 */
void GameAssetManager::ClearAnimationPathCoordinates(){
	animation_target_coordinates.clear();
}

/**
 * Method which sets the axis which a object should rotate around. A value of 1 (or higher) tells the
 * program to animate the object around that axis. The rotation speed is also set here.
 *
 * @param x_rotation - float - set to 1 or higher to animate the asset around the X axis.
 * @param y_rotation - float - set to 1 or higher to animate the asset around the Y axis.
 * @param z_rotation - float - set to 1 or higher to animate the asset around the Z axis.
 * @param rotation_speed - float - sets the rotation speed of the asset.
 */
void GameAssetManager::SetRotationParameters(float x_rotation, float y_rotation, float z_rotation, float rotation_speed){
	rotation_axis = glm::vec3(x_rotation, y_rotation, z_rotation);
	this->rotation_speed = rotation_speed;
}

/**
 * Method which clears the rotation parameters.
 */
void GameAssetManager::ClearRotationParameters(){
	rotation_axis = glm::vec3(0, 0, 0);
}

/**
 * Method which animates the asset stored in the last position of world_array according to previously specified parameters.
 * IMPORTANT - this method should be called immediately after an object has been added to the array if
 * it needs to be animated. Calling it at any other time will animate the wrong object.
 *
 * @param movement_speed - float - The speed the object should be moved at towards the array of target coordinates.
 **/
void GameAssetManager::SetAnimationParameters(float movement_speed){

	world_array.back()-> SetAnimationParameters(animation_target_coordinates, movement_speed, rotation_axis, rotation_speed);

}


/**
 * Method which returns the number of assets added to the game world.
 *
 * @return the number of assets in the 'world_array_ array.
 */
int GameAssetManager::GetNumberOfAssets(){
	return world_array.size();
}

/**
 * The 'Draw' method sets the value of the uniform variables in the shader program
 * then loops through the world_array to find assets to draw. It sends the model transformation
 * matrix to the shader program and sets the draw colour based on the type
 * of asset being drawn. Finally it calls the assets 'Draw' method to draw it on screen.
 */
void GameAssetManager::Draw() {

	//Update the uniform variables inside the shader program before drawing the object.
	glUniformMatrix4fv(projection_matrix_link, 1, GL_FALSE, &projection_matrix[0][0]);
	glUniformMatrix4fv(view_matrix_link, 1, GL_FALSE, &view_matrix[0][0]);

	//Loop through the world_array to find assets to draw.
	for(int i = 0; i < world_array.size(); i++){

		//Check that an object exists before attempting to draw it.
		if(world_array[i] != NULL){

			//Create a new variable to store the pointer of the current asset.
			auto ga = world_array.at(i);

			//Get the transform matrix (with translation, rotation and scaling already calculated) directly from the model.
			model_transformation_matrix = ga->GetCompleteModelTransformationMatrix();
			glUniformMatrix4fv(model_transformation_matrix_link, 1, GL_FALSE, &model_transformation_matrix[0][0]);

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
		//exit(-1); //Disabled on purpose to prevent python script and windows builds from exiting.
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
		//exit(-1);  //Disabled on purpose to prevent windows builds from exiting.
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
	rotation_speed = 0;
}

/**
 * Unimplemented copy constructor -- this means that the GameAssetManager
 * may not work as you'd expect when being copied.
 */
GameAssetManager::GameAssetManager(GameAssetManager const& the_manager) {
	rotation_speed = 0;
}

/**
 * Unimplemented move constructor -- this unimplemented method violates the
 * C++11 move semantics for GameAssetManager.
 */
GameAssetManager::GameAssetManager(GameAssetManager const&& the_manager) {
	// TODO: implement this
}
