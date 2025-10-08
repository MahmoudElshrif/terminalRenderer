#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int width = 150;
int height = 50;
int refreshtick = 0;
int refreshtickmax = 1000;

string *buffer;

void clear_buffer(string *buffer)
{
	for (int i = 0; i < height; i++)
	{
		string s = string(width, ' ');
		buffer[i] = s;
	}
}
void init_buffer()
{
	buffer = new string[height];
	clear_buffer(buffer);
}

bool valid_position(int x, int y)
{
	if (x < 0 || y < 0 ||
		x > width || y > height)
	{
		return false;
	}
	return true;
}

void set_cell(string *buffer, int x, int y, char symb)
{
	if (!valid_position(x, y))
	{
		return;
	}

	buffer[y][x] = symb;
}

char get_cell(string *buffer, int x, int y)
{
	if (!valid_position(x, y))
	{
		return 0;
	}

	return buffer[y][x];
}

void render_buffer(string *buffer)
{
	string out = "";
	if (refreshtick <= 0)
	{
		out += "\033[2J";
		refreshtick = refreshtickmax;
	}
	refreshtick--;
	for (int i = 0; i < height; i++)
	{
		out += buffer[i] + '\n';
	}
	out += "\033[H";
	cout << out;
	cout.flush();
}

void draw_circle(string *buffer, int x, int y, int rad)
{
	for (int xf = max(0, x - rad); xf < min(width, x + rad + 1); xf++)
	{
		for (int yf = max(0, y - rad); yf < min(height, y + rad + 1); yf++)
		{
			if ((yf - y) * (yf - y) + (xf - x) * (xf - x) <= rad * rad)
				set_cell(buffer, xf, yf, 'f');
		}
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	init_buffer();
	double x = 0;
	while (true)
	{
		clear_buffer(buffer);
		x += 0.0005;
		draw_circle(buffer, cos(x) * 10 + width / 2, sin(x) * 4 + height / 2, 4);
		render_buffer(buffer);
	}

	return 0;
}