#include<iostream>
#include "Constants.h"
#include "Game.h"
#include <glm/glm.hpp>
#include "AssetManager.h"
#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/TranslationComponent.h"
#include "Components/KeyboardInputComponent.h"
#include "Components/ColliderComponent.h"
#include "Map.h"


EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);
SDL_Renderer* Game::renderer;
SDL_Event Game::event;
SDL_Rect Game::camera = { 0,0,WINDOW_WIDTH,WINDOW_HEIGHT };
Map* map;
bool Game::isDebugMode;

Game::Game()
{
	this->isRunning = false;
	this->window = NULL;
	this->renderer = NULL;
	this->isDebugMode = false;
	ticksLastFrame = 0;
}

Game::~Game()
{

}

bool Game::IsRunning() const {
	return this->isRunning;
}

void Game::Initialize(int width, int height)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cerr << "Error initializing SDL";
		return;
	}

	window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_BORDERLESS);
	if (!window)
	{
		std::cerr << "Error creating window";
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
	{
		std::cerr << "Error initializing renderer";
		return;
	}

	LoadLevel(0);
	//debug to console block
	manager.ListAllEntitiesAndTheirComponents();
	//debug block ends
	isRunning = true;
	return;
}

void Game::ProcessInput()
{
	//SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			isRunning = false;
		}
		if (event.key.keysym.sym == SDLK_F1)
		{
			isDebugMode = !isDebugMode;
		}
		break;
	default:
		break;
	}
}

void Game::Update()
{
	//naive While loop to wait until we can reach our target framerate. This process will tax the processor significantly.
	//while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TARGET_TIME));

	//Delay execution until we reach our target frame rendering time in milliseconds
	int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - ticksLastFrame);

	//Only call Delay if our system processes this frame too quickly
	if (timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME)
	{
		SDL_Delay(timeToWait);
	}

	float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

	//Clamping delta time incase we debug and things start to jump forward in time by a massive magnitude
	deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

	ticksLastFrame = SDL_GetTicks();

	//toDO call EntityManager's Update method to update all entites as a function of delta time
	manager.Update(deltaTime);

	ProcessCameraMovement();

	ProcessCollisions();
}

void Game::Render()
{
	SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
	SDL_RenderClear(renderer);

	//toDo Call EntityManager here to render whatever we want
	if (manager.HasNoEntities())
	{
		return;
	}
	manager.Render();

	SDL_RenderPresent(renderer);
}

Entity& playerEntity = manager.AddEntity("player", PLAYER_LAYER);

void Game::ProcessCameraMovement()
{
	TransformComponent* playerTransForm = playerEntity.GetComponent<TransformComponent>();
	camera.x = playerTransForm->position.x - (WINDOW_WIDTH / 2);
	camera.y = playerTransForm->position.y - (WINDOW_HEIGHT / 2);

	//clamping values incase we go out of bounds
	camera.x = camera.x < 0 ? 0 : camera.x;
	camera.y = camera.y < 0 ? 0 : camera.y;

	camera.x = camera.x > camera.w ? camera.w : camera.x;
	camera.y = camera.y > camera.h ? camera.h : camera.y;
}

void Game::ProcessCollisions()
{
	//Check all entities colliding with this one.
	std::string collisionTagType = manager.CheckEntityCollisions(playerEntity);
	if (collisionTagType.compare("enemy") == 0)
	{
		std::cout << collisionTagType <<"-----------------------------------------------";
		//isRunning = false;//stops application.
	}
}

void Game::Destroy()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}


void Game::LoadLevel(int levelNumber)
{
	//Loading a tilemap before loading other entities
	std::string mapFilePath = "./assets/tilemaps/jungle.png";
	assetManager->AddTexture("Level-TileMapTexture", mapFilePath.c_str());
	map = new Map("Level-TileMapTexture", 2, 32);
	map->LoadMap("./assets/tilemaps/jungle.map", 25, 20);//Hard coding the values of the tilemap elements for now.

	//Width and height of transform component should match texture dimensions to produce artifactless animations
	Entity& entity1 = manager.AddEntity("truck", ENEMY_LAYER);
	std::string textureFilePath1 = "./assets/images/truck-ford-right.png";
	assetManager->AddTexture("truck-Image", textureFilePath1.c_str());
	entity1.AddComponent<TransformComponent>(0, 300, 32, 32, 3);
	entity1.AddComponent<TranslationComponent>(10, 0);
	entity1.AddComponent<SpriteComponent>("truck-Image");
	entity1.AddComponent<ColliderComponent>("enemy", 0, 0, 35, 35);
	//std::cout << entity1.HasComponent<SpriteComponent>() <<"\n";


	
	std::string textureFilePath2 = "./assets/images/chopper-spritesheet.png";
	assetManager->AddTexture("chopper-SpriteSheet", textureFilePath2.c_str());
	playerEntity.AddComponent<TransformComponent>(200, 100, 32, 32, 2);
	playerEntity.AddComponent<TranslationComponent>();
	playerEntity.AddComponent<SpriteComponent>("chopper-SpriteSheet", 2, 60, true, false);
	playerEntity.AddComponent<KeyboardInputComponent>("w", "d", "s", "a", "space");
	playerEntity.AddComponent<ColliderComponent>("player", 200, 100, 32, 32);


	Entity& entity3 = manager.AddEntity("radar", UI_LAYER);
	std::string textureFilePath3 = "./assets/images/radar-spritesheet.png";
	assetManager->AddTexture("radar-SpriteSheet", textureFilePath3.c_str());
	entity3.AddComponent<TransformComponent>(720, 20, 64, 64, 1);
	entity3.AddComponent<SpriteComponent>("radar-SpriteSheet", 8, 60, false, true);

	Entity& entity4 = manager.AddEntity("lightning", UI_LAYER);
	std::string textureFilePath4 = "./assets/images/Lightning.jpg";
	assetManager->AddTexture("lightning-SpriteSheet", textureFilePath4.c_str());
	entity4.AddComponent<TransformComponent>(0, 0, 128, 160, 1);
	entity4.AddComponent<TranslationComponent>();
	entity4.AddComponent<SpriteComponent>("lightning-SpriteSheet", 4, 90, false, false);


}
