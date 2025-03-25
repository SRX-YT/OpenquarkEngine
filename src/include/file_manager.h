#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

namespace FileManager {
    std::string readShaderFile(const char* filePath) {
        std::string shaderCode;
        std::ifstream shaderFile;

        shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try {
            shaderFile.open(filePath);
            std::stringstream shaderStream;

            shaderStream << shaderFile.rdbuf();

            shaderFile.close();

            shaderCode = shaderStream.str();
        }
        catch (std::ifstream::failure& e) {
            std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY READ: " << filePath << std::endl;
        }

        return shaderCode;
    }
}