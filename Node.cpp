#include "Node.h"



Node::Node(int key, glm::vec3 startingPosition, Scene *se)
{

	s = se;
	m_currentState = STATE::NEW;
	m_lineColor = glm::vec4(1, 0, 0, 1);
	m_key = key;
	m_position = startingPosition;
	m_lineColor = { 1,0,0,1 };
	vector<glm::vec2*> boundPoints;
	for (int i = 10; i != 0; i--)
	{
		boundPoints.push_back(new glm::vec2(20 * cos(glm::radians(i * 36.0f)), 20 * sin(glm::radians(i * 36.0f))));
	}

	m_bounds = new Polygon(boundPoints, m_position);
	model = new Model("galaxy", m_position, glm::vec3(8, 8, 8), 0);
	model->setPosition(m_position);
	m_currentBounds = new Circle(m_position, 20);
	m_level = Profile::GetInstance()->GetLevel();
	m_enemyCount = Profile::GetInstance()->GetEnemyCount();
	m_inputManager = InputManager::GetInstance();
	m_inputManager->ProcessInput();
	Command* select = new SpaceCommand(std::bind(&Node::SelectKey, this), Press);
	m_inputManager->AddKey(Event::BUTTON_A, select, this);

	Command* fight = new SpaceCommand(std::bind(&Node::SelectFight, this), Press);
	m_inputManager->AddKey(Event::BUTTON_B, fight, this);
	m_isSelected = false;
	m_fightEnemies = false;

}

Node::Node()
{
}

void Node::Start()
{
	m_inputManager = InputManager::GetInstance();
	m_inputManager->ProcessInput();
	Command* select = new SpaceCommand(std::bind(&Node::SelectKey, this), Press);
	m_inputManager->AddKey(Event::BUTTON_A, select, this);

	Command* fight = new SpaceCommand(std::bind(&Node::SelectFight, this), Press);
	m_inputManager->AddKey(Event::BUTTON_B, fight, this);
	m_isSelected = false;
	m_fightEnemies = false;
}

void Node::SelectFight()
{
	//if()
}

Node::~Node()
{
}

void Node::Update(float dt, Scene * scene)
{
	m_rotation += dt;
	m_bounds->Update(dt);
	model->setRotation(glm::vec3(0, 1, 0), m_rotation, 0, 0);
	model->Update();
	if (m_currentState == STATE::IS_CREATING)
	{
		CreateChildren();
		m_currentState = STATE::IS_EXPLORED;
		m_fightEnemies = true;
	}
	if (m_currentState == STATE::IS_EXPLORED)
	{
		m_lineColor = glm::vec4(0, 1, 0, 1);

	}
	if (m_currentState == STATE::NEW)
	{
		m_lineColor = glm::vec4(1, 0, 0, 1);
	}
	for (const auto& itr : children)
	{
		itr->Update(dt, scene);
		itr->SetPointerCollision(m_pointerBounds);
	}
}

void Node::PrintInfo(SpriteRenderer * spriteRenderer)
{

	if (m_pointerBounds != NULL && m_currentBounds != nullptr)
	{
		if (m_pointerBounds->GetDistance(m_currentBounds) < m_currentBounds->GetRadius())
		{
			m_bounds->SetColor(glm::vec4(0, 155, 254, 1));
			if (m_currentState == STATE::NEW)
			{
				spriteRenderer->DrawSprite(ResourceManager::getInstance()->GetSprite("infoBox"),
					glm::vec2(0, 580), glm::vec2(440, 140), 0, glm::vec3(1.0f, 1.0f, 1.0f));
				s->RenderText("Level : " + to_string(m_level), 20, 100, 0.65f, glm::vec3(0, 155, 254));
				s->RenderText("Enemies : " + to_string(m_enemyCount), 20, 50, 0.65f, glm::vec3(0, 155, 254));
				s->RenderText("A to Explore", 20, 20, 0.65f, glm::vec3(0, 155, 254));
			}
			else if (m_fightEnemies && m_currentState == STATE::IS_EXPLORED)
			{
				spriteRenderer->DrawSprite(ResourceManager::getInstance()->GetSprite("infoBox"),
					glm::vec2(0, 580), glm::vec2(440, 140), 0, glm::vec3(1.0f, 1.0f, 1.0f));
				s->RenderText("Enemies : " + to_string(m_enemyCount), 20, 80, 0.65f, glm::vec3(0, 155, 254));
				s->RenderText("push A to enter", 20, 20, 0.65f, glm::vec3(0, 155, 254));
			}
			else if (!m_fightEnemies && m_currentState == STATE::IS_EXPLORED)
			{
				spriteRenderer->DrawSprite(ResourceManager::getInstance()->GetSprite("infoBox"),
					glm::vec2(0, 580), glm::vec2(440, 140), 0, glm::vec3(1.0f, 1.0f, 1.0f));
				s->RenderText("Enemies : " + to_string(0), 20, 80, 0.65f, glm::vec3(0, 155, 254));
				s->RenderText("Explored", 20, 20, 0.65f, glm::vec3(0, 155, 254));
			}
		}
	}
}

void Node::CreateChildren()
{
	srand(time(NULL));
	for (int i = 0; i < m_maxCreationAmount; i++)
	{
		float r = rand() % (m_maxSpawnDistance - m_minSpawnDistance) + m_minSpawnDistance;
		float a = rand() % (m_maxAngle - m_minAngle) + m_minAngle;
		glm::vec3 calulatedPosition = m_position + glm::vec3(r *cos(glm::radians(a)), 0, r *sin(glm::radians(a)));
		children.push_back(new Node(m_key + (i + 1), calulatedPosition, s));
		glm::vec3 lineStart = m_position + glm::vec3(20 *cos(glm::radians(a)), 0, 20 *sin(glm::radians(a)));
		glm::vec3 lineEnd = m_position + glm::vec3((r - 20) *cos(glm::radians(a)), 0, (r - 20) *sin(glm::radians(a)));
		m_conectionLines.push_back(new Line(lineStart, lineEnd, 5));
	}
}

void Node::Render(Camera *cam, SpriteRenderer * spriteRenderer)
{
	m_bounds->Render(cam);
	m_bounds->SetColor(m_lineColor);
	for (const auto& itr : m_conectionLines)
	{
		itr->SetLineColor(m_lineColor);
		itr->Render(cam);
	}
	for (const auto& itr : children)
	{
		itr->Render(cam, spriteRenderer);
	}
	model->Render(cam);
	PrintInfo(spriteRenderer);
}

glm::vec3 Node::GetPosition()
{
	return m_position;
}

STATE Node::GetState()
{
	return m_currentState;
}

void Node::SetState(STATE state)
{
	m_currentState = state;
}

void Node::SetLineColor(glm::vec4 color)
{
	m_lineColor = color;
}

void Node::SetPointerCollision(Circle* pointerBounds)
{
	m_pointerBounds = pointerBounds;
}

void Node::SelectKey()
{
	if (m_pointerBounds != nullptr && m_pointerBounds->GetDistance(m_currentBounds) < m_currentBounds->GetRadius())
	{
		m_lineColor = glm::vec4(1.0f, 0.8f, 0.1f, 1.0f);

		if (m_currentState != STATE::IS_EXPLORED)
		{
			m_currentState = STATE::IS_CREATING;
		}

		if (m_fightEnemies)
		{
			m_fightEnemies = false;
			s->GoToScene("Fighting");
		}
	}
	for (const auto& itr : children)
	{
		itr->SelectKey();
	}
}

