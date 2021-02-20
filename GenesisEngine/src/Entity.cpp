#include "Entity.h"

Entity::Entity(EntityManager& entityManager):entityManager(entityManager)
{
	this->isActive = true;
}

Entity::Entity(EntityManager& entityManager, std::string entityName):entityManager(entityManager),entityName(entityName)
{
	this->isActive = true;
}

void Entity::Update(float deltaTime)
{
	for (auto& component : components)
	{
		component->Update(deltaTime);
	}
}

void Entity::Render()
{
	for (auto& component : components)
	{
		component->Render();
	}
}

void Entity::Destroy()
{
	this->isActive = false;
}

bool Entity::IsActive() const
{
	return this->isActive;
}
