#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "world/Voxel.h"
#include "Shader.h"
#include "Camera.h"
#include <stb_image.h>
#include <filesystem>

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

void mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    static float pitch = 0.0f;
    static float yaw = -90.0f;

    static float lastX = SCREEN_WIDTH / 2;
    static float lastY = SCREEN_HEIGHT / 2;

    static bool firstMouse = true;
    
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
  
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.9f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    glm::vec3 cameraFront = glm::normalize(direction);

    Camera *camera = Camera::getInstance();
    camera->direction = cameraFront;
}  

void processInput(GLFWwindow *window)
{
    Camera *camera = Camera::getInstance();

    static double lastFrame = 0.0f;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
    
    double speed = 1.0f;
    float delta = speed * (glfwGetTime() - lastFrame);
    lastFrame = glfwGetTime();
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->translate(camera->direction * delta);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->translate(camera->direction * -delta);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->translate(glm::normalize(glm::cross(camera->direction, camera->up))  * -delta);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->translate(glm::normalize(glm::cross(camera->direction, camera->up))  * delta);
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
    glfwSetCursorPosCallback(window, mouseCallback);  

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
    Voxel voxel4(glm::vec3(0.0f, 1.0f, 0.0f));

    Camera *camera = Camera::getInstance();
    
    GLuint texture0;
    /*
    glGenTextures(1, &texture0);
    glBindTexture(GL_TEXTURE_2D, texture0);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    
    unsigned char *data = stbi_load("res/textures/grass.jpg", &width, &height, &nrChannels, 0); 
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    */
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.1f, 0.1f, 0.7f, 1.0f);

        voxel1.draw(shader);
        voxel2.draw(shader);
        voxel3.draw(shader);
        voxel4.draw(shader);

        camera->draw(shader);

        glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
    
	glfwTerminate();
	return 0;
}