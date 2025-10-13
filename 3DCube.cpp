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

struct Triangle3D
{
	Vector3 a;
	Vector3 b;
	Vector3 c;
};

Triangle2D project_triangle_on_surface(Screen &screen, Triangle3D tri)
{
	return {
		project_on_surface(screen, tri.a),
		project_on_surface(screen, tri.b),
		project_on_surface(screen, tri.c)};
}

void draw_cube(Screen &screen, int x, int y, int z, double size, double A = 0, double B = 0, double C = 0, double stepsize = 0.3)
{
	stepsize *= z / 60.;

	Triangle3D t1 = {
		{x - size / 2., y - size / 2., z + size / 2.},
		{x - size / 2., y + size / 2., z + size / 2.},
		{x + size / 2., y + size / 2., z + size / 2.},
	};
	Triangle3D t2 = {
		{x - size / 2., y - size / 2., z + size / 2.},
		{x + size / 2., y + size / 2., z + size / 2.},
		{x + size / 2., y - size / 2., z + size / 2.},
	};

	draw_triangle(screen, project_triangle_on_surface(screen, t1));
	draw_triangle(screen, project_triangle_on_surface(screen, t2));
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