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
};

struct Vector3
{
	double x;
	double y;
	double z;
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

struct Triangle
{
	Vector2 a;
	Vector2 b;
	Vector2 c;
};

bool triangle_containes_point(Triangle &tri, Vector2 p)
{
	Vector2 a = tri.a;
	Vector2 b = tri.b;
	Vector2 c = tri.c;

	double firstdom = (b.y - a.y) * (c.x - a.x) - (b.x - a.x) * (c.y - a.y);
	double seconddom = c.y - a.y;

	double w1 = (a.x * (c.y - a.y) + (p.y - a.y) * (c.x - a.x) - p.x * (c.y - a.y)) / firstdom;
	if (w1 < 0)
		return false;
	double w2 = (p.y - a.y - w1 * (b.y - a.y)) / seconddom;
	if (w2 < 0)
		return false;
	if (w1 + w2 > 1.)
		return false;

	return true;
}

Rect triangle_bounding_box(Triangle &tri)
{
	Rect rect = {tri.a, {1., 1.}};
	grow_to_fit(rect, tri.b);
	grow_to_fit(rect, tri.c);
	return rect;
}