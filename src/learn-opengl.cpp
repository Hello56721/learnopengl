#include <iostream>
#include <vector>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

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
    
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    
    float positions[] {
        // positions
         0.5f,  0.5f, 0.0f, 
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
    };
    float textureCoordinates[] {
        // texture coordinates
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f
    };
    unsigned int indices[] {
        0, 1, 2,
        0, 3, 2
    };
    
    Shader shader("../shaders/basic/vertex.glsl", "../shaders/basic/fragment.glsl");
    
    unsigned int vao;
    glCall(glGenVertexArrays, 1, &vao);
    glCall(glBindVertexArray, vao);
    
    unsigned int vboPos;
    glCall(glGenBuffers, 1, &vboPos);
    glCall(glBindBuffer, GL_ARRAY_BUFFER, vboPos);
    glCall(glBufferData, GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
    
    unsigned int ebo;
    glCall(glGenBuffers, 1, &ebo);
    glCall(glBindBuffer, GL_ELEMENT_ARRAY_BUFFER, ebo);
    glCall(glBufferData, GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glCall(glVertexAttribPointer, 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glCall(glEnableVertexAttribArray, 0);
    
    unsigned int vboTexCoords;
    glCall(glGenBuffers, 1, &vboTexCoords);
    glCall(glBindBuffer, GL_ARRAY_BUFFER, vboTexCoords);
    glCall(glBufferData, GL_ARRAY_BUFFER, sizeof(textureCoordinates), textureCoordinates, GL_STATIC_DRAW);
    
    glCall(glVertexAttribPointer, 1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glCall(glEnableVertexAttribArray, 1);
    
    unsigned int texture;
    glCall(glGenTextures, 1, &texture);
    glCall(glBindTexture, GL_TEXTURE_2D, texture);
    
    glCall(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glCall(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glCall(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glCall(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    // Load the container texture
    int width, height, nrChannels;
    unsigned char* data = stbi_load("../textures/container.jpg", &width, &height, &nrChannels, 0);
    // Check if the data is valid
    if (data == nullptr) {
        std::cerr << "[ERROR]: Couldn't find or load ../textures/container.jpg" << std::endl;
    } else {
        glCall(glTexImage2D, GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glCall(glGenerateMipmap, GL_TEXTURE_2D);
    }
    
    glm::mat4 model(1.0);
    glm::mat4 view(1.0);
    glm::mat4 projection(1.0);
    
    view = glm::translate(view, glm::vec3(0.0, 0.0, -3.0));
    
    while (!glfwWindowShouldClose(window)) {
        glCall(glClear, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        projection = glm::perspective(glm::radians(45.0), static_cast<double>(wWidth) / static_cast<double>(wHeight), 0.1, 100.0);
        
        shader.use();
        
        shader.setUniform("model", model);
        shader.setUniform("view", view);
        shader.setUniform("projection", projection);
        
        glCall(glBindTexture, GL_TEXTURE_2D, texture);
        
        glCall(glBindVertexArray, vao);
        glCall(glDrawElements, GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glCall(glDeleteBuffers, 1, &vboPos);
    glCall(glDeleteBuffers, 1, &vboTexCoords);
    glCall(glDeleteBuffers, 1, &ebo);
    glCall(glDeleteVertexArrays, 1, &vao);
    
    glfwTerminate();
    return 0;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    wWidth = width;
    wHeight = height;
    glCall(glViewport, 0, 0, wWidth, wHeight);
}