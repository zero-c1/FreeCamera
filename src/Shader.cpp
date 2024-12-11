#include <iostream>
#include <fstream>
#include "glad/glad.h"
#include "Shader.hpp"
#include "utils.hpp"

void MyApp::Shader::init(const char* vertexPath, const char* fragmentPath)
{   
    std::string vertex_str{MyApp::utils::loadTextFile(vertexPath)};
    const char* vertex_code {vertex_str.c_str()};
    std::string fragment_str{MyApp::utils::loadTextFile(fragmentPath)};
    const char* fragment_code {fragment_str.c_str()};
    mHandle = glCreateProgram();
    // CHECK_GL_ERROR;

    if (vertexPath)
    {
        GLuint vp {compileShader(vertex_code, GL_VERTEX_SHADER)};
        if (!vp)
        {
            return;
        }
        glAttachShader(mHandle, vp);
    }

    if (fragmentPath)
    {
        GLuint fp {compileShader(fragment_code, GL_FRAGMENT_SHADER)};
        if (!fp)
        {
            return;
        }
        glAttachShader(mHandle, fp);
    }

    if (linkShader())
    {
        mIsInitialized = true;
    }
}

GLuint MyApp::Shader::compileShader(const char* shader_code, GLuint type)
{
    std::string shader_type;
    switch (type)
    {
        case GL_VERTEX_SHADER:
            shader_type = "vertex";
            break;
        case GL_FRAGMENT_SHADER:
            shader_type = "fragment";
            break;
        case GL_GEOMETRY_SHADER:
            shader_type = "geometry";
            break;
        default:
            std::runtime_error("Shader types other than vertex/fragment/geometry not supported");
    }

    GLuint id = glCreateShader(type);
    glShaderSource(id, 1, &shader_code, nullptr);
    glCompileShader(id);

    GLint compiled;
    glGetShaderiv(id, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
        GLint maxLength;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);
        char* infoLog = new char[maxLength+1];
        GLint len = 0;
        glGetShaderInfoLog(id, maxLength, &len, infoLog);
        std::cerr << "GLSL " << shader_type << " shader compilation failed\n"
            << infoLog << '\n';
        delete [] infoLog;
        glDeleteShader(id);
        return 0;
    }
    return id;
}

GLint MyApp::Shader::linkShader()
{
    GLint shader_linked;
    glLinkProgram(mHandle);

    glGetProgramiv(mHandle, GL_LINK_STATUS, &shader_linked);
    if (!shader_linked)
    {
        GLint maxLength;
        glGetProgramiv(mHandle, GL_INFO_LOG_LENGTH, &maxLength);
        char* infoLog = new char[maxLength + 1];
        glGetProgramInfoLog(mHandle, maxLength, nullptr, infoLog);
        std::cerr << "GLSL program failed to link\n"
            << "Shader linking log:\n" << infoLog << '\n';
        delete[] infoLog;
        return 0;
    }
    return shader_linked;
}

void MyApp::Shader::use()
{
    if (!mIsInitialized)
    {
        std::cerr << "calling glUseProgram before compiling and linking shaders\n";
        return;
    }
    glUseProgram(mHandle);
}

void MyApp::Shader::disuse()
{
    glUseProgram(0);
}

GLuint MyApp::Shader::getHandle()
{
    return mHandle;
}