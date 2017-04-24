#include "FightingScene.h"



FightingScene::FightingScene(SDL_Window* window, ISoundEngine * sound) : Scene("Fighting",sound)
{
	//SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	m_spriteRenderer = new SpriteRenderer(ResourceManager::getInstance()->GetShader("sprite"));
	m_cam = new Camera(glm::vec3(0, 0, 0), glm::vec3(0.0f, 1.0f, 0.0f));
	m_sky.init();
	m_shader = ResourceManager::getInstance()->GetShader("texture");
	m_pointer = new Entity();
	pointerPosition = glm::vec3(0, 0, 0);
	m_bulletFactory = new BulletFactory();
	WeaponFactory::getInstance()->createWeapons(m_bulletFactory);
	
	m_Weapon = Weapon(WeaponFactory::getInstance()->getNewWeapon(WeaponType::SHORT));
	m_Weapon.Update(glm::vec3(0, 0, 0), 90, 0);
	m_player = Ship(glm::vec3(0,0,0),"playerShip");
	m_hpShieldBar = ProgressBar("name", glm::vec2(465, 660), Profile::GetInstance()->GetShipShieldAmount(), Profile::GetInstance()->GetShipHullAmount());
	m_enemyManager = EnemyManager();
}

FightingScene::~FightingScene()
{
	delete m_pointer;
	m_pointer = nullptr;
}
void FightingScene::Start()
{
	
	if (m_inputManager->IsControllerConnected())
	{

		BindKeys();
	}
	bgSound = m_soundEngine->play2D("Assets\\audio\\fighting.wav", GL_TRUE, GL_TRUE);
	bgSound->setVolume(0.3);

	//m_pointer = new Entity();
	pointerPosition = glm::vec3(0, 0, 0);
	m_bulletFactory = new BulletFactory();
	WeaponFactory::getInstance()->createWeapons(m_bulletFactory);

	m_Weapon = Weapon(WeaponFactory::getInstance()->getNewWeapon(WeaponType::SHORT));
	m_Weapon.Update(glm::vec3(0, 0, 0), 90, 0);
	m_player = Ship(glm::vec3(0, 0, 0), "playerShip");
	m_hpShieldBar = ProgressBar("name", glm::vec2(465, 660), Profile::GetInstance()->GetShipShieldAmount(), Profile::GetInstance()->GetShipHullAmount());
	m_enemyManager = EnemyManager();

	SetUpEntitys();
	SetUpSystems();                      
}
void FightingScene::BindKeys()
{
	Command* select = new SpaceCommand(std::bind(&FightingScene::SelectKey, this), Press);
	m_inputManager->AddKey(Event::BUTTON_A, select, this);
	Command* shoot = new SpaceCommand(std::bind(&FightingScene::ShootLeft, this), Press);
	m_inputManager->AddKey(Event::BUTTON_B, shoot, this);
	Command* shootLeft = new SpaceCommand(std::bind(&FightingScene::ShootRight, this), Press);
	m_inputManager->AddKey(Event::BUTTON_X, shootLeft, this);
	Command* shortIdicator = new SpaceCommand(std::bind(&FightingScene::ToggleShortIndicator, this), Press);
	m_inputManager->AddKey(Event::BUTTON_LEFTSHOULDER, shortIdicator, this);
	Command* longIdicator = new SpaceCommand(std::bind(&FightingScene::ToggleLongIndicator, this), Press);
	m_inputManager->AddKey(Event::BUTTON_RIGHTSHOULDER, longIdicator, this);
	Command* shootLong = new SpaceCommand(std::bind(&FightingScene::ShootLong, this), Press);
	m_inputManager->AddKey(Event::BUTTON_Y, shootLong, this);
	Command* moveLine = new SpaceCommand(std::bind(&FightingScene::ToggleMoveLine, this), Press);
	m_inputManager->AddKey(Event::BUTTON_BACK, moveLine, this);
}

void FightingScene::ToggleMoveLine()
{
	m_player.ToggleMoveLineIndicator();
	for (const auto & itr : m_enemyManager.GetEnemyList())
	{
		itr->ToggleMoveLineIndicator();
	}
}
void FightingScene::ToggleShortIndicator()
{
	m_player.ToggleShortRangeIndicator();
}
void FightingScene::ToggleLongIndicator()
{
	m_player.ToggleLongRangeIndicator();
}

