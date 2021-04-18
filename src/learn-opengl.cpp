#include <iostream>
#include <vector>
#include <string>
#include <random>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <LearnOpenGL/opengl-debug.hpp>
#include <LearnOpenGL/shader-class.hpp>
#include <LearnOpenGL/camera-class.hpp>

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

float movementSpeed = 2.5f;

static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

static void mouseCallback(GLFWwindow* window, double xoffset, double yoffset);

// Respond to all of the inputs generated by the specified window
static void handleInput(GLFWwindow* window);

// The camera
Camera camera(glm::vec3(0.0, 0.0, 2.0), glm::vec3(0.0, 1.0, 0.0), -90.0f, 0.0f);

// Time keeping variables
double startTime, endTime, deltaTime;

float lastX;
float lastY;

bool firstMouse = true;

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
    
    std::cout << "[INFO]: Creating Window..." << std::endl;
    
    // Window
    // ###################################################################################################
    // ###################################################################################################
    // ###################################################################################################
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    
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
    
    glCall(glEnable, GL_DEPTH_TEST);
    
    std::cout << "[INFO]: Window has been created. Using OpenGL " << glCallR(glGetString, GL_VERSION) << std::endl;
    
    // Capture the mouse pointer
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetCursorPosCallback(window, mouseCallback);
    
    std::cout << "[INFO]: Initializing the program. Please wait." << std::endl;
    
    float positions[] {
        // front
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,
        
        // left
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        
        // back
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        
        // right
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,
        
        // top
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        
        // bottom
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
    };
    float textureCoordinates[] {
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
    };
    unsigned int indices[] {
        0, 1, 2,
        0, 3, 2
    };
    
    Shader shader("../shaders/basic/vertex.glsl", "../shaders/basic/fragment.glsl");
    
    // Data
    // ###################################################################################################
    // ###################################################################################################
    // ###################################################################################################
    
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
    
    // Textures
    // ###################################################################################################
    // ###################################################################################################
    // ###################################################################################################
    
    // Flip it so that the textures aren't upside down
    stbi_set_flip_vertically_on_load(true);
    
    unsigned int texture;
    glCall(glGenTextures, 1, &texture);
    glCall(glBindTexture, GL_TEXTURE_2D, texture);
    
    glCall(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glCall(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
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
    
    stbi_image_free(data);
    
    // ##################################################################################################
    
    unsigned int texture2;
    glCall(glGenTextures, 1, &texture2);
    glCall(glBindTexture, GL_TEXTURE_2D, texture2);
    
    glCall(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glCall(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glCall(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glCall(glTexParameteri, GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    // Load the face texture
    int width2, height2, nrChannels2;
    unsigned char* data2 = stbi_load("../textures/awesomeface.png", &width2, &height2, &nrChannels2, 0);
    // Check if the data is valid
    if (data == nullptr) {
        std::cerr << "[ERROR]: Couldn't find or load ../textures/awesomeface.png" << std::endl;
    } else {
        glCall(glTexImage2D, GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
        glCall(glGenerateMipmap, GL_TEXTURE_2D);
    }
    
    stbi_image_free(data2);
    
    // Set up the random engine stuff
    long seed;
    std::random_device device;
    if (device.entropy() == 0) {
        seed = time(0);
    } else {
        seed = device();
    }
    std::mt19937 randomEngine(seed);
    
    // Generate a random vector of 1000 random cube positions and rotations
    std::vector<glm::vec3> cubePositions;
    std::vector<float> cubeRotations;
    std::uniform_int_distribution<long> positionsRandomDistribution(-100, 100);
    std::uniform_real_distribution<float> rotationsRandomDistribution(-180, 180);
    for (unsigned int i = 0; i < 3000; i++) {
        glm::vec3 position;
        position.x = positionsRandomDistribution(randomEngine);
        position.y = positionsRandomDistribution(randomEngine);
        position.z = positionsRandomDistribution(randomEngine);
        cubePositions.push_back(position);
        
        cubeRotations.push_back(rotationsRandomDistribution(randomEngine));
    }
    
    shader.use();
    shader.setUniform("texture1", 0);
    shader.setUniform("texture2", 1);
    
    glm::mat4 model(1.0);
    glm::mat4 view(1.0);
    glm::mat4 projection(1.0);
    
    std::cout << "[INFO]: Initialization Complete. Entering main loop." << std::endl;
    
    // Main Loop
    // ###################################################################################################
    // ###################################################################################################
    // ###################################################################################################
    
    glfwShowWindow(window);
    while (!glfwWindowShouldClose(window)) {
        startTime = glfwGetTime();
        
        handleInput(window);
        
        glCall(glClear, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        projection = glm::perspective(glm::radians(45.0), static_cast<double>(wWidth) / static_cast<double>(wHeight), 0.1, 1000000.0);
        
        view = camera.lookAt();
        
        glCall(glActiveTexture, GL_TEXTURE0);
        glCall(glBindTexture, GL_TEXTURE_2D, texture);
        glCall(glActiveTexture, GL_TEXTURE1);
        glCall(glBindTexture, GL_TEXTURE_2D, texture2);
        
        shader.use();
        
        shader.setUniform("model", model);
        shader.setUniform("view", view);
        shader.setUniform("projection", projection);
        
        glCall(glBindVertexArray, vao);
        //glCall(glDrawElements, GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        for (unsigned int i = 0; i < 3000; i++) {
            model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            model = glm::rotate(model, glm::radians(cubeRotations[i]), glm::vec3(0.5f, 1.0f, 0.3f));
            
            shader.setUniform("model", model);
            
            glCall(glDrawArrays, GL_TRIANGLES, 0, (sizeof(positions) / sizeof(float)) / 3);
        }
        
        glfwSwapBuffers(window);
        glfwPollEvents();
        
        endTime = glfwGetTime();
        deltaTime = endTime - startTime;
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

void handleInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window, true);
    }
    
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) {
        movementSpeed = 15.0f;
    }
    if (!glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) {
        movementSpeed = 2.5f;
    }
    
    if (glfwGetKey(window, GLFW_KEY_W)) {
        camera.translate(movementSpeed * deltaTime, Camera::Direction::Forward);
    }
    if (glfwGetKey(window, GLFW_KEY_S)) {
        camera.translate(movementSpeed * deltaTime, Camera::Direction::Backward);
    }
    if (glfwGetKey(window, GLFW_KEY_A)) {
        camera.translate(movementSpeed * deltaTime, Camera::Direction::Left);
    }
    if (glfwGetKey(window, GLFW_KEY_D)) {
        camera.translate(movementSpeed * deltaTime, Camera::Direction::Right);
    }
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = wWidth / 2;
        lastY = wHeight / 2;
        firstMouse = false;
    }
    
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    
    lastX = xpos;
    lastY = ypos;
    
    xoffset = xoffset * 2.5f * deltaTime;
    yoffset = yoffset * 2.5f * deltaTime;
    
    camera.rotate(xoffset, yoffset, true);
}