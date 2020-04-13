#pragma once
#include <vector>

class Vector3d
{
public:
	struct Vector3
	{
		float x, y, z;
	};

	struct Triangle
	{
		Vector3 a, b, c;
		uint8_t red = 255, green = 20, blue = 0;
	};

	struct Mesh
	{
		std::vector<Triangle> triangles;
	};
};

