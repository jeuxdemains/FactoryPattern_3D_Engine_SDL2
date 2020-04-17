#pragma once
#include <memory>
#include "Object3dCube.h"

class ObjectsFactory
{
public:
	enum Type
	{
		cube,
		model
	};

	Object3d* createObject(Type objType, SDL_Renderer* 
		sdlRndr, int scrnW, int scrnH, uint8_t alpha = 255)
	{
		Object3d* obj;
		switch (objType)
		{
		case ObjectsFactory::cube:
			obj = new Object3dCube(sdlRndr, scrnW, scrnH, alpha);
			break;
		case ObjectsFactory::model:
		default:
			obj = new Object3dCube(sdlRndr, scrnW, scrnH, alpha);
			break;
		}

		return obj;
	}
};

