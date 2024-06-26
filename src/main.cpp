#include <glad/glad.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>
#include <filesystem>
#include "world/Block.h"
#include "world/BlockDatabase.h"
#include "Shader.h"
#include "Camera.h"
#include "Player.h"
#include "world/Chunk.h"
#include "Constants.h"
#include "Controller.h"
#include <GLFW/glfw3.h>
#include "world/World.h"


int main(int argc, char **argv)
{
    glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
	    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //uncomment this statement to fix compilation on OS X
    #endif
	
	GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Minecraft alpha 1.0", NULL, NULL);
	

    if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwMakeContextCurrent(window);
glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); });

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

    glEnable(GL_DEPTH_TEST);

    Shader shader("src/shader/vshader.glsl", "src/shader/fshader.glsl");
    shader.use();
    
    BlockDatabase db;
    TextureAtlas::getInstance()->generateTexture("res/textures/terrain.png");

    //Block voxel1(db.blockDatabase[(int)BlockId::Grass], glm::vec3(0.0f, 0.0f, 0.0f));

    Player *player = Player::getInstance();
    Controller* controller = Controller::getInstance();
    Camera* camera = Camera::getInstance();
    controller->setWindow(window);

	World world;
	world.init();

	float time = glfwGetTime();
	
  while (!glfwWindowShouldClose(window))
	{
        float newTime = glfwGetTime();
        float deltaTime = newTime - time;
        time = newTime;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.69f, 0.92f, 0.92f, 1.0f);

        player->tick(deltaTime);       
		world.tick(deltaTime);
        controller->tick();

		world.render(shader);
        camera->draw(shader);
		
		player->position += player->speed * deltaTime;
		
		player->boundingBox.x = player->position.x + PLAYER_SIZE.x / 2.0f;
		player->boundingBox.y = player->position.y - (PLAYER_SIZE).y / 2.0f ;
		player->boundingBox.z = player->position.z + PLAYER_SIZE.z / 2.0f;
		
		camera->position = player->position;
		camera->direction = player->direction;
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
    
	glfwTerminate();
	return 0;
}