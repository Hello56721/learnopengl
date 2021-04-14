#ifndef CD08BFE2_4D4E_4341_8155_E5289DFACC9A
#define CD08BFE2_4D4E_4341_8155_E5289DFACC9A

#include <iostream>
#include <string>
#include <string_view>

#include <glad/glad.h>

#define glCall(x, ...) OpenGLDebug::glCallImpl(__FILE__, __LINE__, __func__, x, __VA_ARGS__)
#define glCallR(x, ...) OpenGLDebug::glCallRImpl(__FILE__, __LINE__, __func__, x, __VA_ARGS__)
#define glCallN(x) OpenGLDebug::glCallImpl(__FILE__, __LINE__, __func__, x)
#define glCallRN(x) OpenGLDebug::glCallRImpl(__FILE__, __LINE__, __func__, x)

namespace OpenGLDebug {
    // Print out all of the errors generated from the last OpenGL call
    void printErrors(std::string_view file, int line, std::string_view func);
    
    // Check the OpenGL call for any errors
    template <typename...ArgsType, typename functionType>
    void glCallImpl(std::string_view file, int line, std::string_view func, functionType call, ArgsType...args) {
        call(args...);
        printErrors(__FILE__, __LINE__, __func__);
    }
    
    // Same as the function above, but this one returns a value
    template <typename...ArgsType, typename functionType>
    auto glCallRImpl(std::string_view file, int line, std::string_view func, functionType call, ArgsType...args) {
        auto result = call(args...);
        printErrors(__FILE__, __LINE__, __func__);
        return result;
    }
}


#endif /* CD08BFE2_4D4E_4341_8155_E5289DFACC9A */
