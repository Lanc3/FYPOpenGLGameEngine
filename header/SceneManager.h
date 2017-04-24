#pragma once

#include <SDL.h>
#include "Scene.h"

#include "MenuScene.h"
#include "OptionsScene.h"
#include "ProfileScene.h"
#include "SystemScene.h"
#include "FightingScene.h"
#include <vector>


class SceneManager {
public:
	SceneManager();
	~SceneManager();
	void Update(float dt);
	void Render();
	void HandleInput(float dt);

	void AddScene(Scene* scene);
	void SwitchScene(string name);

	Scene* GetCurrentScene();

private:
	

	Scene* m_currentScene;
	static SceneManager* mInstance;
	std::map<string,Scene*> m_scenes;
};
