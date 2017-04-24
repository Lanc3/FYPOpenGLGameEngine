#include "ControllerSystem.h"


ControllerSystem::ControllerSystem()
{
	m_inputManager = InputManager::GetInstance();
}

ControllerSystem::~ControllerSystem()
{

}

void ControllerSystem::BindKeys()
{
}

void ControllerSystem::Pause()
{
	m_paused = !m_paused;
}
void ControllerSystem::Exit()
{
	m_exit = !m_exit;
}

void ControllerSystem::Turn(float dir)
{
	if (m_player != nullptr)
	{
		Transformable* t = (Transformable*)m_player->GetComponent("transformable");
		if (t != nullptr)
		{
			t->m_yaw -= (dir*dts) * 2;
		}
	}
}

void ControllerSystem::GamepadControls()
{
	Turn(m_inputManager->GetRightStickVectorNormal().x);

	Accelerate(-m_inputManager->GetLeftStickVectorNormal().y);
	Strafe(m_inputManager->GetLeftStickVectorNormal().x);

}

void ControllerSystem::CameraZoomControlls(Camera * cam)
{
	if (cam->GetZoom() > 50)
	{
		cam->SubtractZoom(ZoomIn());
	}
	if(cam->GetZoom() < 1200)
	{
		cam->AddZoom(ZoomOut());
	}
	m_moveSpeed = cam->GetZoom() / 2;
}

float ControllerSystem::ZoomIn()
{
	float accel = m_inputManager->GetRightTrigger();
	accel = accel / 35000;
	if (accel <= 0)
	{
		accel = 0;
	}
	return accel;
}

float ControllerSystem::ZoomOut()
{
	float decel = m_inputManager->GetLeftTrigger();
	decel = decel / 35000;
	if (decel < 0)
	{
		decel = 0;
	}
	return decel;
}

void ControllerSystem::Accelerate(float value)
{
	if (m_player != nullptr)
	{
		Transformable* t = (Transformable*)m_player->GetComponent("transformable");
		Velocity* v = (Velocity*)m_player->GetComponent("velocity");
		if (t != nullptr && v != nullptr)
		{
			v->m_acceleration = (value * m_moveSpeed);
		}
	}
}

bool ControllerSystem::GetPaused()
{
	return m_paused;
}
bool ControllerSystem::GetExit()
{
	return m_exit;
}

void ControllerSystem::Strafe(float value)
{
	if (m_player != nullptr)
	{
		Transformable* t = (Transformable*)m_player->GetComponent("transformable");
		Velocity* v = (Velocity*)m_player->GetComponent("velocity");
		if (t != nullptr && v != nullptr)
		{
			v->m_strafeAcceleration = (value * m_moveSpeed);
		}
	}
}

void ControllerSystem::HandleInput(float dt)
{
	dts = dt;

	m_inputManager->ProcessInput();
	m_inputManager->ConstantInput();

	if (m_inputManager->IsControllerConnected() == true)
	{
		GamepadControls();
	}
}

void ControllerSystem::SetEntity(Entity* e)
{
	m_player = e;
}

