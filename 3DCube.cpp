#include "terminalDraw.cpp"
#include <cmath>
#include <vector>
#include <iostream>
#include "utils.cpp"
#include "shapeDraw.cpp"

double calcX(double i, double j, double k, double A, double B, double C)
{
	return k * (sin(A) * sin(B) * cos(C) - cos(A) * sin(C)) +
		   i * (sin(A) * sin(B) * sin(C) + cos(A) * cos(C)) -
		   j * sin(A) * cos(B);
}

double calcY(double i, double j, double k, double A, double B, double C)
{
	return k * (-cos(A) * sin(B) * cos(C) - sin(A) * sin(C)) +
		   i * (sin(A) * cos(C) - cos(A) * sin(B) * sin(C)) +
		   j * cos(A) * cos(B);
}

double calcZ(double i, double j, double k, double A, double B, double C)
{
	return k * cos(B) * cos(C) +
		   i * cos(B) * sin(C) +
		   j * sin(B);
}

Vector2 project_on_surface(Screen &screen, Vector3 p)
{
	double fov = 1.0 / tan(90 / 2.0);

	double xp = fov * p.x / p.z;
	double yp = fov * p.y / p.z;

	double sx = (int)((xp + 1) * 0.5 * screen.width);
	double sy = (int)((yp + 1) * 0.5 * screen.height);

	return {sx, sy};
}

struct Mesh
{
	vector<Triangle3D> mesh;
};

const Mesh cube{
	// Mesh {vector {Triangle2D {Vector3}}}
	{
		// FRONT (+Z)
		{
			{-0.5, -0.5, 0.5},
			{-0.5, 0.5, 0.5},
			{0.5, 0.5, 0.5},
		},
		{
			{-0.5, -0.5, 0.5},
			{0.5, 0.5, 0.5},
			{0.5, -0.5, 0.5},
		},

		// BACK (-Z)
		{
			{0.5, 0.5, -0.5},
			{-0.5, 0.5, -0.5},
			{-0.5, -0.5, -0.5},
		},
		{
			{0.5, 0.5, -0.5},
			{-0.5, -0.5, -0.5},
			{0.5, -0.5, -0.5},
		},

		// LEFT (-X)
		{
			{-0.5, -0.5, -0.5},
			{-0.5, 0.5, -0.5},
			{-0.5, 0.5, 0.5},
		},
		{
			{-0.5, -0.5, -0.5},
			{-0.5, 0.5, 0.5},
			{-0.5, -0.5, 0.5},
		},

		// RIGHT (+X)
		{
			{0.5, -0.5, -0.5},
			{0.5, 0.5, 0.5},
			{0.5, 0.5, -0.5},
		},
		{
			{0.5, -0.5, -0.5},
			{0.5, -0.5, 0.5},
			{0.5, 0.5, 0.5},
		},

		// TOP (+Y)
		{
			{-0.5, 0.5, -0.5},
			{0.5, 0.5, -0.5},
			{0.5, 0.5, 0.5},
		},
		{
			{-0.5, 0.5, -0.5},
			{0.5, 0.5, 0.5},
			{-0.5, 0.5, 0.5},
		},

		// BOTTOM (-Y)
		{
			{-0.5, -0.5, -0.5},
			{0.5, -0.5, 0.5},
			{0.5, -0.5, -0.5},
		},
		{
			{-0.5, -0.5, -0.5},
			{-0.5, -0.5, 0.5},
			{0.5, -0.5, 0.5},
		},

	}};

Triangle2D
project_triangle_on_surface(Screen &screen, Triangle3D tri)
{
	return {
		project_on_surface(screen, tri.a),
		project_on_surface(screen, tri.b),
		project_on_surface(screen, tri.c)};
}

Vector3 rotate_point(Vector3 p, Vector3 rot)
{
	return {
		calcX(p.x, p.y, p.z, rot.x, rot.y, rot.z),
		calcY(p.x, p.y, p.z, rot.x, rot.y, rot.z),
		calcZ(p.x, p.y, p.z, rot.x, rot.y, rot.z),
	};
}

void draw_cube(Screen &screen, Vector3 pos, double size, Vector3 rot)
{

	for (Triangle3D i : cube.mesh)
	{
		i.a = rotate_point(i.a, rot);
		i.b = rotate_point(i.b, rot);
		i.c = rotate_point(i.c, rot);

		i.a = mult(i.a, size);
		i.b = mult(i.b, size);
		i.c = mult(i.c, size);

		i.a = add(i.a, pos);
		i.b = add(i.b, pos);
		i.c = add(i.c, pos);

		Vector3 normal = cross(i.b - i.a, i.c - i.a);

		if (normal.z < 0.)
			continue;

		draw_triangle(screen, project_triangle_on_surface(screen, i));
	}
	// for (double i = -size / 2; i < size / 2; i += stepsize)
	// {
	// 	for (double j = -size / 2; j < size / 2; j += stepsize)
	// 	{
	// 		vector<double> point;

	// 		point = {i, j, (double)-size / 2};
	// 		project_on_surface(screen, x + calcX(point[0], point[1], point[2], A, B, C), y + calcY(point[0], point[1], point[2], A, B, C), z + calcZ(point[0], point[1], point[2], A, B, C), '#');

	// 		point = {size / 2, j, i};
	// 		project_on_surface(screen, x + calcX(point[0], point[1], point[2], A, B, C), y + calcY(point[0], point[1], point[2], A, B, C), z + calcZ(point[0], point[1], point[2], A, B, C), 'K');

	// 		point = {-size / 2, j, -i};
	// 		project_on_surface(screen, x + calcX(point[0], point[1], point[2], A, B, C), y + calcY(point[0], point[1], point[2], A, B, C), z + calcZ(point[0], point[1], point[2], A, B, C), '/');

	// 		point = {-i, j, size / 2};
	// 		project_on_surface(screen, x + calcX(point[0], point[1], point[2], A, B, C), y + calcY(point[0], point[1], point[2], A, B, C), z + calcZ(point[0], point[1], point[2], A, B, C), '%');

	// 		point = {i, -size / 2, -j};
	// 		project_on_surface(screen, x + calcX(point[0], point[1], point[2], A, B, C), y + calcY(point[0], point[1], point[2], A, B, C), z + calcZ(point[0], point[1], point[2], A, B, C), '#');

	// 		point = {i, size / 2, j};
	// 		project_on_surface(screen, x + calcX(point[0], point[1], point[2], A, B, C), y + calcY(point[0], point[1], point[2], A, B, C), z + calcZ(point[0], point[1], point[2], A, B, C), '>');
	// 	}
	// }
}