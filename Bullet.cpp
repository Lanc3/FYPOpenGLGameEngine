#include "Bullet.h"

Bullet::Bullet(glm::vec3 position, glm::vec3 direction, float speed, float radius, float killDistance, float damage, string meshName, std::string audioName)
	: m_position(position),
	m_initPosition(position),
	m_range(killDistance),
	m_speed(speed),
	m_radius(radius),
	m_direction(direction),
	m_bounds(Circle(position, radius)),
	m_alive(true),
	m_damage(damage),
	m_bulletModel(new Model(meshName,position,glm::vec3(0.012f, 0.012f, 0.012f),0))
{
}


float Bullet::getDamage()
{
	return m_damage;
}

void Bullet::Update(float dt)
{
	m_velocity = m_direction * m_speed * dt;
	m_position += m_velocity;
	m_bounds.SetCenter(m_position);
	m_bulletModel->setPosition(m_position);
	m_bulletModel->Update();
	if (glm::distance(m_position, m_initPosition) > m_range)
	{
		kill();
	}
}
void Bullet::kill()
{
	m_alive = false;
	if (m_bulletModel != nullptr)
	m_bulletModel = nullptr;
}
Circle& Bullet::getBounds()
{
	return m_bounds;
}

void Bullet::Render(Camera * cam)
{
	if (m_bulletModel != nullptr)
	{
		m_bulletModel->Render(cam);
	}
}

bool Bullet::getAlive()
{
	return m_alive;
}
