#pragma once
#include "Object3d.h"

class Object3dCube : public Object3d
{
public:
	Object3dCube(SDL_Renderer* sdlRndr, int scrnW, int scrnH)
	{
		Object3dAdd(InitObject(), sdlRndr, scrnW, scrnH);
	};
	~Object3dCube() {};
	Vector3d::Mesh InitObject() override;
};

