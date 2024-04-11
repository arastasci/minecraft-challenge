#include <GLFW/glfw3.h>
class Application
{
public:
    Application() = default;
    ~Application() = default;
    void Init();
    void Run();

private:
    GLFWwindow* window;
}