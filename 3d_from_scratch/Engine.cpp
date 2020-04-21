#include "Engine.h"

Engine::Engine(const int width, const int height) :
	iWinWidth_(width), iWinHeight_(height)
{
	SDL_Init(SDL_INIT_VIDEO);

	sdlMainWindow_ = SDL_CreateWindow(
		"3D From Scratch",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		iWinWidth_, iWinHeight_,
		SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_RESIZABLE);

	sdlRenderer_ = SDL_CreateRenderer(
		sdlMainWindow_, -1,
		SDL_RENDERER_ACCELERATED);

	SDL_SetRenderDrawBlendMode(sdlRenderer_, SDL_BLENDMODE_BLEND);

	int numOfObjs = 600;
	float alpha = 0;
	for (int i = 0; i < numOfObjs; i++)
	{
		if (i < numOfObjs - 1)
			alpha += 0.049f;
		else
			alpha = 100;

		objects_.push_back(objectsFactory_->createObject(
			ObjectsFactory::Type::cube,
			sdlRenderer_, iWinWidth_, iWinHeight_, alpha));
	}

	loop();
}

Engine::~Engine()
{
	SDL_DestroyRenderer(sdlRenderer_);
	SDL_DestroyWindow(sdlMainWindow_);
}

void Engine::loop()
{
	int startTick;

	while (bIsLooping_)
	{
		startTick = SDL_GetTicks();

		handleEvents();
		update();
		
		int endTick = SDL_GetTicks() - startTick;
		if (endTick < fFps_)
			SDL_Delay(fFps_ - (float)endTick);
	}
}

void Engine::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_KEYDOWN:
		if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			bIsLooping_ = false;
		break;
	default:
		break;
	}
}

void Engine::update()
{
	SDL_SetRenderDrawColor(sdlRenderer_, 0, 0, 0, 255);
	SDL_RenderClear(sdlRenderer_);

	//update all objects
	for (auto obj : objects_)
		obj->Update();

	SDL_RenderPresent(sdlRenderer_);
}