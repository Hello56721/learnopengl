#include <iostream>
#include <vector>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <LearnOpenGL/opengl-debug.hpp>
#include <LearnOpenGL/shader-class.hpp>

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
    
    float vertices[] {
         0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };
    unsigned int indices[] {
        0, 1, 2,
        0, 3, 2
    };
    
    Shader shader("../shaders/basic/vertex.glsl", "../shaders/basic/fragment.glsl");
    
    unsigned int vao;
    glCall(glGenVertexArrays, 1, &vao);
    glCall(glBindVertexArray, vao);
    
    unsigned int vbo;
    glCall(glGenBuffers, 1, &vbo);
    glCall(glBindBuffer, GL_ARRAY_BUFFER, vbo);
    glCall(glBufferData, GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    unsigned int ebo;
    glCall(glGenBuffers, 1, &ebo);
    glCall(glBindBuffer, GL_ELEMENT_ARRAY_BUFFER, ebo);
    glCall(glBufferData, GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glCall(glVertexAttribPointer, 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glCall(glEnableVertexAttribArray, 0);
    
    while (!glfwWindowShouldClose(window)) {
        glCall(glClear, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        shader.use();
        glCall(glBindVertexArray, vao);
        glCall(glDrawElements, GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glCall(glDeleteBuffers, 1, &vbo);
    glCall(glDeleteBuffers, 1, &ebo);
    glCall(glDeleteVertexArrays, 1, &vao);
    
    glfwTerminate();
    return 0;
}