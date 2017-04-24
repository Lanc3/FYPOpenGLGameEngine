#include "EnemyManager.h"



EnemyManager::EnemyManager()
{
	enemy = new Ship(glm::vec3(500, 0, 600), "enemyShip");
	m_listOfEnemies.push_back(enemy);
	m_enemyLevel = Profile::getInstance()->GetLevel();
	m_enemyXPValue = m_enemyLevel * m_enemyScaleValue;
}


EnemyManager::~EnemyManager()
{
}

void EnemyManager::Update(float dt)
{
	for (int i = 0; i < m_listOfEnemies.size(); i++)
	{
		if (m_listOfEnemies.at(i)->IsAlive())
		{
			m_listOfEnemies.at(i)->Update(dt);
		}
		else
		{
			delete m_listOfEnemies[i];
			m_listOfEnemies[i] = nullptr;
			m_listOfEnemies.erase(m_listOfEnemies.begin() + i);
		}
	}
}
void EnemyManager::SetTarget(glm::vec3 target)
{
	for (const auto& itr : m_listOfEnemies)
	{
		itr->SetMovePosition(target);
	}
}

void EnemyManager::Render(Camera * cam)
{
	for (const auto& itr : m_listOfEnemies)
	{
		itr->Render(cam);
	}
}

vector<Ship*> EnemyManager::GetEnemyList()
{
	return m_listOfEnemies;
}
