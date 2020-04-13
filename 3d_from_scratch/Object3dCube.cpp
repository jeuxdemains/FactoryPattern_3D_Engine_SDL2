#include "Object3dCube.h"

Vector3d::Mesh Object3dCube::InitObject()
{
	Vector3d::Triangle tri1 =
	{
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f
	};

	Vector3d::Triangle tri2 =
	{
		0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f
	};

	Vector3d::Triangle tri3 =
	{
		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 1.0f
	};

	Vector3d::Triangle tri4 =
	{
		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f
	};

	Vector3d::Triangle tri5 =
	{
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f
	};

	Vector3d::Triangle tri6 =
	{
		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 0.0f
	};

	Vector3d::Triangle tri7 =
	{
		0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 1.0f
	};

	Vector3d::Triangle tri8 =
	{
		0.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f
	};

	Vector3d::Triangle tri9 =
	{
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	Vector3d::Triangle tri10 =
	{
		0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f
	};

	Vector3d::Triangle tri11 =
	{
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 1.0f,
	};

	Vector3d::Triangle tri12 =
	{
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f
	};

	Vector3d::Mesh obj, obj2;
	obj.triangles.push_back(tri1);
	obj.triangles.push_back(tri2);
	obj.triangles.push_back(tri3);
	obj.triangles.push_back(tri4);
	obj.triangles.push_back(tri5);
	obj.triangles.push_back(tri6);
	obj.triangles.push_back(tri7);
	obj.triangles.push_back(tri8);
	obj.triangles.push_back(tri9);
	obj.triangles.push_back(tri10);
	obj.triangles.push_back(tri11);
	obj.triangles.push_back(tri12);

	/*obj2 = obj;
	for (auto tri : obj2.triangles)
	{
		Vector3d::Triangle t;
		t = tri;
		t.a.x -= 1.0f;
		t.a.y -= 1.0f;
		t.a.z -= 1.0f;

		t.b.x -= 1.0f;
		t.b.y -= 1.0f;
		t.b.z -= 1.0f;

		t.c.x -= 1.0f;
		t.c.y -= 1.0f;
		t.c.z -= 1.0f;

		obj.triangles.push_back(t);
	}*/

	return obj;
}