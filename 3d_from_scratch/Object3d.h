#pragma once
#include <SDL.h>
#include <time.h>
#include <memory>
#include "Vector3d.h"
#include "Matrix.h"

static float incRX, incRY, incRZ;

class Object3d
{
	float fRotationX_ = 0.0f, fRotationY_ = 0.0f, fRotationZ_ = 0.0f;
	uint8_t clrR_ = 0, clrG_ = 0, clrB_ = 0;
	float clrA_ = 255;
	SDL_Renderer* sdlRenderer_;
	std::vector<Vector3d::Mesh> objects_;
	int scrnW_, scrnH_;
	bool isFirst_ = false;
	Matrix* matrix = nullptr;

public:
	Object3d() {};
	Object3d(SDL_Renderer* sdlRndr, int scrnW, int scrnH) :
		sdlRenderer_(sdlRndr), scrnW_(scrnW), scrnH_(scrnH) {};

	void Object3dAdd(Vector3d::Mesh obj, SDL_Renderer* sdlR, 
		int sW, int sH, float alpha)
	{
		sdlRenderer_ = sdlR;
		scrnW_ = sW;
		scrnH_ = sH;
		matrix = new Matrix((float)scrnW_, (float)scrnH_);

		incRX = incRY = incRZ += 0.013f;
		fRotationX_ = incRX;
		fRotationY_ = incRY;
		fRotationZ_ = incRZ;
		clrA_ = alpha;

		objects_.push_back(obj);
	};

	//back-face culling
	bool IsFrontFace(Vector3d::Triangle& tri)
	{
		//make lines from vertices b->a & c->a
		Vector3d::Vector3 line1, line2;
		line1.x = tri.b.x - tri.a.x;
		line1.y = tri.b.y - tri.a.y;
		line1.z = tri.b.z - tri.a.z;

		line2.x = tri.c.x - tri.a.x;
		line2.y = tri.c.y - tri.a.y;
		line2.z = tri.c.z - tri.a.z;

		Vector3d* v3d = new Vector3d();
		Vector3d::Vector3 cross = v3d->Cross(line1, line2);
		Vector3d::Vector3 normal, cam;

		normal = v3d->Normalize(cross);
		cam.x = tri.a.x - 0.0f;
		cam.y = tri.a.y - 0.0f;
		cam.z = tri.a.z - 0.0f;

		float dot = v3d->Dot(normal, cam);
		delete v3d;

		if (dot < 0.0f)
			return true;

		return false;
	}

	void FillPolygon(Vector3d::Triangle& tri)
	{
		int x, y, dx, dy;
		x = tri.a.x + tri.b.x + tri.c.x;
		x /= 3;
		y = tri.a.y + tri.b.y + tri.c.y;
		y /= 3;

		SDL_RenderDrawPoint(sdlRenderer_, x, y);
		
	}

	int Min(int a, int b)
	{
		return (a > b) ? a : b;
	}

	virtual ~Object3d();
	virtual Vector3d::Mesh InitObject() = 0;
	virtual void Update();
	virtual void Render();
};

