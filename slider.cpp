#include "slider.h"



slider::slider()
{

}

slider::slider(float w, float h, float x, float y,float startingAmount)
{
	m_inputManager = InputManager::GetInstance();
	m_inputManager->ProcessInput();
	m_sliderRect.x = x;
	m_sliderRect.y = y;
	m_sliderRect.w = w;
	m_sliderRect.h = h;
	m_sliderImage = ResourceManager::getInstance()->getInstance()->GetTexture("slider");
	m_currentAmount = startingAmount;
	m_cellWidth = w / m_maxAmount;
	for (int i = 0; i < m_maxAmount; i++)
	{
		m_listOFCells.push_back(new sliderCell(m_cellWidth-1, h-(m_offset*2), x + m_offset + ((m_cellWidth-0.10f)*i), y + m_offset));
	}
	if (InputManager::GetInstance()->IsControllerConnected())
	{
		BindKeys();
	}
}
void slider::BindKeys()
{
	//Command* left = new SpaceCommand(std::bind(&slider::Left, this), Press);
	//m_inputManager->AddKey(EventListener::Event::BUTTON_DPAD_LEFT, left, this);

	//Command* right = new SpaceCommand(std::bind(&slider::Right, this), Press);
	//m_inputManager->AddKey(Event::BUTTON_DPAD_RIGHT, right, this);
}
void slider::Left()
{
	if (isSelected)
	{
		if (m_heightlightedAmount > 0)
			m_heightlightedAmount--;
	}
}
void slider::Right()
{
	if (isSelected)
	{
		if (m_heightlightedAmount < m_maxAmount)
			m_heightlightedAmount++;
	}
}

slider::~slider()
{

}

void slider::Render(SDL_Renderer * renderer)
{
	for (int i = 0; i < m_currentAmount; i++)
	{
		m_listOFCells[i]->SetFull();
	}
	for (int i = m_currentAmount; i < m_currentAmount+m_heightlightedAmount; i++)
	{
		m_listOFCells[i]->SetHighlighted();
	}
	for (int i = m_currentAmount + m_heightlightedAmount; i < m_maxAmount; i++)
	{
		m_listOFCells[i]->SetEmpty();
	}
	if (!isSelected)
	{
		m_sliderImage = ResourceManager::getInstance()->getInstance()->GetTexture("slider");
	}
	else
	{
		m_sliderImage = ResourceManager::getInstance()->getInstance()->GetTexture("sliderSelected");
	}
	SDL_RenderCopy(renderer, m_sliderImage, NULL, &m_sliderRect);
	for (const auto& itr : m_listOFCells)
	{
		itr->Render(renderer);
	}
	m_inputManager->ProcessInput();

	m_sliderTotal = m_currentAmount + m_heightlightedAmount;
}

int slider::GetTotal()
{
	return m_sliderTotal;
}

int slider::GetHighlightedAmount()
{
	return m_heightlightedAmount;
}
