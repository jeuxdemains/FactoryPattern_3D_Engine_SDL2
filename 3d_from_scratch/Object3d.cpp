#include "Object3d.h"

Object3d::~Object3d()
{
	delete matrix;
}

void Object3d::Update()
{
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

		rotX[i].a.z += 3.0f;
		rotX[i].b.z += 3.0f;
		rotX[i].c.z += 3.0f;

		/*rotX[i].a.x += 3.0f;
		rotX[i].b.x += 3.0f;
		rotX[i].c.x += 3.0f;*/

		rotX[i].a.x += 2.0f * cosf(fRotationX_) * sinf(fRotationY_);
		rotX[i].b.x += 2.0f * cosf(fRotationX_) * sinf(fRotationY_);
		rotX[i].c.x += 2.0f * cosf(fRotationX_) * sinf(fRotationY_);

		rotX[i].a.y += 1.0f * sinf(fRotationY_) * cosf(fRotationX_);
		rotX[i].b.y += 1.0f * sinf(fRotationY_) * cosf(fRotationX_);
		rotX[i].c.y += 1.0f * sinf(fRotationY_) * cosf(fRotationX_);

		//rotX[i].a.z += 3.0f * sinf(fRotationY_) * cosf(fRotationX_);
		//rotX[i].b.z += 3.0f * sinf(fRotationY_) * cosf(fRotationX_);
		//rotX[i].c.z += 3.0f * sinf(fRotationY_) * cosf(fRotationX_);


		//back-face culling
		Vector3d::Vector3 line1, line2;
		line1.x = rotX[i].b.x - rotX[i].a.x;
		line1.y = rotX[i].b.y - rotX[i].a.y;
		line1.z = rotX[i].b.z - rotX[i].a.z;

		line2.x = rotX[i].c.x - rotX[i].a.x;
		line2.y = rotX[i].c.y - rotX[i].a.y;
		line2.z = rotX[i].c.z - rotX[i].a.z;

		Vector3d::Vector3 cross = v3d->Cross(line1, line2);
		Vector3d::Vector3 normal, cam;
		normal = v3d->Normalize(cross);

		cam.x = rotX[i].a.x - 0.0f;
		cam.y = rotX[i].a.y - 0.0f;
		cam.z = rotX[i].a.z - 0.0f;

		float dot = v3d->Dot(normal, cam);
		if (dot < 0.0f)
		{
			projectedTri[i] = rotX[i];
			matrix->mulTriangleByMatrix(
				rotX[i], projectedTri[i],
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