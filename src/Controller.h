#pragma once
#include "Camera.h"
#include "Constants.h"
#include "Player.h"
#include <GLFW/glfw3.h>

class Controller {
public:
    ~Controller();
    static Controller* getInstance();
    void operator=(const Controller &) = delete;

    void setWindow(GLFWwindow* window);

    void tick();
private:
    Controller();
    static Controller* instance;

    GLFWwindow* window;
    Player* player;

    double time = 0.0f;

    static void mouse(GLFWwindow* window, double xpos, double ypos);
    void keyboard();
};