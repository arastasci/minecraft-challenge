#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>

#include "world/Voxel.h"
#include "Shader.h"

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

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
    
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

    Shader shader("src/shader/vshader.glsl", "src/shader/fshader.glsl");
    shader.use();
    
    Voxel voxel1(glm::vec3(0.0f, 0.0f, 0.0f));
    Voxel voxel2(glm::vec3(1.0f, 0.0f, 0.0f));
    Voxel voxel3(glm::vec3(-1.0f, 0.0f, 0.0f));


    glm::mat4 projection = glm::perspective()

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		
        glClear(GL_COLOR_BUFFER_BIT);

        voxel1.draw(shader);
        voxel2.draw(shader);
        voxel3.draw(shader);

        glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
    
	glfwTerminate();
	return 0;
}