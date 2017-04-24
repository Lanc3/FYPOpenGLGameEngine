#include "TransformSystem.h"

TransformSystem::TransformSystem()
{

}

TransformSystem::~TransformSystem()
{

}

void TransformSystem::Update(float dt)
{
	m_timer += dt;


	for (Entity* e : m_entities)
	{
		Transformable* t = (Transformable*)e->GetComponent("transformable");
		Velocity * v = (Velocity*)e->GetComponent("velocity");
		PolygonBounds* pB = (PolygonBounds*)e->GetComponent("polygonBounds");
		CircleBounds * cB = (CircleBounds*)e->GetComponent("circleBounds");
		ModelMesh * mM = (ModelMesh*)e->GetComponent("modelMesh");
		if (v != nullptr)
		{
			
			t->m_direction = glm::normalize(glm::vec3(cos(-t->m_yaw), 0, sin(-t->m_yaw)));
			t->m_strafeDirection = glm::cross(t->m_direction, glm::vec3(0, 1, 0));
			v->m_velocity = (t->m_direction * (v->m_acceleration * dt)) + (t->m_strafeDirection * (v->m_strafeAcceleration *dt));
			t->m_position += v->m_velocity;
		}
		if (t != nullptr && pB != nullptr)
		{
			pB->m_bounds->SetPosition(t->m_position);
		}
		if (cB != nullptr)
		{
			cB->m_bounds->SetCenter(t->m_position);
		}
	}
}

void TransformSystem::AddEntity(Entity* entity)
{
	m_entities.push_back(entity);
}