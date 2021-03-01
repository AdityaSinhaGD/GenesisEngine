#pragma once
#include "../EntityManager.h"
#include <SDL.h>
#include "../TextureManager.h"
#include "../AssetManager.h"
#include "TransformComponent.h"

class SpriteComponent :public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect sourceRectangle;
	SDL_Rect targetRectangle;
public:
	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent(const char* filePath)
	{
		SetTexture(filePath);
	}
	void SetTexture(std::string assetTextureId)
	{
		texture = Game::assetManager->GetTexture(assetTextureId);
	}

	void Initialize() override
	{
		transform = owner->GetComponent<TransformComponent>();
		sourceRectangle.x = 0;
		sourceRectangle.y = 0;
		sourceRectangle.w = transform->width;
		sourceRectangle.h = transform->height;
	}

	void Update(float deltaTime) override
	{
		targetRectangle.x = (int)transform->position.x;
		targetRectangle.y = (int)transform->position.y;
		targetRectangle.w = transform->width * transform->scale;
		targetRectangle.h = transform->height * transform->scale;
	}

	void Render() override
	{
		TextureManager::DrawTexture(texture, sourceRectangle, targetRectangle, spriteFlip);
	}
};

