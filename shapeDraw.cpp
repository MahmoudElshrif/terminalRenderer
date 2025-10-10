#pragma once

#include "terminalDraw.cpp"
#include <cmath>

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

void draw_square(Screen &screen, int x, int y, int width, int height, double ang = 0, double stepsize = 0.75)
{

	for (double i = -width / 2; i < width / 2; i += stepsize)
	{
		for (double j = -height / 2; j < height / 2; j += stepsize)
		{
			set_cell(screen, x + calcX(i, j, ang), y + calcY(i, j, ang), '#');
		}
	}
}
