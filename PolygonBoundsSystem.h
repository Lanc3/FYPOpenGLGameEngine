#pragma once

#include "Entity.h"
#include "Components.h"

#include <vector>

class PolygonBoundsSystem
{
public:
	PolygonBoundsSystem();
	~PolygonBoundsSystem();

	void Update(float dt);
	void Draw(Camera* cam);
	void AddEntity(Entity* e);

private:
	std::vector<Entity*> m_entities;
};

