#include <cmath>

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