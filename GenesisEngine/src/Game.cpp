#include<iostream>
#include "Constants.h"
#include "Game.h"
#include <glm/glm.hpp>

EntityManager manager;
SDL_Renderer* Game::renderer;

Game::Game()
{
	this->isRunning = false;
	this->window = NULL;
	this->renderer = NULL;
	ticksLastFrame = 0;
}

Game::~Game()
{

}

bool Game::IsRunning() const {
	return this->isRunning;
}

glm::vec2 projectilePos = glm::vec2(0.0f, 0.0f);
glm::vec2 projectileVelocity = glm::vec2(20.0f, 30.0f);


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

	isRunning = true;
	return;
}

void Game::ProcessInput()
{
	SDL_Event event;
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

	projectilePos = glm::vec2(projectilePos.x + projectileVelocity.x * deltaTime, projectilePos.y + projectileVelocity.y * deltaTime);
}

void Game::Render()
{
	SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
	SDL_RenderClear(renderer);

	SDL_Rect projectile{
		(int)projectilePos.x,
		(int)projectilePos.y,
		10,
		10
	};

	SDL_SetRenderDrawColor(renderer, 255, 21, 21, 255);
	SDL_RenderFillRect(renderer, &projectile);

	SDL_RenderPresent(renderer);
}

void Game::Destroy()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void Game::LoadLevel()
{
}
