#pragma once
#include "glm\glm.hpp"
#include <vector>
#include "Model.h"
#include "Polygon.h"
#include "Camera.h"
#include "Line.h"
#include <time.h>
#include "Circle.h"
#include "Profile.h"
#include "Scene.h"
#include "SpriteRenderer.h"
#include "FLInputManager.h"

enum STATE {NEW,IS_CREATING,CAN_FIGHT,IS_EXPLORED};
class Node : public EventListener
{
public:
	Node(int key,glm::vec3 startingPosition,Scene *);
	Node();
	void Start();
	~Node();
	void Update(float dt, Scene * scene);
	void PrintInfo(SpriteRenderer * spriteRenderer);
	void CreateChildren();
	void Render(Camera * cam,SpriteRenderer * spriteRenderer);
	glm::vec3 GetPosition();
	STATE GetState();
	void SelectFight();
	void SetState(STATE state);
	void SetLineColor(glm::vec4 color);
	void SetPointerCollision(Circle *pointerBounds);
	
	void SelectKey();
private:
	glm::vec3 m_position;
	std::vector<Node *> children;
	Model* model;
	Polygon * m_bounds;
	glm::vec4 m_lineColor;
	int m_key;
	STATE m_currentState;
	int m_minSpawnDistance = 100, m_maxSpawnDistance = 500;
	int m_minAngle = 20, m_maxAngle = 340, m_maxCreationAmount = 3;
	std::vector<Line*> m_conectionLines;
	Circle* m_pointerBounds;
	Circle* m_currentBounds;
	bool m_isSelected = false;
	int m_hostileAmount = 0;
	int m_level;
	int m_enemyCount;
	Scene * s;
	InputManager * m_inputManager;
	bool m_fightEnemies = false;
	float m_rotation = 0;
};

