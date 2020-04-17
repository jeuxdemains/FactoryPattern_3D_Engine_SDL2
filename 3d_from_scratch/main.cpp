#include <stdio.h>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "Engine.h"

int main()
{
	Engine* engine = new Engine(1440, 1080);
	delete engine;

	return 0;
}