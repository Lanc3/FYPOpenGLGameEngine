#include "Camera.h"


Camera::Camera()
{
}


Camera::Camera(glm::vec3 startingPosition, glm::vec3 up)
{
	m_position = startingPosition;
	m_worldUp = up;
	m_target = startingPosition;
	SetupCameraAttributes();
}

Camera::~Camera()
{

}

void Camera::SetupCameraAttributes()
{
	m_yaw = 0.0f;
	m_pitch = 0.0f;
	m_speed = 0.1f;
	m_zoom = 150;
}

void Camera::Update(float dt)
{
	glm::mat4 R = glm::yawPitchRoll((GLfloat)(m_yaw + (PI/2)), 0.0f, 0.0f);
	//GLfloat R = m_yaw + (PI / 2);
	glm::vec3 offset = glm::vec3(0, m_zoom, -m_zoom);

	offset = glm::vec3(R*glm::vec4(offset, 0.0f));

	m_position = m_target + offset;

	m_front = glm::normalize(m_target - m_position);
	m_upAxis = glm::normalize(glm::vec3(R*glm::vec4(m_worldUp, 0.0f)));
	m_rightAxis = glm::normalize(glm::cross(m_front, m_upAxis));

	m_view = glm::lookAt(m_position, m_target, m_upAxis);
}

void Camera::SetYaw(GLfloat yaw) {	m_yaw = yaw; }
void Camera::SetTarget(glm::vec3 target) {	m_target = target; }
glm::mat4 Camera::GetViewMatrix() { return m_view; }
glm::vec3 Camera::GetTarget() { return m_target; }
float Camera::GetZoom() { return m_zoom; }
void Camera::SetPosition(glm::vec3 position) {	m_position = position; }
void Camera::SetOffset(glm::vec3 offset)
{
}
void Camera::SetZoom(float zoom) { m_zoom = zoom; }
void Camera::SubtractZoom(float amount)
{
	m_zoom -= amount*m_zoomSpeed;
}
void Camera::AddZoom(float amount)
{
	m_zoom += amount * m_zoomSpeed;
}
glm::vec3 Camera::GetPosition() { return m_position; }