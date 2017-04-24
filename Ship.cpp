#include "Ship.h"



Ship::Ship(glm::vec3 startingPosition, string modelName)
{
	m_position = startingPosition;
	m_model = new Model(modelName, startingPosition, glm::vec3(50, 50, 50), 0);
	m_bulletFactory = new BulletFactory();
	WeaponFactory::getInstance()->createWeapons(m_bulletFactory);

	m_leftShortWeapon = new Weapon(WeaponFactory::getInstance()->getNewWeapon(WeaponType::SHORT));
	m_leftShortWeapon->Update(glm::vec3(0, 0, 0), 90, 0);
	m_rightShortWeapon = new Weapon(WeaponFactory::getInstance()->getNewWeapon(WeaponType::SHORT));
	m_rightShortWeapon->Update(glm::vec3(0, 0, 0), 90, 0);
	m_longWeapon =  new Weapon(WeaponFactory::getInstance()->getNewWeapon(WeaponType::LONG));
	m_longWeapon->Update(glm::vec3(0, 0, 0), 90, 0);
	vector<glm::vec2*> boundPoints;
	for (int i = 10; i != 0; i--)
	{
		boundPoints.push_back(new glm::vec2(m_rightShortWeapon->GetRange() * cos(glm::radians(i * 36.0f)), m_rightShortWeapon->GetRange() * sin(glm::radians(i * 36.0f))));
	}
	m_shortRangeIndicator = Polygon(boundPoints, m_position);
	m_shortRangeIndicator.SetColor(glm::vec4(0, 150, 254, 1));
	vector<glm::vec2*> nboundPoints;
	for (int i = 10; i != 0; i--)
	{
		nboundPoints.push_back(new glm::vec2(m_longWeapon->GetRange() * cos(glm::radians(i * 36.0f)), m_longWeapon->GetRange() * sin(glm::radians(i * 36.0f))));
	}
	m_longRangeIndicator = Polygon(nboundPoints, m_position);
	m_longRangeIndicator.SetColor(glm::vec4(255, 0, 0, 1));

	m_maxHP = Profile::GetInstance()->GetShipHullAmount();
	m_maxShield = Profile::GetInstance()->GetShipShieldAmount();
	m_currentHP = m_maxHP;
	m_currentShield = m_maxShield;
	m_acceleration = Profile::GetInstance()->GetShipHEngineSpeedAmount();
	m_bounds = Circle(m_position, 50);
}


Ship::~Ship()
{
}
float Ship::GetCurrentHp()
{
	return m_currentHP;
}
float Ship::GetCurrentShield()
{
	return m_currentShield;
}

glm::vec3 Ship::GetPosition()
{
	return m_position;
}
void Ship::Update(float dt)
{
	m_model->Update();
	m_bulletFactory->Update(dt);
	CalculateMovement(dt);
	CalculateLeftShortTargetDirection(dt);
	CalculateRightShortTargetDirection(dt);
	m_shortRangeIndicator.SetPosition(m_position);
	m_shortRangeIndicator.Update(dt);
	m_longRangeIndicator.SetPosition(m_position);
	m_longRangeIndicator.Update(dt);
	CalculateLongTargetDirection(dt);
	m_bounds.SetCenter(m_position);
	if (m_currentHP > 0)
	{
		m_isAlive = true;
	}
	else
	{
		m_isAlive = false;
	}
}
void Ship::CalculateLeftShortTargetDirection(float dt)
{
	if (m_shortRangeLeftLock)
	{
		float angle = atan2(m_shortRangeTargetLeft.z - m_position.z, m_shortRangeTargetLeft.x - m_position.x);
		//caclulate gun positions
		glm::vec3 leftGunPosition = (glm::cross(m_direction, glm::vec3(0, 1, 0)) * -15.0f) + (m_direction * 50.0f);
		m_leftShortWeapon->Update(m_position + leftGunPosition, angle, dt);
		m_leftShortWeapon->fire();
	}
}
void Ship::CalculateRightShortTargetDirection(float dt)
{
	if (m_shortRangeRightLock)
	{
		float angle = atan2(m_shortRangeTargetRight.z - m_position.z, m_shortRangeTargetRight.x - m_position.x);
		//caclulate gun positions
		glm::vec3 rightGunPosition = (glm::cross(m_direction, glm::vec3(0, 1, 0)) * 15.0f) + (m_direction * 50.0f);
		m_rightShortWeapon->Update(m_position + rightGunPosition, angle, dt);
		m_rightShortWeapon->fire();
	}
}

