#include "Controller.h"

Controller* Controller::instance = nullptr;

Controller::Controller()
{
}

Controller::~Controller()
{
}

Controller* Controller::getInstance()
{
    if (instance == nullptr)
    {
        instance = new Controller();
    }
    return instance;
}

void Controller::setWindow(GLFWwindow *window)
{
    this->window = window;
    glfwSetCursorPosCallback(window, mouse);

}

void Controller::mouse(GLFWwindow* window, double xpos, double ypos)
{
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
    
    Player* player = Player::getInstance();
    player->rotate(xoffset, yoffset);
    
    lastX = xpos;
    lastY = ypos;
}

void Controller::keyboard()
{
    Player* player = Player::getInstance();

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
    
    float delta = (glfwGetTime() - time);
    time = glfwGetTime();
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        player->moveForward(delta);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        player->moveBackward(delta);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        player->moveLeft(delta);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        player->moveRight(delta);
}

void Controller::tick()
{
    keyboard();
}