#include <iostream>
#include <string>
#include <cmath>
#include <stack>
#include <vector>
#include <queue>
#include "utils.cpp"
#include <deque>
#include "terminalDraw.cpp"
#include "shapeDraw.cpp"

using namespace std;

int main()
{
	std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	Screen screen;
	init_buffer(screen);
	vector<double> position = {screen.width / 2., screen.height / 2.};
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

		clear_buffer(screen);
		lastposes.push_back(position);

		if (lastposes.size() > 10)
		{
			lastposes.pop_front();
		}

		v[1] += 9 * framerate;
		if (position[1] + rad + v[1] > screen.height)
		{
			v[1] = -v[1] * 0.999;
			position[1] = screen.height - rad;
		}
		if (position[1] + rad + v[1] < 0)
		{
			v[1] = -v[1];
		}

		if (position[0] + rad > screen.width)
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
			draw_circle(screen, i[0], i[1], 2, bright);
			bright += 10;
		}
		draw_circle(screen, position[0], position[1], 2);

		render_buffer(screen);
	}

	return 0;
}