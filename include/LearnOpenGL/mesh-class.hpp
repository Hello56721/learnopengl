#ifndef C2EA2E66_3757_413E_8C0A_7E365FE0B69E
#define C2EA2E66_3757_413E_8C0A_7E365FE0B69E

#include <LearnOpenGL/vertex-struct.hpp>
#include <LearnOpenGL/texture-struct.hpp>
#include <LearnOpenGL/shader-class.hpp>

#include <vector>

class Mesh {
public:
    // The Mesh Data
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    
    // Constructor
    Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture>& textures);
    
    // Render the mesh on screen
    void draw(Shader& shader);
    
private:
    // Rendering Data
    unsigned int vao, vbo, ebo;
    
    // Create the Mesh
    void setupMesh();
};

#endif /* C2EA2E66_3757_413E_8C0A_7E365FE0B69E */
