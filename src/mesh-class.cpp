#include <LearnOpenGL/mesh-class.hpp>

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture>& textures) {
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
    
    setupMesh();
}

void Mesh::draw(Shader& shader) {
    // Bind the neccessary textures
    unsigned int specular_num = 1;
    unsigned int diffuse_num = 1;
    for (unsigned int i = 0; i < textures.size(); i++) {
        glCall(glActiveTexture, GL_TEXTURE0 + i);
        
        std::string number;
        std::string name = textures[i].type;
        
        if (name == "texture_diffuse") {
            number = std::to_string(diffuse_num++);
        }
        if (name == "texture_specular") {
            number = std::to_string(specular_num++);
        }
        
        shader.setUniform(name + "_" + number, static_cast<int>(i));
        glCall(glBindTexture, GL_TEXTURE_2D, textures[i].texture);
    }
    glCall(glActiveTexture, GL_TEXTURE0);
    
    // Draw Mesh
    glCall(glBindVertexArray, vao);
    glCall(glDrawElements, GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
    glCall(glBindVertexArray, 0);
}

void Mesh::setupMesh() {
    // Create the vertex array
    glCall(glGenVertexArrays, 1, &vao);
    glCall(glBindVertexArray, vao);
    
    // Create the vertex buffer
    glCall(glGenBuffers, 1, &vbo);
    glCall(glBindBuffer, GL_ARRAY_BUFFER, vbo);
    glCall(glBufferData, GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
    
    // Create the element buffer
    glCall(glGenBuffers, 1, &ebo);
    glCall(glBindBuffer, GL_ELEMENT_ARRAY_BUFFER, ebo);
    glCall(glBufferData, GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    
    // Specify vertex layout of position
    glCall(glVertexAttribPointer, 0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), offsetof(Vertex, position));
    glCall(glEnableVertexAttribArray, 0);
    
    // Normal
    glCall(glVertexAttribPointer, 1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), offsetof(Vertex, normal));
    glCall(glEnableVertexAttribArray, 1);
    
    // Texture Coordinates
    glCall(glVertexAttribPointer, 2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), offsetof(Vertex, texture_coordinate));
    glCall(glEnableVertexAttribArray, 2);
    
    // Unbind the vertex array afterwards
    glCall(glBindVertexArray, 0);
}