#include "EnemyManager.h"



EnemyManager::EnemyManager()
{
	m_enemyLevel = Profile::GetInstance()->GetLevel();
	m_enemyXPValue = m_enemyLevel * m_enemyScaleValue;
	m_amountToSpawn = Profile::GetInstance()->GetEnemyCount();

	
	for (int i = 0; i != m_amountToSpawn; i++)
	{
		float r = rand() % (4000 - 600) + 600;
		float a = rand() % (360 - 0);
		enemy = new Ship(glm::vec3(r *cos(glm::radians(a)), 0, r *sin(glm::radians(a))), "enemyShip");
		m_listOfEnemies.push_back(enemy);
	}
		
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
			Profile::GetInstance()->AddExp(40);
			delete m_listOfEnemies[i];
			m_listOfEnemies[i] = nullptr;
			m_listOfEnemies.erase(m_listOfEnemies.begin() + i);
		}
	}
	if (m_listOfEnemies.size() <= 0)
	{
		m_alldead = true;
	}
}
bool EnemyManager::GetState()
{
	return m_alldead;
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
