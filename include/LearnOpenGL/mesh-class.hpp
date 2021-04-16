#ifndef C8A47903_0A8A_4722_9F81_2497F6FA87F8
#define C8A47903_0A8A_4722_9F81_2497F6FA87F8

#include <vector>
#include <LearnOpenGL/vertex-struct.hpp>
#include <LearnOpenGL/texture-struct.hpp>

class Mesh {
public:
    // Mesh Data
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    
    // Constructor
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    
};

#endif /* C8A47903_0A8A_4722_9F81_2497F6FA87F8 */
