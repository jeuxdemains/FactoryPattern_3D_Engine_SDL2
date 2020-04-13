#pragma once
#include <SDL.h>
#include <time.h>
#include "Vector3d.h"
#include "Matrix.h"

static float incRX, incRY, incRZ;

class Object3d
{
	float fRotationX_ = 0.0f, fRotationY_ = 0.0f, fRotationZ_ = 0.0f;
	uint8_t clrR_ = 0, clrG_ = 0, clrB_ = 0;
	SDL_Renderer* sdlRenderer_;
	std::vector<Vector3d::Mesh> objects_;
	int scrnW_, scrnH_;
	bool isFirst_ = false;
public:
	Object3d() {};
	Object3d(SDL_Renderer* sdlRndr, int scrnW, int scrnH) :
		sdlRenderer_(sdlRndr), scrnW_(scrnW), scrnH_(scrnH) {};

	void Object3dAdd(Vector3d::Mesh obj, SDL_Renderer* sdlR, int sW, int sH)
	{
		sdlRenderer_ = sdlR;
		scrnW_ = sW;
		scrnH_ = sH;

		incRX = incRY = incRZ += 0.001f;
		fRotationX_ = incRX;
		fRotationY_ = incRY;
		fRotationZ_ = incRZ;

		objects_.push_back(obj);
	};

	virtual ~Object3d() {};
	virtual Vector3d::Mesh InitObject() = 0;
	virtual void Update();
	virtual void Render();
};

