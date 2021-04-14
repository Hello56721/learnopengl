#ifndef F07C3395_BD14_4EBF_B170_A37E6AEB5E53
#define F07C3395_BD14_4EBF_B170_A37E6AEB5E53

#include <glad/glad.h>

#include <LearnOpenGL/opengl-debug.hpp>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <string_view>

class Shader {
private:
    // The ID of the shader object
    unsigned int mID;
    
public:
    // Constructor
    Shader(std::string_view vertexPath, std::string_view fragmentPath);
    // Use the shader program
    void use() const;
    // Utility functions for setting uniforms
    void setUniform(std::string_view name, bool value) const;
    void setUniform(std::string_view name, int value) const ;
    void setUniform(std::string_view name, float value) const;
    // Getter for the id
    unsigned int getID() const;
    // Destructor
    ~Shader();
};

#endif /* F07C3395_BD14_4EBF_B170_A37E6AEB5E53 */
