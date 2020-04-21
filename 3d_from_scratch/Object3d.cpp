#include "Object3d.h"

Object3d::~Object3d()
{
	delete matrix;
}

void Object3d::Update()
{
	fRotationX_ += 1.0f * 0.01f;
	fRotationY_ += 1.0f * 0.03f;
	fRotationZ_ += 1.0f * 0.05f;

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
	Matrix::Matrix4 const transMat = 
		matrix->makeTranslateMatrix(0.0f, -0.5f, 0.0f);

	Vector3d::Triangle
		projectedTri[24],
		rotX[24],
		rotY[24],
		rotZ[24],
		transX[24];

	Vector3d* v3d = new Vector3d();
	int i = 0;
	for (auto triangle : objects_[0].triangles)
	{
		rotZ[i] = triangle;
		matrix->mulTriangleByMatrix(triangle, rotZ[i], matRotZ);
		rotY[i] = rotZ[i];
		matrix->mulTriangleByMatrix(rotZ[i], rotY[i], matRotY);
		rotX[i] = rotY[i];
		matrix->mulTriangleByMatrix(rotY[i], rotX[i], matRotX);
		transX[i] = rotX[i];
		//matrix->mulTriangleByMatrix(rotX[i], transX[i], transMat);

		SDL_GetRendererOutputSize(sdlRenderer_, &scrnW_, &scrnH_);

		transX[i].a.z += 8.0f * scrnH_ / scrnW_;
		transX[i].b.z += 8.0f * scrnH_ / scrnW_;
		transX[i].c.z += 8.0f * scrnH_ / scrnW_;

		/*rotX[i].a.x += 3.0f;
		rotX[i].b.x += 3.0f;
		rotX[i].c.x += 3.0f;*/

		transX[i].a.x += 1.5f * cosf(fRotationX_) * sinf(fRotationY_);
		transX[i].b.x += 1.5f * cosf(fRotationX_) * sinf(fRotationY_);
		transX[i].c.x += 1.5f * cosf(fRotationX_) * sinf(fRotationY_);

		transX[i].a.y += 1.5f * sinf(fRotationX_) * cosf(fRotationY_);
		transX[i].b.y += 1.5f * sinf(fRotationX_) * cosf(fRotationY_);
		transX[i].c.y += 1.5f * sinf(fRotationX_) * cosf(fRotationY_);

		//rotX[i].a.z += 3.0f * sinf(fRotationY_) * cosf(fRotationX_);
		//rotX[i].b.z += 3.0f * sinf(fRotationY_) * cosf(fRotationX_);
		//rotX[i].c.z += 3.0f * sinf(fRotationY_) * cosf(fRotationX_);

		if (IsFrontFace(transX[i]))
		{
			projectedTri[i] = transX[i];
			matrix->mulTriangleByMatrix(
				transX[i], projectedTri[i],
				matrix->projectionMatrix_);

			i++;
		}
	}

	i--;

	//render
	SDL_SetRenderDrawColor(sdlRenderer_,
		clrR_, clrG_, clrB_, clrA_);

	for (; i >= 0; i--)
	{
		projectedTri[i].a.x += 1.0f;
		projectedTri[i].a.y += 1.0f;
		projectedTri[i].b.x += 1.0f;
		projectedTri[i].b.y += 1.0f;
		projectedTri[i].c.x += 1.0f;
		projectedTri[i].c.y += 1.0f;

		projectedTri[i].a.x *= 0.5f * (float)scrnW_;
		projectedTri[i].a.y *= 0.5f * (float)scrnH_;
		projectedTri[i].b.x *= 0.5f * (float)scrnW_;
		projectedTri[i].b.y *= 0.5f * (float)scrnH_;
		projectedTri[i].c.x *= 0.5f * (float)scrnW_;
		projectedTri[i].c.y *= 0.5f * (float)scrnH_;

		FillPolygon(projectedTri[i]);

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

	delete v3d;
}