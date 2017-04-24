#pragma once

#include <iostream> 
#include <math.h>
#include "FLInputManager.h"
#include <GL/glew.h> // Contains all the necessery OpenGL includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"
#include "ResourceManager.h"
#include "irrKlang.h"

using namespace irrklang;
using namespace std;

struct Character {
	GLuint TextureID;
	glm::ivec2 Size;
	glm::ivec2 Bearing;
	GLuint Advance;
};

class Scene : public EventListener
{
public:
	Scene(string name,ISoundEngine * sound);
	~Scene();
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual void HandleInput(float dt) = 0;

	virtual void Start();
	virtual void Stop();

	void GoToScene(string name);
	void SetAlive();
	void SetDead();
	bool IsAlive();
	string CheckNext();
	string GetName();
	void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);

	std::map<GLchar, Character> setUpTextObjects();

protected:
	ISoundEngine *m_soundEngine;
	InputManager* m_inputManager;
	bool m_active;
	bool m_alive;
	string m_transition;
	string	m_name;

	Shader m_textShader;
	std::map<GLchar, Character> Characters;

	GLuint VAO;
	GLuint VBO;
};
