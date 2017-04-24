#pragma once
#include "SpriteRenderer.h"
#include "Weapon.h"
#include "BulletFactory.h"
#include "WeaponFactory.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "Camera.h"
#include "Model.h"
#include "Shader.h"
#include "Line.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "Polygon.h"
#include "Profile.h"
#include "Bullet.h"
class Ship
{
public:
	Ship(glm::vec3 startingPosition,string modelName);
	Ship() {};
	~Ship();
	float GetCurrentHp();
	float GetCurrentShield();
	glm::vec3 GetPosition();
	void Update(float dt);
	void CalculateLeftShortTargetDirection(float dt);
	void CalculateRightShortTargetDirection(float dt);
	void CalculateLongTargetDirection(float dt);
	void CalculateMovement(float dt);
	void Render(Camera * cam);
	void SetMovePosition(glm::vec3 move);
	void SetTargetShortLeft(glm::vec3 target);
	void SetTargetShortRight(glm::vec3 target);
	void SetTargetLong(glm::vec3 target);
	void ToggleShortRangeIndicator();
	void ToggleLongRangeIndicator();
	void DamageShip(int amount);
	void Kill();
	bool IsAlive();
	
private:
	glm::vec3 m_position,m_movePosition , m_shortRangeTargetLeft, m_shortRangeTargetRight, m_longRangeTarget, m_ultTarget;
	bool m_shortRangeLeftLock = false, m_shortRangeRightLock = false, m_longRangeLock = false, m_shortRangeIndicatorRender = false, m_longRangeIndicatorRender = false;
	float m_turnSpeed = 5, m_moveSpeed = 15;
	Model * m_model;
	Weapon m_shortRangeWeaponLeft, m_shortRangeWeaponRight, m_longRangeWeapon, m_ultWeapon;
	glm::vec3 m_velocity = glm::vec3(0);
	glm::vec3 m_direction = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 m_steering;
	float m_yaw;
	float m_acceleration = 15;
	Line m_moveLine;
	Weapon * m_leftShortWeapon, * m_rightShortWeapon, * m_longWeapon;
	BulletFactory * m_bulletFactory;
	Polygon m_shortRangeIndicator, m_longRangeIndicator;
	float m_currentHP, m_currentShield, m_maxHP, m_maxShield;
	bool m_isAlive = true;
};

