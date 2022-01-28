//
//  Camera.h
//  LearnOpenGL
//
//  Created by Kishan on 28/01/22.
//

#ifndef Camera_h
#define Camera_h

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>


enum CameraMovement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// default camera props
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f; // zoom is fov


// abstract Camera class.
class Camera {
public:
	// cam attributes
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	// euler angles
	float Yaw;
	float Pitch;
	// camera Positions
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;
	
	//------------ Constructors -----------
	// constructor with vectors
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		Position = position;
		WorldUp = up;
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}
	
	// constructor with scalar values
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(Zoom)
	{
		Position = glm::vec3(posX, posY, posZ);
		WorldUp = glm::vec3(upX, upY, upZ);
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}
	
	// return view matrix calculated using the pos, front and up vectors
	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(Position, Position + Front, Up);
	}
	
	// process input from kbd
	void ProcessKeyboard(CameraMovement direction, float deltaTime)
	{
		float velocity = MovementSpeed * deltaTime;
		if(direction == FORWARD)
			Position += Front * velocity;
		if(direction == BACKWARD)
			Position -= Front * velocity;
		if(direction == LEFT)
			Position -= Right * velocity;
		if(direction == RIGHT)
			Position += Right * velocity;
	}
	
	// process input from mouse
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
	{
		xoffset *= MouseSensitivity;
		yoffset *= MouseSensitivity;
		
		Yaw += xoffset;
		Pitch += yoffset;
		
		// avoid screen flipping
		if(constrainPitch)
		{
			if(Pitch > 89.0f)
				Pitch = 89.0f;
			if(Pitch < -89.0f)
				Pitch = -89.0f;
		}
		
		updateCameraVectors();
	}
	
	// process scroll input
	void ProcessMouseScroll(float yoffset)
	{
		Zoom -= (float)yoffset;
		if(Zoom < 1.0f)
			Zoom = 1.0f;
		if(Zoom > 45.0f)
			Zoom = 45.0f;
	}
	
private:
	// calculate front, up and right vectors from upated euler angles
	void updateCameraVectors()
	{
		// calculate new front vector
		glm::vec3 front;
		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		Front = glm::normalize(front);
		Right = glm::normalize(glm::cross(Front, WorldUp));
		Up = glm::normalize(glm::cross(Right, Front));
	}
};




#endif /* Camera_h */
