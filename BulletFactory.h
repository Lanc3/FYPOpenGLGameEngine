#pragma once
#include "glm\glm.hpp"
#include <vector>
#include "Bullet.h"

enum class BulletType{ SHORT,LONG,ULT };



class BulletFactory
{
public:

	BulletFactory();
	//updates all the bullets in the list
	void Update(float dt);

	//draws all the bullets in the list
	void Render(Camera * cam);

	//creates a bullet and places it inside the bulletList to be updated
	void addBullet(std::string parentId, BulletType bullet, glm::vec3 position, glm::vec3 direction, float range, float damage);

	std::vector<Bullet *> getBullets();

private:
	std::vector<Bullet *> m_bulletList;
	float const SHORT_SPEED = 150;
	float const SHORT_RADIUS = 15;
	string const SHORT_MESH_NAME = "pickup";
	const std::string LONG_AUDIO_NAME;
	float const LONG_SPEED = 150;// defined in GameConstants.cpp	

	
};



