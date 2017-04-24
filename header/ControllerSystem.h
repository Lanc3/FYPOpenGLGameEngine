#pragma once

#include "Entity.h"
#include "Components.h"
#include <vector>
#include "FLInputManager.h"

class ControllerSystem : public EventListener {
public:
	ControllerSystem();
	~ControllerSystem();

	void Pause();
	void Exit();

	void GamepadControls();
	void CameraZoomControlls(Camera * cam);
	float ZoomIn();
	float ZoomOut();

	void Accelerate(float value);
	void Strafe(float value);
	void Turn(float dir);

	bool GetPaused();
	bool GetExit();

	void HandleInput(float dt);
	void SetEntity(Entity* e);

private:
	void BindKeys();

	bool m_paused;
	bool m_exit;
	float m_moveSpeed = 50;
	InputManager* m_inputManager;
	Entity* m_player;
	float dts;
};