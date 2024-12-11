#pragma once
#include <string>
#include <glad/glad.h>

namespace MyApp
{

class Shader 
{
public:
    void init(const char* vertexPath, const char* fragmentPath);
    void use();
    void disuse();
    GLuint getHandle();

protected:
    GLuint compileShader(const char* shader_code, GLuint type);
    GLint linkShader();

    bool mIsInitialized {false};
    GLuint mHandle; ///< Shader program handle.
    
};

} // namespace MyApp