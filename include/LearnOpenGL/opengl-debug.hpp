#include <iostream>
#include <string>
#include <string_view>

#include <glad/glad.h>

namespace OpenGLDebug {
    // Print out all of the errors generated from the last OpenGL call
    void printErrors(std::string_view file, int line, std::string_view func);
    
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