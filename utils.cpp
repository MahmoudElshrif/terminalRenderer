#pragma once

#include <vector>
#include <cstdint>
#include <chrono>
#include <cmath>
#include "terminalDraw.cpp"

uint64_t timeSinceEpochMillisec()
{
	using namespace std::chrono;
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

std::vector<double> add(std::vector<double> v1, std::vector<double> v2)
{
	for (int i = 0; i < v1.size(); i++)
	{
		v1[i] += v2[i];
	}

	return v1;
}

struct Vector2
{
	double x;
	double y;

	Vector2 operator+(Vector2 v2)
	{
		return {x + v2.x, y + v2.y};
	}
	Vector2 operator-(Vector2 v2)
	{
		return {x - v2.x, y - v2.y};
	}
	Vector2 operator-()
	{
		return {-x, -y};
	}
	Vector2 operator*(Vector2 v2)
	{
		return {x * v2.x, y * v2.y};
	}
	Vector2 operator/(Vector2 v2)
	{
		return {x / v2.x, y / v2.y};
	}
	Vector2 operator*(double i)
	{
		return {x * i, y * i};
	}
	Vector2 operator/(double i)
	{
		return {x / i, y / i};
	}
};

struct Vector3
{
	double x;
	double y;
	double z;

	Vector3 operator+(Vector3 v2)
	{
		return {x + v2.x, y + v2.y, z + v2.z};
	}
	Vector3 operator-(Vector3 v2)
	{
		return {x - v2.x, y - v2.y, z - v2.z};
	}
	Vector3 operator-()
	{
		return {-x, -y, -z};
	}
	Vector3 operator*(Vector3 v2)
	{
		return {x * v2.x, y * v2.y, z * v2.z};
	}
	Vector3 operator/(Vector3 v2)
	{
		return {x / v2.x, y / v2.y, z / v2.z};
	}

	Vector3 operator*(double i)
	{
		return {x * i, y * i, z * i};
	}
	Vector3 operator/(double i)
	{
		return {x / i, y / i, z / i};
	}
};

struct Rect
{
	Vector2 pos;
	Vector2 size;
};

double distance(Vector2 v1, Vector2 v2)
{
	return sqrt(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2));
}

double distance_squared(Vector2 v1, Vector2 v2)
{
	return pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2);
}

void grow_to_fit(Rect &rect, Vector2 p)
{
	if (p.x < rect.pos.x)
	{
		rect.size.x += rect.pos.x - p.x;
		rect.pos.x = p.x;
	}
	if (p.y < rect.pos.y)
	{
		rect.size.y += rect.pos.y - p.y;
		rect.pos.y = p.y;
	}
	if (p.x > rect.pos.x + rect.size.x)
	{
		rect.size.x = p.x - rect.pos.x;
	}
	if (p.y > rect.pos.y + rect.size.y)
	{
		rect.size.y = p.y - rect.pos.y;
	}
}

void clip_rect_to_screen(Rect &rect, Screen &screen)
{
	rect.pos.x = max(0., rect.pos.x);
	rect.pos.y = max(0., rect.pos.y);
	rect.size.x = min(screen.width, (int)(rect.pos.x + rect.size.x)) - rect.pos.x;
	rect.size.y = min(screen.height, (int)(rect.pos.y + rect.size.y)) - rect.pos.y;
}

struct Triangle2D
{
	Vector2 a;
	Vector2 b;
	Vector2 c;
};

struct Triangle3D
{
	Vector3 a;
	Vector3 b;
	Vector3 c;
};

Triangle2D tri_3_to_2(Triangle3D v)
{
	return {{v.a.x, v.a.x}, {v.b.x, v.b.y}, {v.c.x, v.c.y}};
}

bool triangle_containes_point(Triangle2D tri, Vector2 p)
{
	Vector2 a = tri.a;
	Vector2 b = tri.b;
	Vector2 c = tri.c;
	double s = (a.x - c.x) * (p.y - c.y) - (a.y - c.y) * (p.x - c.x);
	double t = (b.x - a.x) * (p.y - a.y) - (b.y - a.y) * (p.x - a.x);

	if ((s < 0) != (t < 0) && s != 0 && t != 0)
	{
		return false;
	}

	double d = (c.x - b.x) * (p.y - b.y) - (c.y - b.y) * (p.x - b.x);
	return d == 0 || (d < 0) == (s + t <= 0);
}

Rect triangle_bounding_box(Triangle2D tri)
{
	Rect rect = {tri.a, {1., 1.}};
	grow_to_fit(rect, tri.b);
	grow_to_fit(rect, tri.c);
	return rect;
}

Vector2 add(Vector2 v1, Vector2 v2)
{
	return {
		v1.x + v2.x,
		v1.y + v2.y};
}

Vector3 add(Vector3 v1, Vector3 v2)
{
	return {
		v1.x + v2.x,
		v1.y + v2.y,
		v1.z + v2.z};
}

Vector2 mult(Vector2 v1, Vector2 v2)
{
	return {
		v1.x * v2.x,
		v1.y * v2.y};
}

Vector3 mult(Vector3 v1, Vector3 v2)
{
	return {
		v1.x * v2.x,
		v1.y * v2.y,
		v1.z * v2.z};
}

Vector2 mult(Vector2 v1, double a)
{
	return {
		v1.x * a,
		v1.y * a};
}

Vector3 mult(Vector3 v1, double a)
{
	return {
		v1.x * a,
		v1.y * a,
		v1.z * a};
}

double dot(Vector3 v1, Vector3 v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector3 cross(Vector3 v1, Vector3 v2)
{
	return {
		v1.y * v2.z - v2.z - v1.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x};
}

Vector3 normalize(Vector3 v)
{
	double len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	return v / len;
}