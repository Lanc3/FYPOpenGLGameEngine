#include "SceneManager.h"

SceneManager::SceneManager()
{
	m_currentScene = nullptr;
	
}

SceneManager::~SceneManager()
{
	m_currentScene = nullptr;
}

void SceneManager::Update(float dt) {
	if (m_currentScene != nullptr || m_currentScene != NULL)
	{
		m_currentScene->Update(dt);


		if (!m_currentScene->IsAlive())
		{
			m_currentScene->Stop();
			m_currentScene->SetDead();
			m_currentScene = m_scenes[m_currentScene->CheckNext()];
			m_currentScene->SetAlive();
			m_currentScene->Start();
		}
	}
}

void SceneManager::Render() { 
	if (m_currentScene != nullptr)
	{
		m_currentScene->Render();
	}
}

void SceneManager::HandleInput(float dt) {
	if (m_currentScene != nullptr)
	{
		m_currentScene->HandleInput(dt);
	}
}

void SceneManager::AddScene(Scene* scene)
{
	m_scenes[scene->GetName()]= scene;
}

void SceneManager::SwitchScene(std::string name)
{
	if (m_currentScene == nullptr)
	{
		m_currentScene = m_scenes[name];
		m_currentScene->Start();
	}
	if (m_currentScene != nullptr)
	{
		m_currentScene->Stop();
		m_currentScene = m_scenes[name];
		m_currentScene->Start();
	}
}



Scene* SceneManager::GetCurrentScene() { return m_currentScene; }