void FightingScene::ShootLeft()
{
	Transformable* ent = (Transformable*)m_pointer->GetComponent("transformable");
	m_player.SetTargetShortLeft(ent->m_position);
}
void FightingScene::ShootRight()
{
	Transformable* ent = (Transformable*)m_pointer->GetComponent("transformable");
	m_player.SetTargetShortRight(ent->m_position);
}

void FightingScene::ShootLong()
{
	Transformable* ent = (Transformable*)m_pointer->GetComponent("transformable");
	m_player.SetTargetLong(ent->m_position);
}

void FightingScene::SelectKey()
{
	Transformable* ent = (Transformable*)m_pointer->GetComponent("transformable");
	m_player.SetMovePosition(ent->m_position);
}

void FightingScene::Render()
{
	m_sky.render(m_cam, 1280, 720);
	if (!m_isPaused)
	{
		m_renderSystem.Draw(m_cam, m_shader);
	}
	m_polygonBoundsSystem.Draw(m_cam);

	m_spriteRenderer->DrawSprite(ResourceManager::getInstance()->GetSprite("systemContainer"),
		glm::vec2(440, 0), glm::vec2(370, 60), 0, glm::vec3(1.0f, 1.0f, 1.0f));
	RenderText("Fight !!!", 450, 680, 0.65f, glm::vec3(0, 155, 254));


	if (Profile::GetInstance()->GetAchievements("10Kills"))
	{
		m_spriteRenderer->DrawSprite(ResourceManager::getInstance()->GetSprite("10KillsDone"),
			glm::vec2(1200, 0), glm::vec2(60, 60), 0, glm::vec3(1.0f, 1.0f, 1.0f));
	}
	else
	{
		m_spriteRenderer->DrawSprite(ResourceManager::getInstance()->GetSprite("10Kills"),
			glm::vec2(1200, 0), glm::vec2(60, 60), 0, glm::vec3(1.0f, 1.0f, 1.0f));
	}
	if (Profile::GetInstance()->GetAchievements("100Kills"))
	{
		m_spriteRenderer->DrawSprite(ResourceManager::getInstance()->GetSprite("100KillsDone"),
			glm::vec2(1200, 80), glm::vec2(60, 60), 0, glm::vec3(1.0f, 1.0f, 1.0f));
	}
	else
	{
		m_spriteRenderer->DrawSprite(ResourceManager::getInstance()->GetSprite("100Kills"),
			glm::vec2(1200, 80), glm::vec2(60, 60), 0, glm::vec3(1.0f, 1.0f, 1.0f));
	}
	if (Profile::GetInstance()->GetAchievements("1KKills"))
	{
		m_spriteRenderer->DrawSprite(ResourceManager::getInstance()->GetSprite("1KKillsDone"),
			glm::vec2(1200, 160), glm::vec2(60, 60), 0, glm::vec3(1.0f, 1.0f, 1.0f));
	}
	else
	{
		m_spriteRenderer->DrawSprite(ResourceManager::getInstance()->GetSprite("1KKills"),
			glm::vec2(1200, 160), glm::vec2(60, 60), 0, glm::vec3(1.0f, 1.0f, 1.0f));
	}
	if (Profile::GetInstance()->GetAchievements("1MKills"))
	{
		m_spriteRenderer->DrawSprite(ResourceManager::getInstance()->GetSprite("1MKillsDone"),
			glm::vec2(1200, 240), glm::vec2(60, 60), 0, glm::vec3(1.0f, 1.0f, 1.0f));
	}
	else
	{
		m_spriteRenderer->DrawSprite(ResourceManager::getInstance()->GetSprite("1MKills"),
			glm::vec2(1200, 240), glm::vec2(60, 60), 0, glm::vec3(1.0f, 1.0f, 1.0f));
	}
	m_Weapon.Render(m_cam);
	m_bulletFactory->Render(m_cam);
	m_player.Render(m_cam);
	m_hpShieldBar.Render(m_cam, m_spriteRenderer, this);
	m_enemyManager.Render(m_cam);
	if (m_isPaused)
	{
		m_spriteRenderer->DrawSprite(ResourceManager::getInstance()->GetSprite("systemContainer"),
			glm::vec2(440, 360), glm::vec2(370, 80), 0, glm::vec3(1.0f, 1.0f, 1.0f));
		RenderText("Paused", 450, 340, 0.65f, glm::vec3(0, 155, 254));
	}
}

