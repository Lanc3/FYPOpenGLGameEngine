#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <GL\glew.h>
#include <iostream>

#include "SceneManager.h"
#include "ResourceManager.h"
#include "Shader.h"
#include "SDL_thread.h"
#include "SDL.h"
#include <thread>
#include "irrKlang.h"

using namespace irrklang;
using namespace std;

class Game
{
public:
	Game();
	~Game();
	bool Initialize();
	void LoadResources();

	void Update(float dt);
	void HandleEvents(float dt);
	void Render();
	bool IsRunning();
	void CleanUp();
private:
	void SetupScenes();

	bool SetOpenGLAttributes();
	SDL_GLContext m_context;
	bool m_running;

	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
	SDL_Surface* m_Surface;
	ResourceManager m_recMan;
	SceneManager* m_sceneManager;
	//The thread that will be used
	SDL_Thread *thread = NULL;
	bool firstPass = true;
	//Quit flag
	bool quit = false;
	ISoundEngine *SoundEngine;
};
#endif

