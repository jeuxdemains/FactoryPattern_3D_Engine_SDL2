#pragma once
#include <array>
#include "SDL.h"
#include "Vector3d.h"
#include "Matrix.h"
#include "Object3d.h"
#include "ObjectsFactory.h"

class Engine
{
	SDL_Window* sdlMainWindow_ = nullptr;
	SDL_Renderer* sdlRenderer_ = nullptr;
	int iWinWidth_, iWinHeight_;
	bool bIsLooping_ = true;
	float fFps_ = 1000.0f / 60.0f;
	std::unique_ptr<ObjectsFactory> objectsFactory_ = std::make_unique<ObjectsFactory>();
	std::vector<Object3d*> objects_;

	void loop();
	void handleEvents();
	void update();

public:
	Engine(const int width, const int height);
	~Engine();
};