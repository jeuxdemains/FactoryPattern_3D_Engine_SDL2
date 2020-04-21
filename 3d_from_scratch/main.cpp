#include <stdio.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "Engine.h"

int main()
{
	Engine* engine = new Engine(1024, 768);
	delete engine;

	return 0;
}