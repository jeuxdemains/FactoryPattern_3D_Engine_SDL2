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

	clrR_ = abs(160 * cos(fRotationX_) * 1.5);
	clrG_ = abs(160 * cos(fRotationY_) * 1.5);
	clrB_ = abs(160 * cos(fRotationZ_) * 1.5);

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
	Matrix::Matrix4 const scaleMat = 
		matrix->setScaleMatrix(1.0f, 1.0f, 1.0f);
	Matrix::Matrix4 const transMat =
		matrix->setTranslateMatrix(0.0f, 0.0f, 0.0f);

	const int vertCount = 7;
	Vector3d::Triangle
		projectedTri[vertCount],
		rotX[vertCount],
		rotY[vertCount],
		rotZ[vertCount],
		transX[vertCount],
		scale[vertCount];

	Vector3d* v3d = new Vector3d();
	int i = 0;
	for (auto triangle : objects_[0].triangles)
	{
		scale[i] = triangle;
		matrix->mulTriangleByMatrix(triangle, scale[i], scaleMat);
		rotZ[i] = scale[i];
		matrix->mulTriangleByMatrix(scale[i], rotZ[i], matRotZ);
		rotY[i] = rotZ[i];
		matrix->mulTriangleByMatrix(rotZ[i], rotY[i], matRotY);
		rotX[i] = rotY[i];
		matrix->mulTriangleByMatrix(rotY[i], rotX[i], matRotX);
		transX[i] = rotX[i];
		matrix->mulTriangleByMatrix(rotX[i], transX[i], transMat);

		transX[i].a.z += 14.0f;
		transX[i].b.z += 14.0f;
		transX[i].c.z += 14.0f;

		SDL_GetRendererOutputSize(sdlRenderer_, &scrnW_, &scrnH_);
		/*transX[i].a.x += scrnW_ / scrnH_;
		transX[i].b.x += scrnW_ / scrnH_;
		transX[i].c.x += scrnW_ / scrnH_;*/

		transX[i].a.x += 2.5f * cosf(fRotationX_ * 2);
		transX[i].b.x += 2.5f * cosf(fRotationX_ * 2);
		transX[i].c.x += 2.5f * cosf(fRotationX_ * 2);

		transX[i].a.y += 3.5f * sinf(fRotationX_ * 2);
		transX[i].b.y += 3.5f * sinf(fRotationX_ * 2);
		transX[i].c.y += 3.5f * sinf(fRotationX_ * 2);

		transX[i].a.z -= 6.5f * cosf(fRotationX_ * 1.5);
		transX[i].b.z -= 6.5f * cosf(fRotationX_ * 1.5);
		transX[i].c.z -= 6.5f * cosf(fRotationX_ * 1.5);

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