#include "Game.h"

using namespace std;

Game::Game() : m_running(false)
{
	SoundEngine = createIrrKlangDevice();
}

Game::~Game()
{

}

bool Game::Initialize()
{
#pragma region InitialiseWindow

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		m_Window = SDL_CreateWindow("The Expanse", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL);
		//SDL_SetWindowFullscreen(m_Window, SDL_WINDOW_FULLSCREEN);
		if (m_Window != 0)
		{
			m_context = SDL_GL_CreateContext(m_Window);
			SetOpenGLAttributes();
			SDL_GL_SetSwapInterval(-1);
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
	glewExperimental = GL_TRUE;
	glewInit();
#pragma endregion
#pragma region SetupScenes

	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_PRESENTVSYNC);

	m_sceneManager = new SceneManager();

	LoadResources();

	m_sceneManager->AddScene(new MenuScene(m_Renderer,m_Window, SoundEngine));
	m_sceneManager->AddScene(new OptionsScene(m_Renderer, SoundEngine));
	m_sceneManager->AddScene(new SystemScene(m_Window, SoundEngine));
	m_sceneManager->AddScene(new FightingScene(m_Window, SoundEngine));
	m_sceneManager->AddScene(new ProfileScene(m_Renderer, SoundEngine));
	m_sceneManager->SwitchScene("Menu");
#pragma endregion

	m_running = true;
	return true;
}

