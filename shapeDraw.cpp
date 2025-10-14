#pragma once

#include <cmath>
#include "terminalDraw.cpp"
#include "utils.cpp"

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

void draw_triangle(Screen &screen, Triangle2D tri)
{
	Rect rect = triangle_bounding_box(tri);
	clip_rect_to_screen(rect, screen);
	for (int i = rect.pos.x; i < rect.pos.x + rect.size.x; i++)
	{
		for (int j = rect.pos.y; j < rect.pos.y + rect.size.y; j++)
		{
			if (triangle_containes_point(tri, {(double)i, (double)j}))
			{
				set_cell(screen, i, j, '#');
			}
		}
	}
}