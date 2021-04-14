export module OpenGLDebug;

#include <iostream>
#include <string>
#include <string_view>

#include <glad/glad.h>

export namespace OpenGLDebug {
    // Print out all of the errors generated from the last OpenGL call
    void printErrors(std::string_view file, int line, std::string_view func) {
        unsigned int errorCode = 0;
        while ((errorCode = glGetError()) != GL_NO_ERROR) {
            std::string error;
            switch (errorCode) {
                case GL_INVALID_ENUM:
                    error = "GL_INVALID_ENUM";
                    break;
                case GL_INVALID_VALUE:
                    error = "GL_INVALID_VALUE";
                    break;
                case GL_INVALID_OPERATION:
                    error = "GL_INVALID_OPERATION";
                    break;
                case GL_INVALID_FRAMEBUFFER_OPERATION:
                    error = "GL_INVALID_FRAMEBUFFER_OPERATION";
                    break;
                case GL_OUT_OF_MEMORY:
                    error = "GL_OUT_OF_MEMORY";
                    break;
                case GL_STACK_UNDERFLOW:
                    error = "GL_STACK_UNDERFLOW";
                    break;
                case GL_STACK_OVERFLOW:
                    error = "GL_STACK_OVERFLOW";
                    break;
                default:
                    error = "";
                    break;
            }
            
            std::cerr << "[OPENGL ERROR]: " << errorCode << " " << error << " at " << file << "[" << line << "]:" << func << "()" << std::endl;
            ;
        }
    }
    
    // Check the OpenGL call for any errors
    template <typename...ArgsType, typename functionType>
    inline void glCall(functionType call, ArgsType...args) {
        call(args...);
        printErrors(__FILE__, __LINE__, __func__);
    }
    
    // Same as the function above, but this one returns a value
    template <typename...ArgsType, typename functionType>
    inline auto glCall(functionType call, ArgsType...args) {
        auto result = call(args...);
        printErrors(__FILE__, __LINE__, __func__);
        return result;
    }
}