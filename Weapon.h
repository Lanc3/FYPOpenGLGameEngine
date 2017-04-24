#pragma once
#include "glm/glm.hpp"
#include "Camera.h"
#include "BulletFactory.h"

class Weapon
{
public:
	Weapon();
	Weapon(float fov, float range, float damage, float bulletsPerSecond, BulletType bullet, BulletFactory * bulletFactory);
	void Render(Camera * cam);
	void Update(glm::vec3 position, float dir, float dt);
	void fire();
	float getRoF();
	float getDamage();
	void setParentId(std::string parentId);

	float RandomFloat(float min, float max);

	float GetRange();

private:
	float m_range;
	float m_timeToFire;
	float m_fireRate;
	float m_damage;
	float m_fov;
	float m_dirAngle;
	glm::vec3 m_position;
	BulletType m_bullet;
	BulletFactory *m_bulletFactory;
	float m_bulletsPerSecond;
	std::string m_parentId;
};


