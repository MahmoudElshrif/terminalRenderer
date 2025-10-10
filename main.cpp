#include "terminalDraw.cpp"
#include "3DCube.cpp"

int main()
{
	Screen screen;

	init_buffer(screen);
	double A = 0;
	double B = 0.4;
	double C = 1.2;

	while (true)
	{
		clear_buffer(screen);
		draw_cube(screen, 0, 0, 10, 10, A, B, C);
		A += 0.007;
		B -= 0.009;
		C -= 0.005;
		render_buffer(screen);
	}

	return 1;
}