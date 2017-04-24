#pragma once

#include "Scene.h"
#include "SDL_ttf.h"
#include "ResourceManager.h"
#include "Quad.h"
#include "SceneManager.h"
#include "slider.h"
#include "Profile.h"
#include "math.h"
#include "glm/glm.hpp"

class ProfileScene : public Scene
{
public:
	ProfileScene(SDL_Renderer * m_renderer, ISoundEngine * sound);
	~ProfileScene();

	void Update(float dt);
	void Left();
	void Right();
	void Render();
	void HandleInput(float dt);

	void Start();
	void Stop();

private:
	ISound* m_bgmMenu;

	SDL_Texture* menuTitle;
	SDL_Texture* play;
	
	SDL_Texture* multi;

	SDL_Texture* img;
	SDL_Texture* buttonPlay;
	SDL_Texture* buttonMulti;
	SDL_Texture* buttonOpt;
	SDL_Texture* buttonQuit;
	SDL_Texture* highlightTex;

	SDL_Rect highlightTexr;
	SDL_Rect texr;
	SDL_Rect PlayTexr;
	SDL_Rect MultiTexr;
	SDL_Rect OptionsTexr;
	SDL_Rect QuitTexr;

	SDL_Rect menuTitlePos;
	SDL_Rect playPos;
	
	SDL_Rect multiPos;

	SDL_Texture* next;
	SDL_Texture* back;
	SDL_Rect nextPos;
	SDL_Rect backPos;

	SDL_Texture* m_container;
	SDL_Rect m_containerRect;

	SDL_Rect m_tenRect;
	SDL_Rect m_hundredRect;
	SDL_Rect m_thousandRect;
	SDL_Rect m_millionRect;
	SDL_Rect m_levelRect;

	SDL_Texture * m_menuContainer;
	SDL_Rect m_menuRect;

	SDL_Texture * m_achievementContainer;
	SDL_Rect m_achievementContainerRect;

	slider m_SheildSlider;
	slider m_ArmorSlider;
	slider m_HullSlider;
	slider m_ShortDMGSlider;
	slider m_LongDMGSlider;
	slider m_ULTSlider;
	SDL_Renderer* sdl_renderer;

	int selectedOption;
	void BindKeys();
	void ScrollUp();
	void SetHighlight();
	void ScrollDown();
	void SelectKey();
	void GetTextures();
	int m_powerPointsToSpend;

	
};
