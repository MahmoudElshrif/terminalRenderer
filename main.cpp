#include <iostream>
#include <string>
#include <cmath>
#include <stack>

using namespace std;

string EMPTYDRAWBUFFER = "";
int width = 620;
int height = 130;
int refreshtick = 0;
int refreshtickmax = 300;

string chars = " `.-':_,^=;><+!rc*/z?sLTv)J7(|Fi{C}fI31tlu[neoZ5Yxjya]2ESwqkP6h9d4VpOGbUAKXHm8RD#$Bg0MNWQ%&@";

int *buffer;
string drawbuffer = "";

stack<int> edited;

char get_character(int brightness)
{
	int b = min(255, brightness);
	// return 0;
	return chars[(b / 255.0) * (chars.length() - 1)];
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

void set_cell(int *buffer, int x, int y, int symb)
{
	symb = min(max(symb, 0), 255);
	if (!valid_position(x, y))
	{
		return;
	}

	edited.push(y * width + x);
	buffer[x + y * width] = symb;
}

int get_cell(int *buffer, int x, int y)
{
	if (!valid_position(x, y))
	{
		return 0;
	}

	return buffer[x + y * width];
}
void clear_buffer(int *buffer)
{
	fill(buffer, buffer + width * height, 0);
	// drawbuffer = EMPTYDRAWBUFFER;

	// if (edited.size() > 300)
	// {
	// 	for (int i = 0; i < width; i++)
	// 	{
	// 		fill(buffer[i], buffer[i] + height, 0);
	// 	}
	// }
	// else
	// {
	// 	while (!edited.empty())
	// 	{
	// 		int pos = edited.top();
	// 		buffer[pos % width][pos / width] = 0;
	// 		edited.pop();
	// 	}
	// }
}
void init_buffer()
{
	buffer = new int[width * height];

	for (int i = 0; i < height; i++)
	{
		EMPTYDRAWBUFFER += string(width, ' ');
	}
	clear_buffer(buffer);
}

void render_buffer(int *buffer)
{
	string out = "";
	refreshtick--;
	if (refreshtick > 0)
	{
		return;
	}
	out += "\033[2J";
	refreshtick = refreshtickmax;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			// cout << get_cell(buffer, i, j) << endl;
			out += get_character(get_cell(buffer, x, y));
		}
		out += '\n';
	}
	out += "\033[H";
	cout << out;
	cout.flush();
}

void draw_circle(int *buffer, int x, int y, int rad)
{
	for (int xf = max(0, x - rad * 2); xf < min(width, x + rad * 2 + 1); xf++)
	{
		for (int yf = max(0, y - rad); yf < min(height, y + rad + 1); yf++)
		{
			if ((yf - y) * (yf - y) + (xf - x) * (xf - x) / 4 <= rad * rad)
				set_cell(buffer, xf, yf, 100);
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
		x += 0.0004;
		draw_circle(buffer, cos(x) * 30 + width / 2, sin(x) * 15 + height / 2, 30);
		render_buffer(buffer);
	}

	return 0;
}