#include "ProfileScene.h"
ProfileScene::ProfileScene(SDL_Renderer* m_renderer, ISoundEngine * sound) : Scene("Profile",sound)
{
	GetTextures();
	sdl_renderer = m_renderer;
	m_SheildSlider = slider(400, 30, 800, 50, Profile::getInstance()->GetShieldAmount());
	m_ArmorSlider = slider(400, 30, 800, 110, Profile::getInstance()->GetArmorAmount());
	m_HullSlider = slider(400, 30, 800, 170, Profile::getInstance()->GetHullAmount());
	m_ShortDMGSlider = slider(400, 30, 800, 230, Profile::getInstance()->GetShortAmount());
	m_LongDMGSlider = slider(400, 30, 800, 290, Profile::getInstance()->GetLongAmopunt());
	m_ULTSlider = slider(400, 30, 800, 350, Profile::getInstance()->GetUltAmount());

	m_powerPointsToSpend = Profile::getInstance()->GetPowerPoints();

	m_container = ResourceManager::getInstance()->GetTexture("menuContainer");
	m_containerRect.w = 450;
	m_containerRect.h = 400;
	m_containerRect.x = 775;
	m_containerRect.y = 10;

	m_achievementContainer = ResourceManager::getInstance()->GetTexture("menuContainer");
	m_achievementContainerRect.w = 450;
	m_achievementContainerRect.h = 200;
	m_achievementContainerRect.x = 20;
	m_achievementContainerRect.y = 500;


	m_tenRect.h = 80;
	m_tenRect.w = 80;
	m_tenRect.x = 45;
	m_tenRect.y = 525;

	m_hundredRect.h = 80;
	m_hundredRect.w = 80;
	m_hundredRect.x = 145;
	m_hundredRect.y = 525;

	m_thousandRect.h = 80;
	m_thousandRect.w = 80;
	m_thousandRect.x = 245;
	m_thousandRect.y = 525;

	m_millionRect.h = 80;
	m_millionRect.w = 80;
	m_millionRect.x = 45;
	m_millionRect.y = 615;

	m_levelRect.h = 80;
	m_levelRect.w = 80;
	m_levelRect.x = 145;
	m_levelRect.y = 615;
}

ProfileScene::~ProfileScene()
{

}

