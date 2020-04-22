#pragma once
#include "Object3d.h"

class Object3dModel : public Object3d
{
public:
	Object3dModel(std::string fName, SDL_Renderer* sdlRndr,
		int scrnW, int scrnH, uint8_t alpha)
	{
		Object3dAdd(LoadModel(fName), sdlRndr, scrnW, scrnH, alpha);
	};

	~Object3dModel() {};

	Vector3d::Mesh LoadModel(std::string fileName) override
	{
		Vector3d::Mesh mesh;
		mesh.LoadFromObjFile(fileName);

		return mesh;
	}
};

