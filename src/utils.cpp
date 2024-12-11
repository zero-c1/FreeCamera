#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "utils.hpp"

std::string MyApp::utils::loadTextFile(const char* file_path)
{
    std::ifstream file;
    std::stringstream str_stream;
    file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        file.open(file_path, std::ifstream::in);
        // read file's buffer contents into streams
        str_stream << file.rdbuf();
        // close file handlers
        file.close();
    }
    catch(std::ifstream::failure e)
    {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    return str_stream.str(); // convert stream into string
}
