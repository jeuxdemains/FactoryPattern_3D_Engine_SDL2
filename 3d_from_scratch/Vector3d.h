#pragma once
#include <vector>

class Vector3d
{
public:
	struct Vector3
	{
		float x = 0.0f, y = 0.0f, z = 0.0f;
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

	Vector3 Cross(const Vector3& v1, const Vector3& v2) const
	{
		Vector3 cross;

		cross.x = v1.y * v2.z - v1.z * v2.y;
		cross.y = v1.z * v2.x - v1.x * v2.z;
		cross.z = v1.x * v2.y - v1.y * v2.x;

		return cross;
	}


	float Dot(const Vector3& v1, const Vector3& v2) const
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	Vector3 Normalize(const Vector3& v1)
	{
		Vector3 normalized;
		float ln = sqrtf(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z);
		normalized.x = v1.x / ln;
		normalized.y = v1.y / ln;
		normalized.z = v1.z / ln;

		return normalized;
	}

	bool IsZeroVec(const Vector3& v1)
	{
		if (v1.x == 0.0f && v1.y == 0.0f && v1.z == 0.0f)
			return true;

		return false;
	}
};

