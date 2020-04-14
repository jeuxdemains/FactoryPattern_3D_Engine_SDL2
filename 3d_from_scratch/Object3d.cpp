#include "Object3d.h"

Object3d::~Object3d()
{
	delete matrix;
}

void Object3d::Update()
{
	srand(time(0));
	float mul = rand() % 3;

	fRotationX_ += 1.0f * 0.01f;
	fRotationY_ += 1.0f * 0.02f;
	fRotationZ_ += 1.0f * 0.03f;

	clrR_ = abs(155 * cos(fRotationX_) * 1.5);
	clrG_ = abs(155 * cos(fRotationY_) * 1.5);
	clrB_ = abs(155 * cos(fRotationZ_) * 1.5);

	Render();
}

void Object3d::Render()
{
	Matrix::Matrix4 const matRotX =
		matrix->getRotationMatrix(fRotationX_, Matrix::Axis::x);
	Matrix::Matrix4 const matRotY =
		matrix->getRotationMatrix(fRotationY_, Matrix::Axis::y);
	Matrix::Matrix4 const matRotZ =
		matrix->getRotationMatrix(fRotationZ_, Matrix::Axis::z);

	Vector3d::Triangle
		projectedTri[24],
		rotX[24],
		rotY[24],
		rotZ[24];

	int i = 0;
	for (auto triangle : objects_[0].triangles)
	{
		rotZ[i] = triangle;
		matrix->mulTriangleByMatrix(triangle, rotZ[i], matRotZ);
		rotY[i] = rotZ[i];
		matrix->mulTriangleByMatrix(rotZ[i], rotY[i], matRotY);
		rotX[i] = rotY[i];
		matrix->mulTriangleByMatrix(rotY[i], rotX[i], matRotX);

		rotX[i].a.z += 3.0f;
		rotX[i].b.z += 3.0f;
		rotX[i].c.z += 3.0f;

		rotX[i].a.x += 3.0f;
		rotX[i].b.x += 3.0f;
		rotX[i].c.x += 3.0f;

		rotX[i].a.x += 2.0f * cosf(fRotationX_) * sinf(fRotationY_);
		rotX[i].b.x += 2.0f * cosf(fRotationX_) * sinf(fRotationY_);
		rotX[i].c.x += 2.0f * cosf(fRotationX_) * sinf(fRotationY_);

		rotX[i].a.y += 1.0f * sinf(fRotationY_) * cosf(fRotationX_);
		rotX[i].b.y += 1.0f * sinf(fRotationY_) * cosf(fRotationX_);
		rotX[i].c.y += 1.0f * sinf(fRotationY_) * cosf(fRotationX_);

		/*rotX[i].a.z += 3.0f * sinf(fRotationY_) * cosf(fRotationX_);
		rotX[i].b.z += 3.0f * sinf(fRotationY_) * cosf(fRotationX_);
		rotX[i].c.z += 3.0f * sinf(fRotationY_) * cosf(fRotationX_);*/

		projectedTri[i] = rotX[i];
		matrix->mulTriangleByMatrix(
			rotX[i], projectedTri[i],
			matrix->projectionMatrix_);

		i++;
	}

	//scale
	for (auto& triPoint : projectedTri)
	{
		triPoint.a.x += 1.0f;
		triPoint.a.y += 1.0f;
		triPoint.b.x += 1.0f;
		triPoint.b.y += 1.0f;
		triPoint.c.x += 1.0f;
		triPoint.c.y += 1.0f;

		triPoint.a.x *= 0.5f * (float)scrnW_;
		triPoint.a.y *= 0.5f * (float)scrnH_;
		triPoint.b.x *= 0.5f * (float)scrnW_;
		triPoint.b.y *= 0.5f * (float)scrnH_;
		triPoint.c.x *= 0.5f * (float)scrnW_;
		triPoint.c.y *= 0.5f * (float)scrnH_;
	}

	//render
	for (; i >= 0; i--)
	{
		SDL_SetRenderDrawColor(sdlRenderer_,
			clrR_, clrG_, clrB_, clrA_);

		SDL_RenderDrawLine(
			sdlRenderer_,
			projectedTri[i].a.x, projectedTri[i].a.y,
			projectedTri[i].b.x, projectedTri[i].b.y);
		SDL_RenderDrawLine(
			sdlRenderer_,
			projectedTri[i].b.x, projectedTri[i].b.y,
			projectedTri[i].c.x, projectedTri[i].c.y);
		SDL_RenderDrawLine(
			sdlRenderer_,
			projectedTri[i].c.x, projectedTri[i].c.y,
			projectedTri[i].a.x, projectedTri[i].a.y);
	}
}