void FightingScene::Update(float dt)
{
	if (!m_isPaused)
	{
		m_transformSystem.Update(dt);
		m_polygonBoundsSystem.Update(dt);
		m_cameraSystem.Chase(dt);
		PolygonBounds* pB = (PolygonBounds*)m_pointer->GetComponent("polygonBounds");
		m_Weapon.Update(glm::vec3(10, 0, 10), 90, dt);
		m_bulletFactory->Update(dt);
		m_player.Update(dt);
		m_hpShieldBar.SetCurrentShieldAmount(m_player.GetCurrentShield());
		m_hpShieldBar.SetCurrentHullAmount(m_player.GetCurrentHp());
		m_hpShieldBar.Update(dt);
		m_enemyManager.Update(dt);
		for (const auto & itr : m_enemyManager.GetEnemyList())
		{
			itr->SetMovePosition(m_player.GetPosition());
			if (glm::distance(itr->GetPosition(), m_player.GetPosition()) < 500)
			{
				itr->SetTargetLong(m_player.GetPosition());
				//if(itr->)
				for (const auto & itrs : itr->GetBulletList())
				{
					if (m_player.GetBounds().Intersets(&itrs->getBounds())) 
					{
						m_player.DamageShip(10);
						itrs->kill();
					}
				}
			}

			for (const auto & itrs : m_player.GetBulletList())
			{
				if (itr->GetBounds().Intersets(&itrs->getBounds()))
				{
					itr->DamageShip(itrs->getDamage());
					itrs->kill();
				}
			}
		}
	}
	bgSound->setIsPaused(false);
	if (!m_player.IsAlive())
	{
		this->GoToScene("Profile");
	}
	if (m_enemyManager.GetState())
	{
		this->GoToScene("Profile");
	}
}

void FightingScene::HandleInput(float dt)
{
	m_controllerSystem.HandleInput(dt);
	m_controllerSystem.CameraZoomControlls(m_cam);
}

void FightingScene::SetUpEntitys()
{
	vector<glm::vec2*> boundPoints;
	for (int i = 10; i != 0; i--)
	{
		boundPoints.push_back(new glm::vec2(20 * cos(glm::radians(i * 36.0f)), 20 * sin(glm::radians(i * 36.0f))));
	}

	m_pointer = new Entity();
	m_pointer->AddComponent(new Transformable(glm::vec3(80, 0, 80), 0, 0, 0));
	Transformable* ent = (Transformable*)m_pointer->GetComponent("transformable");
	m_pointer->AddComponent(new ModelMesh("pointerIcon", ent->m_position, glm::vec3(10, 10, 10), 0));
	m_pointer->AddComponent(new Velocity(0.1f, 1.f, 5.f));
	m_pointer->AddComponent(new PolygonBounds(boundPoints, ent->m_position));
	PolygonBounds* color = (PolygonBounds*)m_pointer->GetComponent("polygonBounds");
	color->m_bounds->SetColor(glm::vec4(0, 155, 254, 1));
	m_pointer->AddComponent(new IDTag("pointer"));
	m_pointer->AddComponent(new CircleBounds(ent->m_position, 5));

}

void FightingScene::SetUpSystems()
{
	m_renderSystem = RenderSystem();
	m_controllerSystem = ControllerSystem();
	m_transformSystem = TransformSystem();
	m_cameraSystem = CameraSystem(m_cam, m_pointer);
	m_polygonBoundsSystem = PolygonBoundsSystem();

	m_renderSystem.AddEntity(m_pointer);
	m_controllerSystem.SetEntity(m_pointer);
	m_transformSystem.AddEntity(m_pointer);
	m_polygonBoundsSystem.AddEntity(m_pointer);

}



