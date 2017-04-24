#pragma once

#include <SDL.h>
#include <algorithm>

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include <GLFW/glfw3.h>
#include <iostream>
#define PI 3.141592635
class Camera
{
public:
	Camera();
	Camera(glm::vec3 startingPosition, glm::vec3 up);
	~Camera();

	void Update(float dt);

	void SetYaw(GLfloat yaw);
	void SetZoom(float zoom);
	void SubtractZoom(float amount);
	void AddZoom(float amount);
	void SetTarget(glm::vec3 target);
	// Returns the view matrix calculated using Eular Angles and the LookAt Matrix
	glm::mat4 GetViewMatrix();
	glm::vec3 GetTarget();
	float GetZoom();
	glm::vec3 GetPosition();
	void SetPosition(glm::vec3 position);
	void SetOffset(glm::vec3 offset);
private:
	glm::mat4 m_view;

	// Camera Attributes
	glm::vec3 m_position;
	glm::vec3 m_offset = glm::vec3(0, 4, -15);
	glm::vec3 m_front;
	glm::vec3 m_upAxis;
	glm::vec3 m_rightAxis;
	glm::vec3 m_worldUp;

	glm::vec3 m_targetOffset;
	glm::vec3 m_target;

	// Eular Angles
	GLfloat m_yaw;
	GLfloat m_pitch;

	// Camera options
	GLfloat m_speed;
	GLfloat m_acceleration;
	float m_zoom;
	float m_zoomSpeed = 5;
	void SetupCameraAttributes();
};


