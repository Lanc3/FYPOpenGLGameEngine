#pragma once
#include "Ship.h"
#include "Camera.h"
#include "Profile.h"

class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();
	void Update(float dt);
	bool GetState();
	void SetTarget(glm::vec3 target);
	void Render(Camera * cam);
	vector<Ship *> GetEnemyList();
private:
	vector<Ship *> m_listOfEnemies;
	Ship* enemy;
	int m_enemyLevel;
	int m_enemyXPValue;
	int m_enemyScaleValue = 50;
	int m_amountToSpawn = 5;
	bool m_alldead = false;
};

