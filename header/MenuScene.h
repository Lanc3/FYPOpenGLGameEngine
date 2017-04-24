#pragma once

#include "Scene.h"
#include "SDL_ttf.h"
#include "ResourceManager.h"
#include "Quad.h"
#include "SceneManager.h"

class MenuScene : public Scene 
{
public:
	MenuScene(SDL_Renderer * m_renderer, SDL_Window* window, ISoundEngine * sound);
	~MenuScene();

	void Update(float dt);
	void Render();
	void HandleInput(float dt);

	void Start();
	void Stop();

private:
	ISound* m_bgmMenu;

	SDL_Texture* menuTitle;
	SDL_Texture* play;
	SDL_Texture* options;
	SDL_Texture* quit;
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
	SDL_Rect optionPos;
	SDL_Rect quitPos;
	SDL_Rect multiPos;

	SDL_Renderer* sdl_renderer;
	SDL_Window* window;
	int selectedOption; 
	void BindKeys();
	void ScrollUp();
	void SetHighlight();
	void ScrollDown();
	void SelectKey();
	void GetTextures();

};
