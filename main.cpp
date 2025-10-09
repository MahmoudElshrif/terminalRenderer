#include <iostream>
#include <string>
#include <cmath>
#include <stack>
#include <vector>
#include <queue>
#include "utils.cpp"
#include <deque>

using namespace std;

string EMPTYDRAWBUFFER = "";
int width = 620;
int height = 130;
;

string chars = " `.-':_,^=;><+!rc*/z?sLTv)J7(|Fi{C}fI31tlu[neoZ5Yxjya]2ESwqkP6h9d4VpOGbUAKXHm8RD#$Bg0MNWQ%&@";

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

void set_cell(int x, int y, int symb)
{
	symb = min(max(symb, 0), 255);
	if (!valid_position(x, y))
	{
		return;
	}

	edited.push(y * width + x);

	drawbuffer[x + y * width] = get_character((char)symb);
}

void clear_buffer()
{
	drawbuffer = EMPTYDRAWBUFFER;
}
void init_buffer()
{
	printf("\033[2]j");
	for (int i = 0; i < height; i++)
	{
		EMPTYDRAWBUFFER += string(width, ' ');
	}

	clear_buffer();
}

void render_buffer()
{
	for (int k = 0; k < width * height; k++)
	{
		if (k < width || k < height - width)
		{
			putchar('#');
		}
		else
		{
			putchar(k % width ? drawbuffer[k] : 10);
		}
	}

	printf("\033[H");
}

void draw_circle(int x, int y, int rad, int bright = 254)
{
	for (int xf = max(0, x - rad * 8); xf < min(width, x + rad * 8 + 1); xf++)
	{
		for (int yf = max(0, y - rad); yf < min(height, y + rad + 1); yf++)
		{
			if ((yf - y) * (yf - y) + (xf - x) * (xf - x) / 8 <= rad * rad)
				set_cell(xf, yf, bright - 127);
		}
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	init_buffer();
	vector<double> position = {width / 2., height / 2.};
	vector<double> v = {3, 0};
	int rad = 5;
	auto lastframe = timeSinceEpochMillisec();
	auto frame = timeSinceEpochMillisec();

	double framerate = 1 / 120.;
	deque<vector<double>> lastposes = {};

	while (true)
	{
		frame = timeSinceEpochMillisec();
		double delta = (frame - lastframe) / 1000.;
		if (delta < framerate)
		{
			continue;
		}
		lastframe = frame;

		clear_buffer();
		lastposes.push_back(position);

		if (lastposes.size() > 10)
		{
			lastposes.pop_front();
		}

		v[1] += 9 * framerate;
		if (position[1] + rad + v[1] > height)
		{
			v[1] = -v[1] * 0.999;
			position[1] = height - rad;
		}
		if (position[1] + rad + v[1] < 0)
		{
			v[1] = -v[1];
		}

		if (position[0] + rad > width)
		{
			v[0] = -v[0];
		}

		if (position[0] - rad < 0)
		{
			v[0] = -v[0];
		}
		position = add(position, v);

		int bright = 100;
		for (auto i : lastposes)
		{
			draw_circle(i[0], i[1], 2, bright);
			bright += 10;
		}
		draw_circle(position[0], position[1], 2);

		render_buffer();
	}

	return 0;
}