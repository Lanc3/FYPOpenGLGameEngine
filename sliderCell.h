#pragma once
#include "SDL_ttf.h"
#include "ResourceManager.h"

class sliderCell
{
public:
	sliderCell();
	sliderCell(float width,float height,float x,float y);
	~sliderCell();
	void Render(SDL_Renderer* m_renderer);
	void SetFull();
	void SetEmpty();
	void SetHighlighted();
private:
	SDL_Texture * m_cellImage;
	SDL_Rect m_rect;
};

