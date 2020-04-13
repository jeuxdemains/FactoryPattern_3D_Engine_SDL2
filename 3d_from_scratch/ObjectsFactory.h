#pragma once
#include <memory>
#include "Object3dCube.h"

class ObjectsFactory
{
public:
	enum ObjectType
	{
		cube,
		model
	};

	Object3d* createObject(ObjectType objType, SDL_Renderer* sdlRndr, int scrnW, int scrnH)
	{
		Object3d* obj;
		switch (objType)
		{
		case ObjectsFactory::cube:
			obj = new Object3dCube(sdlRndr, scrnW, scrnH);
			break;
		case ObjectsFactory::model:
		default:
			obj = new Object3dCube(sdlRndr, scrnW, scrnH);
			break;
		}

		return obj;
	}
};

