#include <iostream>
#include <vector>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <LearnOpenGL/opengl-debug.hpp>

// A vector of command line options
extern std::vector<std::string> commandLineArguments;
std::vector<std::string> commandLineArguments;

// A struct containing all of the executable options
struct {
    bool windowed = false;
} options;

// The window's width and height
unsigned int wWidth;
unsigned int wHeight;

int main(int argl, char** argv) {
    // Put all of the command line arguments in a vector
    for (unsigned int i = 0; i < argl; ++i) {
        commandLineArguments.push_back(argv[i]);
    }
    
    // Process all of the command line arguments
    for (std::vector<std::string>::iterator i = commandLineArguments.begin(); i != commandLineArguments.end(); i++) {
        if (*i == "--windowed") {
            options.windowed = true;
        }
    }
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWmonitor* monitor = nullptr;
    const GLFWvidmode* videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    
    if (!options.windowed) {
        monitor = glfwGetPrimaryMonitor();
        wWidth = videoMode->width;
        wHeight = videoMode->height;
    } else {
        wWidth = videoMode->width / 2;
        wHeight = videoMode->height / 2;
    }
    
    GLFWwindow* window = glfwCreateWindow(wWidth, wHeight, "LearnOpenGL", monitor, nullptr);
    if (window == nullptr) {
        std::cerr << "[FATAL ERROR]: Failed to initialize GLFW. Program will now terminate." << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "[FATAL ERROR]: Failed to initialize GLAD. Program will now terminate." << std::endl;
        glfwTerminate();
        return -1;
    }
    
    while (!glfwWindowShouldClose(window)) {
        glCall(glClear, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}