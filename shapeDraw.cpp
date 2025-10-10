#pragma once

#include "terminalDraw.cpp"

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

void draw_square(Screen &screen, int x, int y, int width, int height, double stepsize = 0.4)
{
	for (double x = 0; x < width; x += stepsize)
	{
		for (double y = 0; y < height; x += stepsize)
		{
			set_cell(screen, (int)x, (int)y, '#');
		}
	}
}