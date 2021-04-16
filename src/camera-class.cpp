#include <LearnOpenGL/camera-class.hpp>

Camera::Camera(glm::vec3 pPosition, glm::vec3 pWorldUp, float pYaw, float pPitch):
mPosition(pPosition), mYaw(pYaw), mPitch(pPitch), mWorldUp(pWorldUp) {
    recalculateVectors();
}

glm::mat4 Camera::lookAt() {
    return glm::lookAt(mPosition, mPosition + mDirection, mUp);
}

void Camera::translate(float pSteps, Direction pDirection) {
    switch (pDirection) {
    case Direction::Forward:
        mPosition += mDirection * pSteps;
        break;
    case Direction::Backward:
        mPosition -= mDirection * pSteps;
        break;
    case Direction::Left:
        mPosition += mRight * pSteps;
        break;
    case Direction::Right:
        mPosition -= mRight * pSteps;
        break;
    }
}

void Camera::rotate(float pX, float pY, bool pConstrainPitch) {
    mYaw += pX;
    mPitch += pY;
    
    if (pConstrainPitch) {
        if (mPitch > 89.0f) {
            mPitch = 89.0f;
        }
        if (mPitch < -89.0f) {
            mPitch = -89.0f;
        }
    }
    
    recalculateVectors();
}

void Camera::recalculateVectors() {
    glm::vec3 newDirection;
    newDirection.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
    newDirection.y = sin(glm::radians(mPitch));
    newDirection.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));
    mDirection = glm::normalize(newDirection);
    
    mRight = glm::normalize(glm::cross(mWorldUp, mDirection));
    mUp = glm::normalize(glm::cross(mDirection, mRight));
}