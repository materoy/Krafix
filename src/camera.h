//
//  camera.h
//  Grafiq
//
//  Created by gZ on 09/07/2021.
//

#ifndef camera_h
#define camera_h

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

enum Camera_Movement{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

// An abstract camera  class that processes input and calculates the corresponding Euler angles
class Camera
{
public:
    // Camera attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    
    // euler angles
    float Yaw;
    float Pitch;
    // camera opotions
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
    
    // Constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
           float yaw = YAW, float pitch = PITCH) :
                            Front(glm::vec3(0.0f, 0.0f, -1.0f)),
                            MovementSpeed(SPEED),
                            MouseSensitivity(SENSITIVITY),
                            Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Pitch = pitch;
        Yaw = yaw;
        updateCameraVectors();
    }
    
    // Constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
            : Front(glm::vec3(0.0f, 0.0f, -1.0f)),
                MovementSpeed(SPEED),
                MouseSensitivity(SENSITIVITY),
                Zoom(ZOOM)
    {
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }
    
    // Returns the view matrix calculated using euler angles and the lookAt Matrix
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(Position, Position + Front, Up);
    }
    
    // Processes input  received from any keyboard-like input system
    // Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems
    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity = MovementSpeed * deltaTime;
        if (direction == FORWARD)
        {
            Position += Front * velocity;
        }
        if (direction == BACKWARD)
        {
            Position -= Front * velocity;
        }
        if (direction == LEFT)
        {
            Position -= Right * velocity;
        }
        if (direction == RIGHT)
        {
            Position += Right * velocity;
        }
    }
    
    // Processes input received from a mouse input system
    // Expects the offset value in both X and Y direction
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;
        
        Yaw += xoffset;
        Pitch += yoffset;
        
        // Prevent flipping when pitch is out of bounds
        if(constrainPitch)
        {
            if(Pitch > 89.0f)
                Pitch = 89.0f;
            if(Pitch < -89.0f)
                Pitch = -89.0f;
        }
        
        // Update Front, Right and Up vectors using the updated Euler angles
        updateCameraVectors();
    }
    
    void ProcessMouseScroll(float yoffset)
    {
        Zoom -= (float) yoffset;
        if(Zoom < 1.0f)
            Zoom = 1.0f;
        if(Zoom > 45.0f)
            Zoom = 45.0f;
    }
    
private:
    // Calculates the front vector from the Cameras (updated) Euler Angles
    void updateCameraVectors()
    {
        // calculate the new front vector
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        
        // also recalculate Right and up vector
        Right = glm::normalize(glm::cross(Front, WorldUp));
        Up = glm::normalize(glm::cross(Right, Front));
    }
};

#endif /* camera_h */
