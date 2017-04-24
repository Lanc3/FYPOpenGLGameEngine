#include "Weapon.h"

Weapon::Weapon(float fov, float range, float damage, float bulletsPerSecond, 
	BulletType bullet, BulletFactory * bulletFactory) 

:	m_bulletFactory(bulletFactory), 
	m_bullet(bullet),
	m_fov(fov),
	m_range(range),
	m_damage(damage),
	m_dirAngle(0),
	m_fireRate(1.0f / bulletsPerSecond),
	m_timeToFire(m_fireRate),
	m_bulletsPerSecond(bulletsPerSecond)
{
}

Weapon::Weapon() {}

void Weapon::Render(Camera * cam)
{
}

void Weapon::Update(glm::vec3 position, float dir, float dt)
{
	m_timeToFire -= dt;
	m_dirAngle = dir;
	m_position = position;
}


float Weapon::getRoF()
{
	return m_bulletsPerSecond;
}
float Weapon::getDamage()
{
	return m_damage;
}
void Weapon::fire()
{
	if (m_timeToFire < 0)
	{
		m_timeToFire = m_fireRate;
		float minAngle = m_dirAngle - m_fov / 2.0f;
		float maxAngle = m_dirAngle + m_fov / 2.0f;
		float angleDirection = RandomFloat(minAngle, maxAngle);
		glm::vec3 fireDirection = glm::vec3(cos(angleDirection),0,sin(angleDirection));
		//fire
		m_bulletFactory->addBullet(m_parentId, m_bullet, m_position, fireDirection, m_range, m_damage);
	}
}

void Weapon::setParentId(std::string parent)
{
	m_parentId = parent;
}
float Weapon::RandomFloat(float min, float max)
{
	// this  function assumes max > min
	float random = ((float)rand()) / (float)RAND_MAX;
	float range = max - min;
	return (random*range) + min;
}

float Weapon::GetRange()
{
	return m_range;
}
