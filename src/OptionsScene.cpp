#include "OptionsScene.h"

OptionsScene::OptionsScene(SDL_Renderer* m_renderer, ISoundEngine * sound) : Scene("Options",sound)
{
	GetTextures();
	sdl_renderer = m_renderer;
}

OptionsScene::~OptionsScene()
{

}

void OptionsScene::Start()
{
	if (m_inputManager->IsControllerConnected())
	{
		highlightTexr.x = 35;
		highlightTexr.w = 400;
		highlightTexr.h = 135;
		selectedOption = 1;
		BindKeys();
		SetHighlight();
	}
}

void OptionsScene::Stop()
{
	m_inputManager->EmptyKeys();
}

void OptionsScene::Update(float dt)
{
	m_inputManager->ProcessInput();
}

void OptionsScene::BindKeys()
{
	Command* select = new SpaceCommand(std::bind(&OptionsScene::SelectKey, this), Press);
	m_inputManager->AddKey(Event::BUTTON_A, select, this);

	Command* up = new SpaceCommand(std::bind(&OptionsScene::ScrollUp, this), Press);
	m_inputManager->AddKey(Event::BUTTON_DPAD_UP, up, this);

	Command* down = new SpaceCommand(std::bind(&OptionsScene::ScrollDown, this), Press);
	m_inputManager->AddKey(Event::BUTTON_DPAD_DOWN, down, this);

	Command* back = new SpaceCommand(std::bind(&OptionsScene::Return, this), Press);
	m_inputManager->AddKey(Event::BUTTON_B, back, this);
}

void OptionsScene::Return()
{
	this->GoToScene("Menu");
}

void OptionsScene::SelectKey()
{
	if (selectedOption == 1)
	{
		//this->SetDead("Game");
	}
	else if (selectedOption == 2)
	{
		//this->SetDead("MultiPlayer");
	}
	else if (selectedOption == 3)
	{
		this->GoToScene("Menu");
	}
}

void OptionsScene::GetTextures()
{
	background =  ResourceManager::getInstance()->getInstance()->GetTexture("MenuBackground");
	texr =  ResourceManager::getInstance()->getInstance()->GetTextureRect("MenuBackground");

	returnButton =  ResourceManager::getInstance()->getInstance()->GetTexture("ReturnButton");
	returnTexr =  ResourceManager::getInstance()->getInstance()->GetTextureRect("ReturnButton");

	buttonAudio =  ResourceManager::getInstance()->getInstance()->GetTexture("AudioOptButton");
	AudioTexr =  ResourceManager::getInstance()->GetTextureRect("AudioOptButton");

	buttonGraphics =  ResourceManager::getInstance()->GetTexture("GraphicsOptButton");
	GraphicsTexr =  ResourceManager::getInstance()->GetTextureRect("GraphicsOptButton");

	buttonGame =  ResourceManager::getInstance()->GetTexture("GameOptButton");
	GameTexr =  ResourceManager::getInstance()->GetTextureRect("GameOptButton");

	optionsTitle =  ResourceManager::getInstance()->GetText("OptionsTitle");
	optionsTitlePos =  ResourceManager::getInstance()->GetTextRect("OptionsTitle");

	audio =  ResourceManager::getInstance()->GetText("AudioOptText");
	audioOptPos =  ResourceManager::getInstance()->GetTextRect("AudioOptText");

	graphics =  ResourceManager::getInstance()->GetText("GraphicsOptText");
	graphicsOptPos =  ResourceManager::getInstance()->GetTextRect("GraphicsOptText");

	game =  ResourceManager::getInstance()->GetText("GameOptText");
	gameOptPos =  ResourceManager::getInstance()->GetTextRect("GameOptText");

	//highlightTex = ResourceManager::getInstance()->GetTexture("highlight");
}

void OptionsScene::Render()
{
	SDL_RenderClear(sdl_renderer);

	SDL_RenderCopy(sdl_renderer, background, NULL, &texr);
	//SDL_RenderCopy(sdl_renderer, highlightTex, NULL, &highlightTexr);
	//SDL_RenderCopy(sdl_renderer, returnButton, NULL, &returnTexr);
	SDL_RenderCopy(sdl_renderer, buttonAudio, NULL, &AudioTexr);
	SDL_RenderCopy(sdl_renderer, buttonGraphics, NULL, &GraphicsTexr);
	SDL_RenderCopy(sdl_renderer, buttonGame, NULL, &GameTexr);
	//SDL_RenderCopy(sdl_renderer, optionsTitle, NULL, &optionsTitlePos);

	SDL_RenderCopy(sdl_renderer, audio, NULL, &audioOptPos);
	SDL_RenderCopy(sdl_renderer, graphics, NULL, &graphicsOptPos);
	SDL_RenderCopy(sdl_renderer, game, NULL, &gameOptPos);
	SDL_RenderPresent(sdl_renderer);
}

void OptionsScene::ScrollUp()
{
	if (selectedOption >= 2)
	{
		selectedOption -= 1;
	}
	else if (selectedOption == 1)
	{
		selectedOption = 3;
	}
	SetHighlight();
}

void OptionsScene::SetHighlight()
{
	if (selectedOption == 1)
	{
		buttonAudio = ResourceManager::getInstance()->GetTexture("highlight");
		buttonGraphics = ResourceManager::getInstance()->GetTexture("OptButton");
		buttonGame = ResourceManager::getInstance()->GetTexture("QuitButton");
	}
	else if (selectedOption == 2)
	{
		buttonAudio = ResourceManager::getInstance()->GetTexture("PlayButton");
		buttonGraphics = ResourceManager::getInstance()->GetTexture("highlight");
		buttonGame = ResourceManager::getInstance()->GetTexture("QuitButton");
	}
	else if (selectedOption == 3)
	{
		buttonAudio = ResourceManager::getInstance()->GetTexture("PlayButton");
		buttonGraphics = ResourceManager::getInstance()->GetTexture("OptButton");
		buttonGame = ResourceManager::getInstance()->GetTexture("highlight");
	}
}

void OptionsScene::ScrollDown()
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

void OptionsScene::HandleInput(float dt)
{
	m_inputManager->ProcessInput();
}
