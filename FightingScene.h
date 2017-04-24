#pragma once
#include "Scene.h"
#include "SkyBox.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "glm/glm.hpp"
#include "Model.h"
#include "Shader.h"
#include "Entity.h"
#include "Components.h"
#include "RenderSystem.h"
#include "ControllerSystem.h"
#include "TransformSystem.h"
#include "CameraSystem.h"
#include "CollisionManager.h"
#include "PolygonBoundsSystem.h"
#include "Node.h"
#include "SpriteRenderer.h"
#include "Weapon.h"
#include "BulletFactory.h"
#include "WeaponFactory.h"
#include "Ship.h"
#include "ProgressBar.h"
#include "EnemyManager.h"

class FightingScene : public Scene
{
public:
	FightingScene(SDL_Window* window, ISoundEngine * sound);
	~FightingScene();
	void Start();
	void BindKeys();
	void ToggleShortIndicator();
	void ToggleLongIndicator();
	void ShootLeft();
	void ShootRight();
	void ShootLong();
	void SelectKey();
	void Render();
	void Update(float dt);
	void HandleInput(float dt);
private:
	void SetUpEntitys();
	void SetUpSystems();
	Skybox m_sky;
	Camera* m_cam;
	Model pointer;
	Shader m_shader;
	glm::vec3 pointerPosition;

	Entity * m_pointer;
	Entity * m_testEntity;

	RenderSystem m_renderSystem;
	TransformSystem m_transformSystem;
	ControllerSystem m_controllerSystem;
	CameraSystem m_cameraSystem;
	PolygonBoundsSystem m_polygonBoundsSystem;
	SDL_Renderer * m_renderer;
	bool m_isPaused = false;

	SpriteRenderer * m_spriteRenderer;
	Weapon m_Weapon;
	BulletFactory * m_bulletFactory;
	Ship m_player;
	ProgressBar m_hpShieldBar;
	ISound * bgSound;
	EnemyManager m_enemyManager;
};

