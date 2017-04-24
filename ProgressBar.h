#pragma once
#include "SpriteRenderer.h"
#include "Camera.h"
#include "ResourceManager.h"
#include "Scene.h"
class ProgressBar
{
public:
	ProgressBar();
	ProgressBar(string name,glm::vec2 startingPosition, float shieldmax,float hullmax);
	~ProgressBar();
	void SetCurrentShieldAmount(float amount);
	void SetCurrentHullAmount(float amount);
	void Update(float dt);
	void Render(Camera * cam,SpriteRenderer * renderer,Scene * s);
private:
	float m_maxShieldAmount, m_currentShieldAmount, m_ShieldWidth, m_height, m_shieldPercentageAmount, m_maxHullAmount, m_currentHullAmount, m_HullWidth,m_hullPercentAmount;
	string m_barImageString;
	glm::vec2 m_position;
};

