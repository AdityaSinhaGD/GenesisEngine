#pragma once
#include "../Game.h"
#include "../EntityManager.h"
#include "TransformComponent.h"
#include "SpriteComponent.h" //including so we can toggle between animations using keyboard input

class KeyboardInputComponent : public Component
{
public:
	std::string upKey;
	std::string downKey;
	std::string leftKey;
	std::string rightKey;
	std::string fireKey;
	TransformComponent* transform;
	SpriteComponent* sprite;

	KeyboardInputComponent()
	{

	}

	KeyboardInputComponent(std::string upKey, std::string rightKey, std::string downKey, std::string leftKey, std::string fireKey)
	{
		this->upKey = GetSDLKeyStringCode(upKey);
		this->rightKey = GetSDLKeyStringCode(rightKey);
		this->downKey = GetSDLKeyStringCode(downKey);
		this->leftKey = GetSDLKeyStringCode(leftKey);
		this->fireKey = GetSDLKeyStringCode(fireKey);
	}

	std::string GetSDLKeyStringCode(std::string key)
	{
		if (key.compare("up") == 0)
		{
			return "1073741906";
		}
		if (key.compare("down") == 0)
		{
			return "1073741905";
		}
		if (key.compare("left") == 0)
		{
			return "1073741904";
		}
		if (key.compare("right") == 0)
		{
			return "1073741903";
		}
		if (key.compare("space") == 0)
		{
			return "32";
		}
		return std::to_string(static_cast<int>(key[0]));//return ascii value for any other key
	}

	void Initialize() override
	{
		transform = owner->GetComponent<TransformComponent>();
		sprite = owner->GetComponent<SpriteComponent>();
	}

	void Update(float deltaTime) override
	{

	}
};