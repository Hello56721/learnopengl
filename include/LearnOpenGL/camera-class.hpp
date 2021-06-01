#ifndef DE04A328_6CB4_4D4D_A9A4_5B3CCBFE0D75
#define DE04A328_6CB4_4D4D_A9A4_5B3CCBFE0D75

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
private:
    glm::vec3 mPosition;
    glm::vec3 mDirection;
    glm::vec3 mRight;
    glm::vec3 mUp;
    glm::vec3 mWorldUp;
    
    float mYaw;
    float mPitch;
    
public:
    // The direction
    enum class Direction {
        Forward, Backward, Left, Right
    };
    
    // Constructor
    Camera(glm::vec3 pPosition, glm::vec3 pWorldUp, float pYaw, float pPitch);
    
    // Returns the look at matrix
    glm::mat4 lookAt();
    
    // Translate the Camera
    void translate(float pSteps, Direction pDirection);
    
    // Rotate the camera
    void rotate(float pX, float pY, bool constrainPitch = false);
    
private:
    // Update the camera vectors
    void recalculateVectors();
};

#endif /* DE04A328_6CB4_4D4D_A9A4_5B3CCBFE0D75 */