void Game::LoadResources()
{
	ResourceManager::getInstance()->SetUp(m_Renderer);
	//Load Shaders

	ResourceManager::getInstance()->AddAssetToQueue(new ShaderData("Shaders\\skyBoxShader.vs", "Shaders\\skyBoxShader.frag",nullptr, "skybox"));
	ResourceManager::getInstance()->AddAssetToQueue(new ShaderData("Shaders\\texture.vs", "Shaders\\texture.frag", nullptr, "texture"));
	ResourceManager::getInstance()->AddAssetToQueue(new ShaderData("Shaders\\textureSun.vs", "Shaders\\textureSun.frag", nullptr, "cube"));
	ResourceManager::getInstance()->AddAssetToQueue(new ShaderData("Shaders\\basic.vs", "Shaders\\basic.frag", nullptr, "basic"));
	ResourceManager::getInstance()->AddAssetToQueue(new ShaderData("Shaders\\texture.vs", "Shaders\\texture.frag", nullptr, "ground"));
	ResourceManager::getInstance()->AddAssetToQueue(new ShaderData("Shaders\\lightShader.vs", "Shaders\\lightShader.frag", nullptr, "model"));
	ResourceManager::getInstance()->AddAssetToQueue(new ShaderData("Shaders\\textShader.vs", "Shaders\\textShader.frag", nullptr, "text"));
	ResourceManager::getInstance()->AddAssetToQueue(new ShaderData("Shaders\\sprite.vs", "Shaders\\sprite.frag", nullptr, "sprite"));
	
	//Load Models
	ResourceManager::getInstance()->AddAssetToQueue(new ModelData("Assets\\Models\\pickupPoint.obj", "pickup"));
	ResourceManager::getInstance()->AddAssetToQueue(new ModelData("Assets\\Models\\pointericon.obj", "pointerIcon"));
	ResourceManager::getInstance()->AddAssetToQueue(new ModelData("Assets\\Models\\galaxy.obj", "galaxy"));
	ResourceManager::getInstance()->AddAssetToQueue(new ModelData("Assets\\Models\\playerShip.obj", "playerShip"));
	ResourceManager::getInstance()->AddAssetToQueue(new ModelData("Assets\\Models\\thesisenemyship.obj", "enemyShip"));
	//Load Images

#pragma region Loading Menu Scene stuff
			//MAIN MENU
	ResourceManager::getInstance()->AddAssetToQueue(new TextureLoadingData("Assets\\Images\\bg.bmp", "MenuBackground", glm::vec2(0, 0)));
	ResourceManager::getInstance()->AddAssetToQueue(new TextureLoadingData("Assets\\Images\\button.png", "PlayButton", glm::vec2(500, 510)));
	ResourceManager::getInstance()->AddAssetToQueue(new TextureLoadingData("Assets\\Images\\button.png", "OptButton", glm::vec2(500, 575)));
	ResourceManager::getInstance()->AddAssetToQueue(new TextureLoadingData("Assets\\Images\\button.png", "QuitButton", glm::vec2(500, 650)));
	ResourceManager::getInstance()->AddAssetToQueue(new TextData("play", "PlayText", 20, glm::vec2(530, 530), glm::vec4(0, 150, 245, 255)));
	ResourceManager::getInstance()->AddAssetToQueue(new TextData("options", "OptionsText", 20, glm::vec2(530, 595), glm::vec4(0, 150, 245, 255)));
	ResourceManager::getInstance()->AddAssetToQueue(new TextData("quit", "QuitText", 20, glm::vec2(530, 670), glm::vec4(0, 150, 245, 255)));
	ResourceManager::getInstance()->AddAssetToQueue(new TextureLoadingData("Assets\\Images\\selectedButton.png", "highlight", glm::vec3(0, 0, 0)));
	//sprite data
	ResourceManager::getInstance()->AddAssetToQueue(new SpriteData("Assets\\Images\\10Kills.png", GL_TRUE,"sprite"));
	ResourceManager::getInstance()->AddAssetToQueue(new SpriteData("Assets\\Images\\InfoBox.png", GL_TRUE, "infoBox"));
	ResourceManager::getInstance()->AddAssetToQueue(new SpriteData("Assets\\Images\\SystemInfoContainer.png", GL_TRUE, "systemContainer"));
	ResourceManager::getInstance()->AddAssetToQueue(new SpriteData("Assets\\Images\\cellHighlight.png", GL_TRUE, "cellHighlight"));
	ResourceManager::getInstance()->AddAssetToQueue(new SpriteData("Assets\\Images\\cellFull.png", GL_TRUE, "cellFull"));
	//achievement sprites
	ResourceManager::getInstance()->AddAssetToQueue(new SpriteData("Assets\\Images\\10Kills.png", GL_TRUE, "10Kills"));
	ResourceManager::getInstance()->AddAssetToQueue(new SpriteData("Assets\\Images\\100Kills.png", GL_TRUE, "100Kills"));
	ResourceManager::getInstance()->AddAssetToQueue(new SpriteData("Assets\\Images\\1KKills.png", GL_TRUE, "1KKills"));
	ResourceManager::getInstance()->AddAssetToQueue(new SpriteData("Assets\\Images\\1MKills.png", GL_TRUE, "1MKills"));
	ResourceManager::getInstance()->AddAssetToQueue(new SpriteData("Assets\\Images\\10KillsDone.png", GL_TRUE, "10KillsDone"));
	ResourceManager::getInstance()->AddAssetToQueue(new SpriteData("Assets\\Images\\100KillsDone.png", GL_TRUE, "100KillsDone"));
	ResourceManager::getInstance()->AddAssetToQueue(new SpriteData("Assets\\Images\\1KKillsDone.png", GL_TRUE, "1KKillsDone"));
	ResourceManager::getInstance()->AddAssetToQueue(new SpriteData("Assets\\Images\\1MKillsDone.png", GL_TRUE, "1MKillsDone"));

	//MULTIPLAYER
	ResourceManager::getInstance()->AddAssetToQueue(new TextureLoadingData("Assets\\Images\\button.bmp", "ConnectButtonMP", glm::vec2(400, 200)));
	ResourceManager::getInstance()->AddAssetToQueue(new TextureLoadingData("Assets\\Images\\button.bmp", "MenuButtonMP", glm::vec2(400, 400)));
	ResourceManager::getInstance()->AddAssetToQueue(new TextData("connect", "connectTextMP", 40, glm::vec2(425, 225), glm::vec4(100, 100, 100, 255)));
	ResourceManager::getInstance()->AddAssetToQueue(new TextData("join game", "JoinTextMP", 40, glm::vec2(425, 425), glm::vec4(100, 100, 100, 255)));

	//OPTIONS
	ResourceManager::getInstance()->AddAssetToQueue(new TextureLoadingData("Assets\\Images\\return.bmp", "ReturnButton", glm::vec2(0, 650)));
	ResourceManager::getInstance()->AddAssetToQueue(new TextureLoadingData("Assets\\Images\\button.png", "AudioOptButton", glm::vec2(500, 510)));
	ResourceManager::getInstance()->AddAssetToQueue(new TextureLoadingData("Assets\\Images\\button.png", "GraphicsOptButton", glm::vec2(500, 575)));
	ResourceManager::getInstance()->AddAssetToQueue(new TextureLoadingData("Assets\\Images\\button.png", "GameOptButton", glm::vec2(500, 650)));
	ResourceManager::getInstance()->AddAssetToQueue(new TextData("options", "OptionsTitle", 40, glm::vec2(475, 50), glm::vec4(0, 150, 245, 255)));
	ResourceManager::getInstance()->AddAssetToQueue(new TextData("audio", "AudioOptText", 20, glm::vec2(530, 530), glm::vec4(0, 150, 245, 255)));
	ResourceManager::getInstance()->AddAssetToQueue(new TextData("graphics", "GraphicsOptText", 20, glm::vec2(530, 595), glm::vec4(0, 150, 245, 255)));
	ResourceManager::getInstance()->AddAssetToQueue(new TextData("back", "GameOptText", 20, glm::vec2(530, 670), glm::vec4(0, 150, 245, 255)));

	//PROFILE
	ResourceManager::getInstance()->AddAssetToQueue(new TextureLoadingData("Assets\\Images\\slider.png", "slider", glm::vec2(0, 650)));
	ResourceManager::getInstance()->AddAssetToQueue(new TextureLoadingData("Assets\\Images\\sliderSelected.png", "sliderSelected", glm::vec2(0, 650)));
	ResourceManager::getInstance()->AddAssetToQueue(new TextureLoadingData("Assets\\Images\\cellFull.png", "cellFull", glm::vec2(0, 650)));
	ResourceManager::getInstance()->AddAssetToQueue(new TextureLoadingData("Assets\\Images\\cellEmpty.png", "cellEmpty", glm::vec2(0, 650)));
	ResourceManager::getInstance()->AddAssetToQueue(new TextureLoadingData("Assets\\Images\\cellHighlight.png", "cellHighlight", glm::vec2(0, 650)));
	ResourceManager::getInstance()->AddAssetToQueue(new TextureLoadingData("Assets\\Images\\menuContainer.png", "menuContainer", glm::vec2(0, 650)));
	ResourceManager::getInstance()->AddAssetToQueue(new TextureLoadingData("Assets\\Images\\10Kills.png ", "10Kills", glm::vec2(0, 650)));
	ResourceManager::getInstance()->AddAssetToQueue(new TextureLoadingData("Assets\\Images\\100Kills.png ", "100Kills", glm::vec2(0, 650)));
	ResourceManager::getInstance()->AddAssetToQueue(new TextureLoadingData("Assets\\Images\\1KKills.png ", "1KKills", glm::vec2(0, 650)));
	ResourceManager::getInstance()->AddAssetToQueue(new TextureLoadingData("Assets\\Images\\1MKills.png ", "1MKills", glm::vec2(0, 650)));
	ResourceManager::getInstance()->AddAssetToQueue(new TextureLoadingData("Assets\\Images\\10KillsDone.png ", "10KillsDone", glm::vec2(0, 650)));
	ResourceManager::getInstance()->AddAssetToQueue(new TextureLoadingData("Assets\\Images\\100KillsDone.png ", "100KillsDone", glm::vec2(0, 650)));
	ResourceManager::getInstance()->AddAssetToQueue(new TextureLoadingData("Assets\\Images\\1KKillsDone.png ", "1KKilsDone", glm::vec2(0, 650)));
	ResourceManager::getInstance()->AddAssetToQueue(new TextureLoadingData("Assets\\Images\\1MKillsDone.png ", "1MKillsDone", glm::vec2(0, 650)));
	ResourceManager::getInstance()->AddAssetToQueue(new TextureLoadingData("Assets\\Images\\profileBG.png ", "profileBG", glm::vec2(0, 650)));
	ResourceManager::getInstance()->AddAssetToQueue(new TextData("shield", "shield", 20, glm::vec2(805, 30), glm::vec4(0, 150, 245, 255)));
	ResourceManager::getInstance()->AddAssetToQueue(new TextData("armor", "armor", 20, glm::vec2(805, 90), glm::vec4(0, 150, 245, 255)));
	ResourceManager::getInstance()->AddAssetToQueue(new TextData("hull", "hull", 20, glm::vec2(805, 150), glm::vec4(0, 150, 245, 255)));
	ResourceManager::getInstance()->AddAssetToQueue(new TextData("short atk", "short", 20, glm::vec2(805, 210), glm::vec4(0, 150, 245, 255)));
	ResourceManager::getInstance()->AddAssetToQueue(new TextData("long atk", "long", 20, glm::vec2(805, 270), glm::vec4(0, 150, 245, 255)));
	ResourceManager::getInstance()->AddAssetToQueue(new TextData("Engine", "ult", 20, glm::vec2(805, 320), glm::vec4(0, 150, 245, 255)));
	ResourceManager::getInstance()->AddAssetToQueue(new TextData("back", "back", 20, glm::vec2(760, 650), glm::vec4(0, 150, 245, 255)));
	ResourceManager::getInstance()->AddAssetToQueue(new TextData("next", "next", 20, glm::vec2(1020, 650), glm::vec4(0, 150, 245, 255)));
	ResourceManager::getInstance()->AddAssetToQueue(new TextData("current level : " + to_string(Profile::GetInstance()->GetLevel()), "level", 20, glm::vec2(0, 0), glm::vec4(0, 150, 245, 255)));
	ResourceManager::getInstance()->AddAssetToQueue(new TextData("Power Points: " + to_string(Profile::GetInstance()->GetPowerPoints()), "powerPoints", 20, glm::vec2(0, 30), glm::vec4(0, 150, 245, 255)));
	ResourceManager::getInstance()->AddAssetToQueue(new TextureLoadingData("Assets\\Images\\button.png ", "bnext", glm::vec2(730, 630)));
	ResourceManager::getInstance()->AddAssetToQueue(new TextureLoadingData("Assets\\Images\\button.png ", "bback", glm::vec2(990, 630)));
	//GAME OVER
	ResourceManager::getInstance()->AddAssetToQueue(new TextureLoadingData("Assets\\Images\\button.bmp", "ReturnButtonGO", glm::vec2(400, 300)));
	ResourceManager::getInstance()->AddAssetToQueue(new TextureLoadingData("Assets\\Images\\button.bmp", "QuitButtonGO", glm::vec2(400, 500)));

	ResourceManager::getInstance()->AddAssetToQueue(new TextData("main menu", "ReturnTextGO", 40, glm::vec2(435, 325), glm::vec4(100, 100, 100, 255)));
	ResourceManager::getInstance()->AddAssetToQueue(new TextData("quit", "QuitTextGO", 40, glm::vec2(475, 525), glm::vec4(100, 100, 100, 255)));

	ResourceManager::getInstance()->AddAssetToQueue(new TextData("game over", "GameOverTitle", 40, glm::vec2(425, 50), glm::vec4(100, 100, 100, 255)));
	ResourceManager::getInstance()->AddAssetToQueue(new TextData("you have lost", "GameOverText", 40, glm::vec2(380, 200), glm::vec4(100, 100, 100, 255)));

	//load mesh textures for opengl
	ResourceManager::getInstance()->AddAssetToQueue(new TextureMeshData("Assets\\Images\\container.png", "container"));
	ResourceManager::getInstance()->AddAssetToQueue(new TextureMeshData("Assets\\Images\\leftRight.jpg", "leftRight"));
	ResourceManager::getInstance()->AddAssetToQueue(new TextureMeshData("Assets\\Images\\upDown.jpg", "upDown"));
	ResourceManager::getInstance()->AddAssetToQueue(new TextureMeshData("Assets\\Images\\turndown.jpg", "turndown"));
	ResourceManager::getInstance()->AddAssetToQueue(new TextureMeshData("Assets\\Images\\opUp.jpg", "opUp"));
	ResourceManager::getInstance()->AddAssetToQueue(new TextureMeshData("Assets\\Images\\turnUp.jpg", "turnUp"));
	ResourceManager::getInstance()->AddAssetToQueue(new TextureMeshData("Assets\\Images\\opDown.jpg", "opDown"));
	ResourceManager::getInstance()->loadAssetQueue();
}
#pragma endregion


bool Game::SetOpenGLAttributes() {

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 2);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 4);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
	return true;
}

void Game::SetupScenes()
{
	
}

void Game::Update(float dt) {

	
	m_sceneManager->Update(dt);
	Profile::GetInstance()->Update();
}

void Game::Render() {

	glClearColor(0.0, 0.0, 0.0, 1.0);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	m_sceneManager->Render();
	
   SDL_GL_SwapWindow(m_Window);
}

void Game::HandleEvents(float dt)
{
	m_sceneManager->HandleInput(dt);
}

bool Game::IsRunning()
{
	return m_running;
}

void Game::CleanUp()
{
	delete (m_sceneManager);
	m_sceneManager = nullptr;

	SDL_GL_DeleteContext(m_context);
	SDL_DestroyWindow(m_Window);
	SDL_DestroyRenderer(m_Renderer);
	SDL_Quit();
}

