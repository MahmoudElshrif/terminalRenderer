#include "terminalDraw.cpp"
#include <cmath>
#include <vector>
#include <iostream>

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

void project_on_surface(Screen &screen, double x, double y, double z, char symb)
{
	double fov = 1.0 / tan(90 / 2.0);
	if (z < fov)
	{
		return;
	}
	double xp = fov * x / z;
	double yp = fov * y / z;

	int sx = (int)((xp + 1) * 0.5 * screen.width);
	int sy = (int)((yp + 1) * 0.5 * screen.height);
	if (!valid_position(sx, sy, screen.width, screen.height))
	{
		return;
	}
	// std::cout << sx << std::endl;
	if (screen.zbuffer[sx + sy * screen.width] < 1 / z)
	{
		screen.zbuffer[sx + sy * screen.width] = 1 / z;
		set_cell(screen, sx, sy, symb);
	}
}

struct Triangle3D
{
};

void draw_cube(Screen &screen, int x, int y, int z, double size, double A = 0, double B = 0, double C = 0, double stepsize = 0.3)
{
	stepsize *= z / 60.;
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