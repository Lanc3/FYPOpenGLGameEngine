#include "BulletFactory.h"
#include "Bullet.h"
#include <iostream>

BulletFactory::BulletFactory()
{
	
}

void BulletFactory::addBullet(std::string meshName, BulletType bullet, glm::vec3 position, glm::vec3 direction, float range, float damage)
{
	float bulletSpeed = 0;
	float radius = 1;
	
	std::string modelName,audioName;

	//use this switch statement to pass in different spritesheets/other 
	//vars to different bullets depending on type
	switch (bullet)
	{
	case BulletType::SHORT:
		bulletSpeed = 150;
		radius = SHORT_RADIUS;
		modelName = SHORT_MESH_NAME;
	case BulletType::LONG:
		bulletSpeed = 150;
		radius = SHORT_RADIUS;
		modelName = SHORT_MESH_NAME;
		//audioName = BULLET_STATS::PLASMA_AUDIO_NAME;
		break;
	default:
		return;
	}

	m_bulletList.push_back(new Bullet(position, direction, bulletSpeed, radius, range, damage, modelName,audioName));

}

std::vector<Bullet *> BulletFactory::getBullets()
{
	return m_bulletList;
}

void BulletFactory::Render(Camera * cam)
{
	for (int i = 0; i < m_bulletList.size(); i++)
	{
		m_bulletList.at(i)->Render(cam);
	}

}

void BulletFactory::Update(float dt)
{
	for (int i = 0; i < m_bulletList.size(); i++)
	{
		if (m_bulletList.at(i)->getAlive())
		{
			m_bulletList.at(i)->Update(dt);
		}
		else
		{
			delete m_bulletList[i];
			m_bulletList[i] = nullptr;
			m_bulletList.erase(m_bulletList.begin() + i);
		}

	}
}