void Ship::CalculateLongTargetDirection(float dt)
{
	if (m_longRangeLock)
	{
		float angle = atan2(m_longRangeTarget.z - m_position.z, m_longRangeTarget.x - m_position.x);
		//caclulate gun positions
		glm::vec3 rightGunPosition = (glm::cross(m_direction, glm::vec3(0, 1, 0)) * 25.0f) + (m_direction * 130.0f);
		m_longWeapon->Update(m_position + rightGunPosition, angle, dt);
		m_longWeapon->fire();
	}
}

void Ship::CalculateMovement(float dt)
{
	if (abs(glm::distance(m_movePosition, m_position)) > 1)
	{

		m_steering = glm::vec3(0);
		m_steering = glm::normalize(glm::vec3(m_movePosition.x - m_position.x, 0, m_movePosition.z - m_position.z));

		glm::vec3 cross = glm::cross(m_direction, m_steering);
		if (glm::length(cross) < 0.001f)
		{
			m_direction = m_steering;
		}
		else
		{
			m_direction = glm::rotate(m_direction, glm::radians(m_turnSpeed)*dt, cross);
		}

		m_yaw = atan2(-m_direction.z, m_direction.x);

		m_velocity = m_direction * (m_acceleration * dt);
		m_position += m_velocity;
		m_model->setRotation(glm::vec3(0, 1, 0), m_yaw + (PI / 2), 0, 0);
		m_model->setPosition(m_position + glm::vec3(0, 10, 0));

		m_moveLine = Line(m_position, m_movePosition);
		m_moveLine.SetLineColor(glm::vec4(0, 150, 254, 255));
	}
}
void Ship::ToggleMoveLineIndicator()
{
	m_toogleMoveLine = !m_toogleMoveLine;
}
void Ship::Render(Camera * cam)
{
	m_model->Render(cam);
	if (m_isAlive)
	{
		if (m_toogleMoveLine)
		{
			m_moveLine.Render(cam);
		}
	}
	m_bulletFactory->Render(cam);
	if (m_shortRangeIndicatorRender)
	{
		m_shortRangeIndicator.Render(cam);
	}
	if (m_longRangeIndicatorRender)
	{
		m_longRangeIndicator.Render(cam);
	}
}

void Ship::SetMovePosition(glm::vec3 move)
{
	m_movePosition = move;
}

void Ship::SetTargetShortLeft(glm::vec3 target)
{
	m_shortRangeTargetLeft = target;
	m_shortRangeLeftLock = true;
}
void Ship::SetTargetShortRight(glm::vec3 target)
{
	m_shortRangeTargetRight = target;
	m_shortRangeRightLock = true;
}

void Ship::SetTargetLong(glm::vec3 target)
{
	m_longRangeTarget = target;
	m_longRangeLock = true;
}
void Ship::ToggleShortRangeIndicator()
{
	m_shortRangeIndicatorRender = !m_shortRangeIndicatorRender;
}
void Ship::ToggleLongRangeIndicator()
{
	m_longRangeIndicatorRender = !m_longRangeIndicatorRender;
}

void Ship::DamageShip(int amount)
{
	if (m_currentHP <= 0)
	{
		m_currentShield -= amount;
		if (m_currentShield < 0)
		{
			m_currentShield = 0;
		}
	}
	else
	{
		m_currentHP -= amount;
	}
}

void Ship::Kill()
{
	m_isAlive = false;
}

bool Ship::IsAlive()
{
	return m_isAlive;
}

Circle Ship::GetBounds()
{
	return m_bounds;
}

vector<Bullet*> Ship::GetBulletList()
{
	return m_bulletFactory->getBullets();
}
