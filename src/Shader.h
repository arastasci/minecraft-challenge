#include <glad/glad.h>
#include <string>
class Shader
{
public:
    Shader(const char *vertexPath, const char *fragmentPath);
    void use();
    void setBool(const std::string &name, bool value) const;
    void setFloat(const std::string &name, float value) const;
    void setInt(const std::string &name, int value) const;
    void setVec3(const std::string &name, float x, float y, float z) const;

private:
    GLuint id;
    void checkCompileErrors(unsigned int shader, std::string type);
};