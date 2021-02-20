#include "EntityManager.h"

void EntityManager::Update(float deltaTime)
{
	for (auto& entity : entities)
	{
		entity->Update(deltaTime);
	}
}

void EntityManager::Render()
{
	for (auto& entity : entities)
	{
		entity->Render();
	}
}

bool EntityManager::HasNoEntities()
{
	return entities.size() == 0;
}

Entity& EntityManager::AddEntity(std::string entityName)
{
	// TODO: insert return statement here
	Entity* entity = new Entity(*this, entityName);
	this->entities.emplace_back(entity);
	return *entity;
}

std::vector<Entity*> EntityManager::GetEntities() const
{
	return this->entities;
}

unsigned int EntityManager::GetEntityCount()
{
	return this->entities.size();
}

void EntityManager::ClearData()
{
	for (auto& entity : entities)
	{
		entity->Destroy();
	}
}
