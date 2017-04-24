#pragma once
#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Circle
{
public:
	Circle();
	Circle(glm::vec3 position, float radius);
	void SetCenter(glm::vec3 position);
	~Circle();
	bool Intersets(Circle * circle);
	float Distance(glm::vec3 objectA, glm::vec3 objectB);
	float GetDistance(Circle * b);
	bool LineIntersectsCircle(glm::vec3 ahead2, glm::vec3 ahead);

	glm::vec3 GetCenter();
	float GetRadius();
	float GetMass();
private:
	glm::vec3 m_center;
	float m_radius;
	float m_mass;
};

