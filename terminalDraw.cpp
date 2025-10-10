#pragma once

#include <string>
#include <stack>

using namespace std;

struct Screen
{
	string EMPTYDRAWBUFFER = "";
	int width = 620;
	int height = 130;
	string drawbuffer = "";

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
		x > width || y > height)
	{
		return false;
	}
	return true;
}

void set_cell(Screen &screen, int x, int y, int symb)
{
	symb = min(max(symb, 0), 255);
	if (!valid_position(x, y, screen.width, screen.height))
	{
		return;
	}

	screen.drawbuffer[x + y * screen.width] = (char)symb;
}

void set_cell_brightness(Screen &screen, int x, int y, int symb)
{
	symb = min(max(symb, 0), 255);
	if (!valid_position(x, y, screen.width, screen.height))
	{
		return;
	}

	screen.drawbuffer[x + y * screen.width] = get_character(screen, (char)symb);
}

void clear_buffer(Screen &screen)
{
	screen.drawbuffer = screen.EMPTYDRAWBUFFER;
}
void init_buffer(Screen &screen)
{
	printf("\033[2]j");
	for (int i = 0; i < screen.height; i++)
	{
		screen.EMPTYDRAWBUFFER += string(screen.width, ' ');
	}

	clear_buffer(screen);
}

void render_buffer(Screen &screen)
{
	printf("\033[2]j");
	for (int k = 0; k < screen.width * screen.height; k++)
	{
		putchar(k % screen.width ? screen.drawbuffer[k] : 10);
	}

	printf("\033[H");
}