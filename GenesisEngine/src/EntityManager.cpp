#include "EntityManager.h"
#include "Collision.h"
#include "Components/ColliderComponent.h"

void EntityManager::Update(float deltaTime)
{
	for (auto& entity : entities)
	{
		entity->Update(deltaTime);
	}
}

void EntityManager::Render()
{
	/*for (auto& entity : entities)
	{
		entity->Render();
	}*/

	for (int layerNumber = 0; layerNumber < NUM_LAYERS; layerNumber++)
	{
		for (auto& entity : GetEntitiesByLayer(static_cast<LayerType>(layerNumber)))
		{
			entity->Render();
		}
	}
}

bool EntityManager::HasNoEntities()
{
	return entities.size() == 0;
}

Entity& EntityManager::AddEntity(std::string entityName,LayerType layer)
{
	// TODO: insert return statement here
	Entity* entity = new Entity(*this, entityName, layer);
	this->entities.emplace_back(entity);
	return *entity;
}

std::vector<Entity*> EntityManager::GetEntities() const
{
	return this->entities;
}

std::vector<Entity*> EntityManager::GetEntitiesByLayer(LayerType layer) const
{
	std::vector<Entity*> selectedEntities;
	for (auto& entity : entities)
	{
		if (entity->layer == layer)
		{
			selectedEntities.emplace_back(entity);
		}
	}
	return selectedEntities;
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

void EntityManager::ListAllEntities()
{
	for (auto& entity : entities)
	{
		std::cout << entity->entityName <<"\n";
	}
}

void EntityManager::ListAllEntitiesAndTheirComponents()
{
	for (auto& entity : entities)
	{
		std::cout << entity->entityName << "\n";
		for (auto& component : entity->GetAllAttachedComponents())
		{
			std::cout <<component->owner->entityName<<":"<<typeid(*component).name() << "\n";
		}
	}
}

std::string EntityManager::CheckEntityCollisions(Entity& myEntity) const
{
	ColliderComponent* myCollider = myEntity.GetComponent<ColliderComponent>();

	for (auto& entity : entities)
	{
		if (entity->entityName.compare(myEntity.entityName) != 0 && entity->entityName.compare("Tile") != 0)//not checking with self and tile entities.
		{
			if (entity->HasComponent<ColliderComponent>())
			{
				ColliderComponent* otherCollider = entity->GetComponent<ColliderComponent>();

				if (Collision::CheckRectangleCollision(myCollider->collider, otherCollider->collider))
				{
					return otherCollider->colliderTag;
				}
			}
		}
		
	}
	return std::string();//if no collisions we just return an empty string.
	
}
