#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include<string>
#include "Component.h"

class EntityManager;
class Component;

class Entity
{
private:
	EntityManager& entityManager;
	bool isActive;
	std::vector<Component*> components;
public:
	std::string entityName;
	Entity(EntityManager& entityManager);
	Entity(EntityManager& entityManager, std::string entityName);
	void Update(float deltaTime);
	void Render();
	void Destroy();
	bool IsActive() const;

};
#endif
