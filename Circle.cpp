#include "Circle.h"



Circle::Circle()
{
}

Circle::Circle(glm::vec3 position, float radius)
{
	m_center = position;
	m_radius = radius;
}

void Circle::SetCenter(glm::vec3 position)
{
	m_center = position;
}


Circle::~Circle()
{
}

float Circle::Distance(glm::vec3 a, glm::vec3 b)
{
	return glm::sqrt((a.x - b.x) * (a.x - b.x) + (a.z - b.z) * (a.z - b.z));
}
float Circle::GetDistance(Circle * b)
{
	return glm::sqrt((m_center.x - b->GetCenter().x) * (m_center.x - b->GetCenter().x) + (m_center.z - b->GetCenter().z) * (m_center.z - b->GetCenter().z));
}

bool Circle::LineIntersectsCircle(glm::vec3 ahead2, glm::vec3 ahead)
{
	return Distance(m_center, ahead) <= m_radius || Distance(m_center, ahead2) <= m_radius;
}

glm::vec3 Circle::GetCenter()
{
	return m_center;
}

float Circle::GetRadius()
{
	return m_radius;
}

float Circle::GetMass()
{
	return m_radius;
}
