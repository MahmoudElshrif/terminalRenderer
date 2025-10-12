#pragma once

#include <cmath>
#include "terminalDraw.cpp"
#include "vector.cpp"

void draw_circle(Screen &screen, int x, int y, int rad, int bright = 254)
{
	for (int xf = max(0, x - rad * 8); xf < min(screen.width, x + rad * 8 + 1); xf++)
	{
		for (int yf = max(0, y - rad); yf < min(screen.height, y + rad + 1); yf++)
		{
			if ((yf - y) * (yf - y) + (xf - x) * (xf - x) / 8 <= rad * rad)
				set_cell_brightness(screen, xf, yf, bright - 127);
		}
	}
}

double calcX(double i, double j, double ang)
{
	return i * cos(ang) - j * sin(ang);
}

double calcY(double i, double j, double ang)
{
	return i * +sin(ang) + j * cos(ang);
}

void draw_rect(Screen &screen, double x, double y, double width, double height)
{

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			set_cell(screen, x + i, y + j, '#');
		}
	}
}

void draw_rect(Screen &screen, double x, double y, double width, double height, double ang, double stepsize = 0.75)
{

	for (double i = -width / 2; i < width / 2; i += stepsize)
	{
		for (double j = -height / 2; j < height / 2; j += stepsize)
		{
			set_cell(screen, x + calcX(i, j, ang), y + calcY(i, j, ang), '#');
		}
	}
}

void draw_triangle(Screen &screen, Vector2 a, Vector2 b, Vector2 c)
{
	Rect rect = {a, {1., 1.}};
	grow_to_fit(rect, b);
	grow_to_fit(rect, c);
	clip_rect_to_screen(rect, screen);
	double firstdom = (b.y - a.y) * (c.x - a.x) - (b.x - a.x) * (c.y - a.y);
	double seconddom = c.y - a.y;
	for (int i = rect.pos.x; i < rect.pos.x + rect.size.x; i++)
	{
		for (int j = rect.pos.y; j < rect.pos.y + rect.size.y; j++)
		{
			Vector2 p = {i, j};
			double w1 = (a.x * (c.y - a.y) + (p.y - a.y) * (c.x - a.x) - p.x * (c.y - a.y)) / firstdom;
			if (w1 < 0)
				continue;
			double w2 = (p.y - a.y - w1 * (b.y - a.y)) / seconddom;
			if (w2 < 0)
				continue;
			if (w1 + w2 > 1.)
				continue;

			set_cell(screen, i, j, '#');
		}
	}
	// draw_rect(screen, rect.pos.x, rect.pos.y, rect.size.x, rect.size.y);
	// draw_circle(screen, a.x, a.y, 2);
	// draw_circle(screen, b.x, b.y, 2);
	// draw_circle(screen, c.x, c.y, 2);
}