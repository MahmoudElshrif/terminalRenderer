#include <iostream>
#include <string>

using namespace std;

int width = 100;
int height = 30;
int refreshtick = 0;
int refreshtickmax = 1000;

string *buffer;

void init_buffer()
{
	buffer = new string[height];
	for (int i = 0; i < height; i++)
	{
		string s = string(width, 'h');
		buffer[i] = s;
	}
}

bool valid_position(int x, int y)
{
	if (x < 0 || y < 0 ||
		x >= width || y >= height)
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
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	init_buffer();
	while (true)
	{
		render_buffer(buffer);
	}

	return 0;
}