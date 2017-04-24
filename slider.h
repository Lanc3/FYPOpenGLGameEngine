#pragma once
#include "SDL_ttf.h"
#include "ResourceManager.h"
#include "sliderCell.h"
#include "FLInputManager.h"
class slider : public EventListener
{
public:
	slider();
	slider(float width, float height, float x, float y, float startingAmount);
	void BindKeys();
	void Left();
	void Right();
	~slider();
	void Render(SDL_Renderer* renderer);
	bool isSelected = false;
	int GetTotal();
	int GetHighlightedAmount();
private:
	SDL_Texture * m_sliderImage;
	SDL_Rect m_sliderRect;
	int m_heightlightedAmount = 0, m_currentAmount = 1, m_maxAmount = 100;
	std::vector<sliderCell*> m_listOFCells;
	float m_cellWidth, m_cellHeight;
	float m_offset = 5;
	InputManager* m_inputManager;
	int m_sliderTotal;
};

