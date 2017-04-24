#include "ProgressBar.h"



ProgressBar::ProgressBar()
{
}


ProgressBar::ProgressBar(string name, glm::vec2 startingPosition,float shieldMax,float hullMax)
{
	m_position = startingPosition;
	m_maxShieldAmount = shieldMax;
	m_maxHullAmount = hullMax;
	m_currentShieldAmount = shieldMax;
	m_currentHullAmount = hullMax;
	m_ShieldWidth = 350;
	m_HullWidth = 350;
	m_shieldPercentageAmount = m_maxShieldAmount / m_currentShieldAmount;
	m_hullPercentAmount = m_maxHullAmount / m_currentHullAmount;
}

ProgressBar::~ProgressBar()
{
}

void ProgressBar::SetCurrentShieldAmount(float amount)
{
	m_currentShieldAmount = amount;
}
void ProgressBar::SetCurrentHullAmount(float amount)
{
	m_currentHullAmount = amount;
}

void ProgressBar::Update(float dt)
{
	m_shieldPercentageAmount = m_maxShieldAmount / m_currentShieldAmount;
	m_hullPercentAmount = m_maxHullAmount / m_currentHullAmount;
}

void ProgressBar::Render(Camera * cam, SpriteRenderer * renderer, Scene * s)
{
	renderer->DrawSprite(ResourceManager::getInstance()->GetSprite("systemContainer"),
		m_position, glm::vec2(370, 80), 0, glm::vec3(1.0f, 1.0f, 1.0f));
	renderer->DrawSprite(ResourceManager::getInstance()->GetSprite("cellHighlight"),
		m_position+ glm::vec2(10, 10), glm::vec2(m_ShieldWidth *m_shieldPercentageAmount, 20), 0, glm::vec3(0, 150, 254));
	renderer->DrawSprite(ResourceManager::getInstance()->GetSprite("cellFull"),
		m_position + glm::vec2(10, 40), glm::vec2(m_HullWidth *m_hullPercentAmount, 20), 0, glm::vec3(240, 207, 94));
}
