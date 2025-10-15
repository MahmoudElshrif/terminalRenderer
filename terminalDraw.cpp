#pragma once

#include <string>
#include <stack>
#include <vector>

using namespace std;

struct Screen
{
	string EMPTYDRAWBUFFER = "";
	int width = 640;
	int height = 128;
	string drawbuffer = "";
	std::vector<double> zbuffer;

	string chars = " `.-':_,^=;><+!rc*/z?sLTv)J7(|Fi{C}fI31tlu[neoZ5Yxjya]2ESwqkP6h9d4VpOGbUAKXHm8RD#$Bg0MNWQ%&@";
};

char get_character(Screen &screen, int brightness)
{
	int b = min(255, brightness);
	// return 0;
	return screen.chars[(b / 255.0) * (screen.chars.length() - 1)];
}

bool valid_position(int x, int y, int width, int height)
{
	if (x < 0 || y < 0 ||
		x >= width || y >= height)
	{
		return false;
	}
	return true;
}

void set_cell(Screen &screen, int x, int y, int symb, double z = 0)
{
	symb = min(max(symb, 0), 255);
	if (!valid_position(x, y, screen.width, screen.height))
	{
		return;
	}

	if (screen.zbuffer[x + y * screen.width] <= z)
	{
		screen.zbuffer[x + y * screen.width] = z;
		screen.drawbuffer[x + y * screen.width] = get_character(screen, symb);
	}
}

void set_cell_brightness(Screen &screen, int x, int y, int symb, double z = 0)
{
	symb = min(max(symb, 0), 255);
	if (!valid_position(x, y, screen.width, screen.height))
	{
		return;
	}

	if (screen.zbuffer[x + y * screen.width] <= z)
	{
		screen.zbuffer[x + y * screen.width] = z;
		screen.drawbuffer[x + y * screen.width] = get_character(screen, (char)symb);
	}
}

void clear_buffer(Screen &screen)
{
	screen.drawbuffer = screen.EMPTYDRAWBUFFER;
	screen.zbuffer = vector<double>(screen.width * screen.height);
}
void init_buffer(Screen &screen)
{
	printf("\033[2]j");
	screen.EMPTYDRAWBUFFER += string(screen.width * screen.height, ' ');
	screen.zbuffer = vector<double>(screen.width * screen.height);

	clear_buffer(screen);
}

void render_buffer(Screen &screen)
{
	for (int k = 0; k < screen.width * screen.height; k++)
	{
		putchar(k % screen.width ? screen.drawbuffer[k] : 10);
	}

	printf("\033[2]j");
	printf("\033[H");
}