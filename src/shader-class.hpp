#ifndef F07C3395_BD14_4EBF_B170_A37E6AEB5E53
#define F07C3395_BD14_4EBF_B170_A37E6AEB5E53

#include <glad/glad.h>

#include "opengl-debug.hpp"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <string_view>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

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
    void setUniform(std::string_view name, glm::mat4 value) const;
    void setUniform(std::string_view name, glm::vec3 value) const;
    void setUniform(std::string_view name, float x, float y, float z) const;
    // Getter for the id
    unsigned int getID() const;
    // Destructor
    ~Shader();
};

#endif /* F07C3395_BD14_4EBF_B170_A37E6AEB5E53 */
