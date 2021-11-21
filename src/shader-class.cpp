
#include "shader-class.hpp"

Shader::Shader(std::string_view vertexPath, std::string_view fragmentPath) {
    // Load the vertex shader
    std::ifstream vertexFile(vertexPath.data());
    std::stringstream vertexStream;
    if (vertexFile) {
        vertexStream << vertexFile.rdbuf();
    } else {
        std::cerr << "[ERROR]: Failed to load shader " << vertexPath << std::endl;
        vertexStream.str("");
    }
    
    // Put the source code into a c string
    std::string vertexString = vertexStream.str();
    const char* vertexSource = vertexString.c_str();
    
    // Compile the vertex shader
    unsigned int vertex = glCallR(glCreateShader, GL_VERTEX_SHADER);
    glCall(glShaderSource, vertex, 1, &vertexSource, nullptr);
    glCall(glCompileShader, vertex);
    
    // Check for compiliation errors
    int success;
    glCall(glGetShaderiv, vertex, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        // Obtain the error log
        int errorLogLength;
        glCall(glGetShaderiv, vertex, GL_INFO_LOG_LENGTH, &errorLogLength);
        char* errorLog = new char[errorLogLength];
        glCall(glGetShaderInfoLog, vertex, errorLogLength, &errorLogLength, errorLog);
        
        std::cerr << "[SHADER ERROR]: Failed to compile " << vertexPath << ":\n";
        std::cerr << errorLog << std::endl;
        std::cerr << std::endl;
        
        delete[] errorLog;
    }
    
    // Load the fragment shader
    std::ifstream fragmentFile(fragmentPath.data());
    std::stringstream fragmentStream;
    if (fragmentFile) {
        fragmentStream << fragmentFile.rdbuf();
    } else {
        std::cerr << "[ERROR]: Failed to load shader " << fragmentPath << std::endl;
        fragmentStream.str("");
    }
    
    // Put the source code into a c string
    std::string fragmentString = fragmentStream.str();
    const char* fragmentSource = fragmentString.c_str();
    
    // Compile the fragment shader
    unsigned int fragment = glCallR(glCreateShader, GL_FRAGMENT_SHADER);
    glCall(glShaderSource, fragment, 1, &fragmentSource, nullptr);
    glCall(glCompileShader, fragment);
    
    // Check for compiliation errors
    success = 1;
    glCall(glGetShaderiv, fragment, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        // Obtain the error log
        int errorLogLength;
        glCall(glGetShaderiv, fragment, GL_INFO_LOG_LENGTH, &errorLogLength);
        char* errorLog = new char[errorLogLength];
        glCall(glGetShaderInfoLog, fragment, errorLogLength, &errorLogLength, errorLog);
        
        std::cerr << "[SHADER ERROR]: Failed to compile " << fragmentPath << ":\n";
        std::cerr << errorLog << std::endl;
        std::cerr << std::endl;
        
        delete[] errorLog;
    }
    
    // Link the shaders together into one shader program
    mID = glCallRN(glCreateProgram);
    glCall(glAttachShader, mID, vertex);
    glCall(glAttachShader, mID, fragment);
    glCall(glLinkProgram, mID);
    
    // Check for compiliation errors
    success = 1;
    glCall(glGetProgramiv, mID, GL_LINK_STATUS, &success);
    if (success == GL_FALSE) {
        // Obtain the error log
        int errorLogLength;
        glCall(glGetProgramiv, mID, GL_INFO_LOG_LENGTH, &errorLogLength);
        char* errorLog = new char[errorLogLength];
        glCall(glGetProgramInfoLog, mID, errorLogLength, &errorLogLength, errorLog);
        
        std::cerr << "[SHADER ERROR]: Failed to link " << fragmentPath << " and " << vertexPath << ":\n";
        std::cerr << errorLog << std::endl;
        std::cerr << std::endl;
        
        delete[] errorLog;
    }
    
    // Delete the object files
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use() const {
    glCall(glUseProgram, mID);
}

void Shader::setUniform(std::string_view name, bool value) const {
    glCall(glUniform1i, glCallR(glGetUniformLocation, mID, name.data()), static_cast<int>(value));
}

void Shader::setUniform(std::string_view name, int value) const {
    glCall(glUniform1i, glCallR(glGetUniformLocation, mID, name.data()), value);
}

void Shader::setUniform(std::string_view name, float value) const {
    glCall(glUniform1f, glCallR(glGetUniformLocation, mID, name.data()), value);
}

void Shader::setUniform(std::string_view name, glm::mat4 value) const {
    glCall(glUniformMatrix4fv, glCallR(glGetUniformLocation, mID, name.data()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setUniform(std::string_view name, glm::vec3 value) const {
    glCall(glUniform3fv, glCallR(glGetUniformLocation, mID, name.data()), 1, glm::value_ptr(value));
}

void Shader::setUniform(std::string_view name, float x, float y, float z) const
{
    glCall(glUniform3f, glCallR(glGetUniformLocation, mID, name.data()), x, y, z);
}

Shader::~Shader() {
    glCall(glDeleteProgram, mID);
}