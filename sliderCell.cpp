#include "sliderCell.h"



sliderCell::sliderCell()
{

}

sliderCell::sliderCell(float w, float h, float x, float y)
{
	m_rect.x = x;
	m_rect.y = y;
	m_rect.w = w;
	m_rect.h = h;
	m_cellImage = ResourceManager::getInstance()->getInstance()->GetTexture("cellEmpty");
}


sliderCell::~sliderCell()
{
}

void sliderCell::Render(SDL_Renderer* m_renderer)
{
	SDL_RenderCopy(m_renderer, m_cellImage, NULL, &m_rect);
}

void sliderCell::SetFull()
{
	m_cellImage = ResourceManager::getInstance()->getInstance()->GetTexture("cellFull");
}
void sliderCell::SetEmpty()
{
	m_cellImage = ResourceManager::getInstance()->getInstance()->GetTexture("cellEmpty");
}

void sliderCell::SetHighlighted()
{
	m_cellImage = ResourceManager::getInstance()->getInstance()->GetTexture("cellHighlight");
}