void ProfileScene::Start()
{
	m_SheildSlider = slider(400, 30, 800, 50, Profile::getInstance()->GetShieldAmount());
	m_ArmorSlider = slider(400, 30, 800, 110, Profile::getInstance()->GetArmorAmount());
	m_HullSlider = slider(400, 30, 800, 170, Profile::getInstance()->GetHullAmount());
	m_ShortDMGSlider = slider(400, 30, 800, 230, Profile::getInstance()->GetShortAmount());
	m_LongDMGSlider = slider(400, 30, 800, 290, Profile::getInstance()->GetLongAmopunt());
	m_ULTSlider = slider(400, 30, 800, 350, Profile::getInstance()->GetUltAmount());

	m_powerPointsToSpend = Profile::getInstance()->GetPowerPoints();

	m_alive = true;
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

void ProfileScene::Stop()
{
	m_inputManager->EmptyKeys();
}

void ProfileScene::BindKeys()
{
	Command* select = new SpaceCommand(std::bind(&ProfileScene::SelectKey, this), Press);
	m_inputManager->AddKey(Event::BUTTON_A, select, this);

	Command* up = new SpaceCommand(std::bind(&ProfileScene::ScrollUp, this), Press);
	m_inputManager->AddKey(Event::BUTTON_DPAD_UP, up, this);

	Command* down = new SpaceCommand(std::bind(&ProfileScene::ScrollDown, this), Press);
	m_inputManager->AddKey(Event::BUTTON_DPAD_DOWN, down, this);

	Command* left = new SpaceCommand(std::bind(&ProfileScene::Left, this), Press);
	m_inputManager->AddKey(EventListener::Event::BUTTON_DPAD_LEFT, left, this);

	Command* right = new SpaceCommand(std::bind(&ProfileScene::Right, this), Press);
	m_inputManager->AddKey(Event::BUTTON_DPAD_RIGHT, right, this);
}

void ProfileScene::Update(float dt)
{
	m_bgmMenu->setIsPaused(false);
}
void ProfileScene::Left()
{
	if (selectedOption == 1)
	{
		if (m_powerPointsToSpend < Profile::getInstance()->GetPowerPoints() && m_SheildSlider.GetHighlightedAmount() > 0)
		{
			m_SheildSlider.Left();
			m_powerPointsToSpend++;
		}
	}
	else if (selectedOption == 2)
	{
		if (m_powerPointsToSpend < Profile::getInstance()->GetPowerPoints() && m_ArmorSlider.GetHighlightedAmount() > 0)
		{
			m_ArmorSlider.Left();
			m_powerPointsToSpend++;
		}
	}
	else if (selectedOption == 3)
	{
		if (m_powerPointsToSpend < Profile::getInstance()->GetPowerPoints() && m_HullSlider.GetHighlightedAmount() > 0)
		{
			m_HullSlider.Left();
			m_powerPointsToSpend++;
		}
	}
	else if (selectedOption == 4)
	{
		if (m_powerPointsToSpend < Profile::getInstance()->GetPowerPoints() && m_ShortDMGSlider.GetHighlightedAmount() > 0)
		{
			m_ShortDMGSlider.Left();
			m_powerPointsToSpend++;
		}
	}
	else if (selectedOption == 5)
	{
		if (m_powerPointsToSpend < Profile::getInstance()->GetPowerPoints() && m_LongDMGSlider.GetHighlightedAmount() > 0)
		{
			m_LongDMGSlider.Left();
			m_powerPointsToSpend++;
		}
	}
	else if (selectedOption == 6)
	{
		if (m_powerPointsToSpend < Profile::getInstance()->GetPowerPoints() && m_ULTSlider.GetHighlightedAmount() > 0)
		{
			m_ULTSlider.Left();
			m_powerPointsToSpend++;
		}
	}
}
void ProfileScene::Right()
{
	if (selectedOption == 1)
	{
		if (m_powerPointsToSpend > 0)
		{
			m_SheildSlider.Right();
			m_powerPointsToSpend--;
		}
	}
	else if (selectedOption == 2)
	{
		if (m_powerPointsToSpend > 0)
		{
			m_ArmorSlider.Right();
			m_powerPointsToSpend--;
		}
	}
	else if (selectedOption == 3)
	{
		if (m_powerPointsToSpend > 0)
		{
			m_HullSlider.Right();
			m_powerPointsToSpend--;
		}
	}
	else if (selectedOption == 4)
	{
		if (m_powerPointsToSpend > 0)
		{
			m_ShortDMGSlider.Right();
			m_powerPointsToSpend--;
		}
	}
	else if (selectedOption == 5)
	{
		if (m_powerPointsToSpend > 0)
		{
			m_LongDMGSlider.Right();
			m_powerPointsToSpend--;
		}
	}
	else if (selectedOption == 6)
	{
		if (m_powerPointsToSpend > 0)
		{
			m_ULTSlider.Right();
			m_powerPointsToSpend--;
		}
	}
}
void ProfileScene::ScrollUp()
{
	if (selectedOption >= 2)
	{
		selectedOption -= 1;
	}
	else if (selectedOption == 1)
	{
		selectedOption = 8;
	}
	SetHighlight();
}

void ProfileScene::SetHighlight()
{
	if (selectedOption == 1)
	{
		m_SheildSlider.isSelected = true;
		m_ArmorSlider.isSelected = false;
		m_HullSlider.isSelected = false;
		m_ShortDMGSlider.isSelected = false;
		m_LongDMGSlider.isSelected = false;
		m_ULTSlider.isSelected = false;
		buttonPlay = ResourceManager::getInstance()->GetTexture("bback");
		buttonOpt = ResourceManager::getInstance()->GetTexture("bnext");
	}
	else if (selectedOption == 2)
	{
		m_SheildSlider.isSelected = false;
		m_ArmorSlider.isSelected = true;
		m_HullSlider.isSelected = false;
		m_ShortDMGSlider.isSelected = false;
		m_LongDMGSlider.isSelected = false;
		m_ULTSlider.isSelected = false;
		buttonPlay = ResourceManager::getInstance()->GetTexture("bback");
		buttonOpt = ResourceManager::getInstance()->GetTexture("bnext");
	}
	else if (selectedOption == 3)
	{
		m_SheildSlider.isSelected = false;
		m_ArmorSlider.isSelected = false;
		m_HullSlider.isSelected = true;
		m_ShortDMGSlider.isSelected = false;
		m_LongDMGSlider.isSelected = false;
		m_ULTSlider.isSelected = false;
		buttonPlay = ResourceManager::getInstance()->GetTexture("bback");
		buttonOpt = ResourceManager::getInstance()->GetTexture("bnext");
	}
	else if (selectedOption == 4)
	{
		m_SheildSlider.isSelected = false;
		m_ArmorSlider.isSelected = false;
		m_HullSlider.isSelected = false;
		m_ShortDMGSlider.isSelected = true;
		m_LongDMGSlider.isSelected = false;
		m_ULTSlider.isSelected = false;
		buttonPlay = ResourceManager::getInstance()->GetTexture("bback");
		buttonOpt = ResourceManager::getInstance()->GetTexture("bnext");
	}
	else if (selectedOption == 5)
	{
		m_SheildSlider.isSelected = false;
		m_ArmorSlider.isSelected = false;
		m_HullSlider.isSelected = false;
		m_ShortDMGSlider.isSelected = false;
		m_LongDMGSlider.isSelected = true;
		m_ULTSlider.isSelected = false;
		buttonPlay = ResourceManager::getInstance()->GetTexture("bback");
		buttonOpt = ResourceManager::getInstance()->GetTexture("bnext");
	}
	else if (selectedOption == 6)
	{
		m_SheildSlider.isSelected = false;
		m_ArmorSlider.isSelected = false;
		m_HullSlider.isSelected = false;
		m_ShortDMGSlider.isSelected = false;
		m_LongDMGSlider.isSelected = false;
		m_ULTSlider.isSelected = true;
		buttonPlay = ResourceManager::getInstance()->GetTexture("bback");
		buttonOpt = ResourceManager::getInstance()->GetTexture("bnext");
	}

	else if (selectedOption == 7)
	{
		m_SheildSlider.isSelected = false;
		m_ArmorSlider.isSelected = false;
		m_HullSlider.isSelected = false;
		m_ShortDMGSlider.isSelected = false;
		m_LongDMGSlider.isSelected = false;
		m_ULTSlider.isSelected = false;
		buttonPlay = ResourceManager::getInstance()->GetTexture("highlight");
		buttonOpt = ResourceManager::getInstance()->GetTexture("bnext");
	}
	else if (selectedOption == 8)
	{
		m_SheildSlider.isSelected = false;
		m_ArmorSlider.isSelected = false;
		m_HullSlider.isSelected = false;
		m_ShortDMGSlider.isSelected = false;
		m_LongDMGSlider.isSelected = false;
		m_ULTSlider.isSelected = false;
		buttonPlay = ResourceManager::getInstance()->GetTexture("bback");
		buttonOpt = ResourceManager::getInstance()->GetTexture("highlight");
	}
}

void ProfileScene::ScrollDown()
{
	if (selectedOption < 8)
	{
		selectedOption += 1;
	}
	else if (selectedOption == 8)
	{
		selectedOption = 1;
	}
	SetHighlight();
}

void ProfileScene::SelectKey()
{
	if (selectedOption == 7)
	{
		m_bgmMenu->stop();
		this->GoToScene("Menu");
	}
	else if (selectedOption == 8)
	{
		Profile::getInstance()->SetPPAmount(m_powerPointsToSpend);
		Profile::getInstance()->Save();
		m_bgmMenu->stop();
		this->GoToScene("System");
	}
	else if (selectedOption == 1)
	{
		Profile::getInstance()->SetPPAmount(m_powerPointsToSpend);
		Profile::getInstance()->SetShieldAmount(m_SheildSlider.GetTotal());
		Profile::getInstance()->Save();
	}
	else if (selectedOption == 2)
	{
		Profile::getInstance()->SetPPAmount(m_powerPointsToSpend);
		Profile::getInstance()->SetArmorAmount(m_ArmorSlider.GetTotal());
		Profile::getInstance()->Save();
	}
	else if (selectedOption == 3)
	{
		Profile::getInstance()->SetPPAmount(m_powerPointsToSpend);
		Profile::getInstance()->SetHullAmount(m_HullSlider.GetTotal());
		Profile::getInstance()->Save();
	}
	else if (selectedOption == 4)
	{
		Profile::getInstance()->SetPPAmount(m_powerPointsToSpend);
		Profile::getInstance()->SetShortAmount(m_ShortDMGSlider.GetTotal());
		Profile::getInstance()->Save();
	}
	else if (selectedOption == 5)
	{
		Profile::getInstance()->SetPPAmount(m_powerPointsToSpend);
		Profile::getInstance()->SetLongAmopunt(m_LongDMGSlider.GetTotal());
		Profile::getInstance()->Save();
	}
	else if (selectedOption == 6)
	{
		Profile::getInstance()->SetPPAmount(m_powerPointsToSpend);
		Profile::getInstance()->SetEngineSpeedAmount(m_ULTSlider.GetTotal());
		Profile::getInstance()->Save();
	}
}

void ProfileScene::GetTextures()
{
	img = ResourceManager::getInstance()->GetTexture("profileBG");
	texr = ResourceManager::getInstance()->GetTextureRect("MenuBackground");

	buttonPlay = ResourceManager::getInstance()->GetTexture("bnext");
	PlayTexr = ResourceManager::getInstance()->GetTextureRect("bnext");

	buttonOpt = ResourceManager::getInstance()->GetTexture("bback");
	OptionsTexr = ResourceManager::getInstance()->GetTextureRect("bback");

	play = ResourceManager::getInstance()->GetText("PlayText");
	playPos = ResourceManager::getInstance()->GetTextRect("PlayText");

	multi = ResourceManager::getInstance()->GetText("MPText");
	multiPos = ResourceManager::getInstance()->GetTextRect("MPText");

	next = ResourceManager::getInstance()->GetText("next");
	nextPos = ResourceManager::getInstance()->GetTextRect("next");

	back = ResourceManager::getInstance()->GetText("back");
	backPos = ResourceManager::getInstance()->GetTextRect("back");

	//highlightTex = ResourceManager::getInstance()->GetTexture("highlight");

}

void ProfileScene::Render()
{
	SDL_RenderClear(sdl_renderer);
	SDL_Rect bgRect;
	bgRect.x = 0;
	bgRect.y = 0;
	bgRect.w = 1280;
	bgRect.h = 720;
	SDL_RenderCopy(sdl_renderer, img, NULL, &bgRect);
	SDL_RenderCopy(sdl_renderer, m_container, NULL, &m_containerRect);
	SDL_RenderCopy(sdl_renderer, m_achievementContainer, NULL, &m_achievementContainerRect);
	SDL_RenderCopy(sdl_renderer, ResourceManager::getInstance()->GetText("level"), NULL, &ResourceManager::getInstance()->GetTextRect("level"));
	SDL_RenderCopy(sdl_renderer, ResourceManager::getInstance()->GetText("powerPoints"), NULL, &ResourceManager::getInstance()->GetTextRect("powerPoints"));

	SDL_RenderCopy(sdl_renderer, ResourceManager::getInstance()->GetText("shield"), NULL, &ResourceManager::getInstance()->GetTextRect("shield"));
	SDL_RenderCopy(sdl_renderer, ResourceManager::getInstance()->GetText("armor"), NULL, &ResourceManager::getInstance()->GetTextRect("armor"));
	SDL_RenderCopy(sdl_renderer, ResourceManager::getInstance()->GetText("hull"), NULL, &ResourceManager::getInstance()->GetTextRect("hull"));
	SDL_RenderCopy(sdl_renderer, ResourceManager::getInstance()->GetText("short"), NULL, &ResourceManager::getInstance()->GetTextRect("short"));
	SDL_RenderCopy(sdl_renderer, ResourceManager::getInstance()->GetText("long"), NULL, &ResourceManager::getInstance()->GetTextRect("long"));
	SDL_RenderCopy(sdl_renderer, ResourceManager::getInstance()->GetText("ult"), NULL, &ResourceManager::getInstance()->GetTextRect("ult"));


	SDL_RenderCopy(sdl_renderer, buttonPlay, NULL, &PlayTexr);

	SDL_RenderCopy(sdl_renderer, buttonOpt, NULL, &OptionsTexr);

	SDL_RenderCopy(sdl_renderer, play, NULL, &playPos);
	SDL_RenderCopy(sdl_renderer, next, NULL, &nextPos);
	SDL_RenderCopy(sdl_renderer, back, NULL, &backPos);
	
	m_SheildSlider.Render(sdl_renderer);
	m_ArmorSlider.Render(sdl_renderer);
	m_HullSlider.Render(sdl_renderer);
	m_ShortDMGSlider.Render(sdl_renderer);
	m_LongDMGSlider.Render(sdl_renderer);
	m_ULTSlider.Render(sdl_renderer);
	
	//achievement draws

	if (Profile::getInstance()->GetAchievements("10Kills"))
	{
		SDL_RenderCopy(sdl_renderer, ResourceManager::getInstance()->GetTexture("10KillsDone"), NULL, &m_tenRect);
	}
	else
	{
		SDL_RenderCopy(sdl_renderer, ResourceManager::getInstance()->GetTexture("10Kills"), NULL, &m_tenRect);
	}
	if (Profile::getInstance()->GetAchievements("100Kills"))
	{
		SDL_RenderCopy(sdl_renderer, ResourceManager::getInstance()->GetTexture("100KillsDone"), NULL, &m_hundredRect);
	}
	else
	{
		SDL_RenderCopy(sdl_renderer, ResourceManager::getInstance()->GetTexture("100Kills"), NULL, &m_hundredRect);
	}
	if (Profile::getInstance()->GetAchievements("1KKills"))
	{
		SDL_RenderCopy(sdl_renderer, ResourceManager::getInstance()->GetTexture("1KKillsDone"), NULL, &m_thousandRect);
	}
	else
	{
		SDL_RenderCopy(sdl_renderer, ResourceManager::getInstance()->GetTexture("1KKills"), NULL, &m_thousandRect);
	}
	if (Profile::getInstance()->GetAchievements("1MKills"))
	{
		SDL_RenderCopy(sdl_renderer, ResourceManager::getInstance()->GetTexture("1MKillsDone"), NULL, &m_millionRect);
	}
	else
	{
		SDL_RenderCopy(sdl_renderer, ResourceManager::getInstance()->GetTexture("1MKills"), NULL, &m_millionRect);
	}
	if (Profile::getInstance()->GetAchievements("10Kills"))
	{
		SDL_RenderCopy(sdl_renderer, ResourceManager::getInstance()->GetTexture("10KillsDone"), NULL, &m_levelRect);
	}
	else
	{
		SDL_RenderCopy(sdl_renderer, ResourceManager::getInstance()->GetTexture("10Kills"), NULL, &m_levelRect);
	}
	RenderText("Universe View ", 720, 630, 0.65f, glm::vec3(0, 155, 254));
	RenderText("Universe View ", 720, 630, 0.65f, glm::vec3(0, 155, 254));
	RenderText("Universe View ", 720, 630, 0.65f, glm::vec3(0, 155, 254));
	RenderText("Universe View ", 720, 630, 0.65f, glm::vec3(0, 155, 254));
	SDL_RenderPresent(sdl_renderer);
	RenderText("Universe View ", 720, 630, 0.65f, glm::vec3(0, 155, 254));
	RenderText("Universe View ", 720, 630, 0.65f, glm::vec3(0, 155, 254));
	RenderText("Universe View ", 720, 630, 0.65f, glm::vec3(0, 155, 254));
	RenderText("Universe View ", 720, 630, 0.65f, glm::vec3(0, 155, 254));


}

void ProfileScene::HandleInput(float dt)
{
	m_inputManager->ProcessInput();
}


