#include "SystemScene.h"



SystemScene::SystemScene(SDL_Window* window, ISoundEngine * sound) : Scene("System",sound)
{
	//SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	m_spriteRenderer = new SpriteRenderer(ResourceManager::getInstance()->GetShader("sprite"));
	m_cam = new Camera(glm::vec3(0,0,0), glm::vec3(0.0f, 1.0f, 0.0f));
	//m_cam->SetOffset(glm::vec3(300, 300, 300));
	//m_cam->SetTarget(glm::vec3(0, 0, 0));
	m_sky.init();

	pointer =  Model("pickup", glm::vec3(0, 0, 0), glm::vec3(100, 100, 100), 0);
	m_shader =  ResourceManager::getInstance()->GetShader("texture");

	pointerPosition = glm::vec3(0, 0, 0);

	m_pointer = new Entity();
	star = Node(0, glm::vec3(10, 0, 10),this);
	star.SetState(STATE::IS_CREATING);
	
}


SystemScene::~SystemScene()
{
	delete m_pointer;
	m_pointer = nullptr;
}
void SystemScene::Start()
{
	SetUpEntitys();
	SetUpSystems();
	if (m_inputManager->IsControllerConnected())
	{

		BindKeys();
	}
	star.Start();
}
void SystemScene::BindKeys()
{
	Command* select = new SpaceCommand(std::bind(&SystemScene::SelectKey, this), Press);
	m_inputManager->AddKey(Event::BUTTON_A, select, this);
}

void SystemScene::SelectKey()
{
	//star.SetIsSelected();
}

void SystemScene::Render()
{
	m_sky.render(m_cam, 1280, 720);
	//m_shader.Use();
	//pointer.Draw(m_cam, m_shader);
	m_renderSystem.Draw(m_cam, m_shader);
	m_polygonBoundsSystem.Draw(m_cam);


	CircleBounds* ent = (CircleBounds*)m_pointer->GetComponent("circleBounds");
	star.SetPointerCollision(ent->m_bounds);
	star.Render(m_cam, m_spriteRenderer);

	m_spriteRenderer->DrawSprite(ResourceManager::getInstance()->GetSprite("systemContainer"),
		glm::vec2(440, 0), glm::vec2(370, 80), 0, glm::vec3(1.0f, 1.0f, 1.0f));
	RenderText("Universe View ", 450, 680, 0.65f, glm::vec3(0, 155, 254));


	if (Profile::GetInstance()->GetAchievements("10Kills"))
	{
		m_spriteRenderer->DrawSprite(ResourceManager::getInstance()->GetSprite("10KillsDone"),
			glm::vec2(1200, 0), glm::vec2(60, 60), 0, glm::vec3(1.0f, 1.0f, 1.0f));
	}
	else
	{
		m_spriteRenderer->DrawSprite(ResourceManager::getInstance()->GetSprite("10Kills"),
			glm::vec2(1200, 80), glm::vec2(60, 60), 0, glm::vec3(1.0f, 1.0f, 1.0f));
	}
	if (Profile::GetInstance()->GetAchievements("100Kills"))
	{
		m_spriteRenderer->DrawSprite(ResourceManager::getInstance()->GetSprite("100KillsDone"),
			glm::vec2(1200, 160), glm::vec2(60, 60), 0, glm::vec3(1.0f, 1.0f, 1.0f));
	}
	else
	{
		m_spriteRenderer->DrawSprite(ResourceManager::getInstance()->GetSprite("100Kills"),
			glm::vec2(1200, 240), glm::vec2(60, 60), 0, glm::vec3(1.0f, 1.0f, 1.0f));
	}
	if (Profile::GetInstance()->GetAchievements("1KKills"))
	{
		m_spriteRenderer->DrawSprite(ResourceManager::getInstance()->GetSprite("1KKillsDone"),
			glm::vec2(1200, 320), glm::vec2(60, 60), 0, glm::vec3(1.0f, 1.0f, 1.0f));
	}
	else
	{
		m_spriteRenderer->DrawSprite(ResourceManager::getInstance()->GetSprite("1KKills"),
			glm::vec2(1200, 400), glm::vec2(60, 60), 0, glm::vec3(1.0f, 1.0f, 1.0f));
	}
	if (Profile::GetInstance()->GetAchievements("1MKills"))
	{
		m_spriteRenderer->DrawSprite(ResourceManager::getInstance()->GetSprite("1MKillsDone"),
			glm::vec2(1200, 480), glm::vec2(60, 60), 0, glm::vec3(1.0f, 1.0f, 1.0f));
	}
	else
	{
		m_spriteRenderer->DrawSprite(ResourceManager::getInstance()->GetSprite("1MKills"),
			glm::vec2(1200, 560), glm::vec2(60, 60), 0, glm::vec3(1.0f, 1.0f, 1.0f));
	}
}

void SystemScene::Update(float dt)
{
	m_transformSystem.Update(dt);
	m_polygonBoundsSystem.Update(dt);
	m_cameraSystem.Chase(dt);
	PolygonBounds* pB = (PolygonBounds*)m_pointer->GetComponent("polygonBounds");
	
	
	star.Update(dt,this);
}

void SystemScene::HandleInput(float dt)
{
	m_controllerSystem.HandleInput(dt);
	m_controllerSystem.CameraZoomControlls(m_cam);
}

void SystemScene::SetUpEntitys()
{
	vector<glm::vec2*> boundPoints;
	for (int i = 10; i != 0; i--)
	{
		boundPoints.push_back(new glm::vec2(20 * cos(glm::radians(i * 36.0f)), 20 * sin(glm::radians(i * 36.0f))));
	}

	m_pointer = new Entity();
	m_pointer->AddComponent(new Transformable(glm::vec3(80,0,80), 0, 0, 0));
	Transformable* ent = (Transformable*)m_pointer->GetComponent("transformable");
	m_pointer->AddComponent(new ModelMesh("pointerIcon", ent->m_position, glm::vec3(10, 10, 10), 0));
	m_pointer->AddComponent(new Velocity(0.1f, 1.f, 5.f));
	m_pointer->AddComponent(new PolygonBounds(boundPoints, ent->m_position));
	PolygonBounds* color = (PolygonBounds*)m_pointer->GetComponent("polygonBounds");
	color->m_bounds->SetColor(glm::vec4(0, 155, 254, 1));
	m_pointer->AddComponent(new IDTag("pointer"));
	m_pointer->AddComponent(new CircleBounds(ent->m_position, 5));


}

void SystemScene::SetUpSystems()
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



