#include "MenuScene.h"

MenuScene::MenuScene(SDL_Renderer* m_renderer, SDL_Window* _window,ISoundEngine * sound) : Scene("Menu",sound)
{
	GetTextures();
	sdl_renderer = m_renderer;
	window = _window;
}

MenuScene::~MenuScene()
{

}

void MenuScene::Start()
{
	m_bgmMenu = m_soundEngine->play2D("Assets\\audio\\music1.wav", GL_TRUE, GL_TRUE);
	m_bgmMenu->setVolume(0.3);

	if (m_inputManager->IsControllerConnected())
	{
		selectedOption = 1;
		BindKeys();
		highlightTexr.x = 350;
		highlightTexr.w = 400;
		highlightTexr.h = 120;
		SetHighlight();
	}
}

void MenuScene::Stop()
{
	m_inputManager->EmptyKeys();
}

void MenuScene::BindKeys()
{
	Command* select = new SpaceCommand(std::bind(&MenuScene::SelectKey, this), Press);
	m_inputManager->AddKey(Event::BUTTON_A, select, this);

	Command* up = new SpaceCommand(std::bind(&MenuScene::ScrollUp, this), Press);
	m_inputManager->AddKey(Event::BUTTON_DPAD_UP, up, this);

	Command* down = new SpaceCommand(std::bind(&MenuScene::ScrollDown, this), Press);
	m_inputManager->AddKey(Event::BUTTON_DPAD_DOWN, down, this);
}

void MenuScene::Update(float dt)
{
	m_bgmMenu->setIsPaused(false);
}

void MenuScene::ScrollUp()
{
	if (selectedOption >= 2)
	{
		selectedOption -= 1;
	}
	else if(selectedOption == 1)
	{
		selectedOption = 3;
	}
	SetHighlight();
}

void MenuScene::SetHighlight()
{
	if (selectedOption == 1)
	{
		buttonPlay = ResourceManager::getInstance()->GetTexture("highlight");
		buttonOpt = ResourceManager::getInstance()->GetTexture("OptButton");
		buttonQuit = ResourceManager::getInstance()->GetTexture("QuitButton");
	}
	else if (selectedOption == 2)
	{
		buttonPlay = ResourceManager::getInstance()->GetTexture("PlayButton");
		buttonOpt = ResourceManager::getInstance()->GetTexture("highlight");
		buttonQuit = ResourceManager::getInstance()->GetTexture("QuitButton");
	}
	else if (selectedOption == 3)
	{
		buttonPlay = ResourceManager::getInstance()->GetTexture("PlayButton");
		buttonOpt = ResourceManager::getInstance()->GetTexture("OptButton");
		buttonQuit = ResourceManager::getInstance()->GetTexture("highlight");
	}
}

void MenuScene::ScrollDown()
{
	if (selectedOption < 3)
	{
		selectedOption += 1;
	}
	else if (selectedOption == 3)
	{
		selectedOption = 1;
	}
	SetHighlight();
}

void MenuScene::SelectKey()
{
	if (selectedOption == 1)
	{
		m_bgmMenu->stop();
		this->GoToScene("Profile");
	}
	else if (selectedOption == 2)
	{
		this->GoToScene("Options");
	}
	else if (selectedOption == 3)
	{
		
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(sdl_renderer);
		SDL_Quit();
	}
}

void MenuScene::GetTextures()
{
	img = ResourceManager::getInstance()->GetTexture("MenuBackground");
	texr = ResourceManager::getInstance()->GetTextureRect("MenuBackground");

	buttonPlay = ResourceManager::getInstance()->GetTexture("PlayButton");
	PlayTexr = ResourceManager::getInstance()->GetTextureRect("PlayButton");

	//buttonMulti = ResourceManager::getInstance()->GetTexture("MPButton");
	//MultiTexr = ResourceManager::getInstance()->GetTextureRect("MPButton");

	buttonOpt = ResourceManager::getInstance()->GetTexture("OptButton");
	OptionsTexr = ResourceManager::getInstance()->GetTextureRect("OptButton");

	buttonQuit = ResourceManager::getInstance()->GetTexture("QuitButton");
	QuitTexr = ResourceManager::getInstance()->GetTextureRect("QuitButton");
	
	menuTitle = ResourceManager::getInstance()->GetText("MenuTitle");
	menuTitlePos = ResourceManager::getInstance()->GetTextRect("MenuTitle");

	play = ResourceManager::getInstance()->GetText("PlayText");
	playPos = ResourceManager::getInstance()->GetTextRect("PlayText");

	multi = ResourceManager::getInstance()->GetText("MPText");
	multiPos = ResourceManager::getInstance()->GetTextRect("MPText");

	options = ResourceManager::getInstance()->GetText("OptionsText");
	optionPos = ResourceManager::getInstance()->GetTextRect("OptionsText");

	quit = ResourceManager::getInstance()->GetText("QuitText");
	quitPos= ResourceManager::getInstance()->GetTextRect("QuitText");

	//highlightTex = ResourceManager::getInstance()->GetTexture("highlight");
	
}

void MenuScene::Render()
{
	SDL_RenderClear(sdl_renderer);
	SDL_Rect bgRect;
	bgRect.x = 0;
	bgRect.y = 0;
	bgRect.w = 1280;
	bgRect.h = 720;
	SDL_RenderCopy(sdl_renderer, img, NULL, &bgRect);
	SDL_RenderCopy(sdl_renderer, highlightTex, NULL, &highlightTexr);
	SDL_RenderCopy(sdl_renderer, buttonPlay, NULL, &PlayTexr);
	//SDL_RenderCopy(sdl_renderer, buttonMulti, NULL, &MultiTexr);
	SDL_RenderCopy(sdl_renderer, buttonOpt, NULL, &OptionsTexr);
	SDL_RenderCopy(sdl_renderer, buttonQuit, NULL, &QuitTexr);
	//SDL_RenderCopy(sdl_renderer, menuTitle, NULL, &menuTitlePos);
	
	//SDL_RenderCopy(sdl_renderer, multi, NULL, &multiPos);
	SDL_RenderCopy(sdl_renderer, play, NULL, &playPos);
	SDL_RenderCopy(sdl_renderer, options, NULL, &optionPos);
	SDL_RenderCopy(sdl_renderer, quit, NULL, &quitPos);
	SDL_RenderPresent(sdl_renderer);
}

void MenuScene::HandleInput(float dt)
{
	m_inputManager->ProcessInput();
}

