#pragma once
#include "glm/glm.hpp"
#include "Circle.h"
#include "Camera.h"
#include "Model.h"

class Bullet
{
public:
	Bullet(glm::vec3 position, glm::vec3 direction, float speed, float radius, float killDistance, float damage,std::string meshName,std::string audioName);
	void Update(float dt);
	void Render(Camera * cam);
	bool getAlive();
	Circle& getBounds();
	void kill();
	float getDamage();
private:
	glm::vec3 m_initPosition;
	glm::vec3 m_position;
	glm::vec3 m_direction;
	glm::vec3 m_velocity;

	float m_radius;
	float m_damage;

	float m_speed;
	float m_range;
	bool  m_alive ;
	Circle m_bounds;
	Model * m_bulletModel;

	
};
