#include "terminalDraw.cpp"
#include "3DCube.cpp"
#include "shapeDraw.cpp"

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
		// draw_cube(screen, 0, 0, 30, 10, A, B, C);
		// draw_cube(screen, -0.5, 0, 60, 10, A, B, C);
		// draw_circle(screen, screen.width / 2., screen.height / 2., 10);
		draw_triangle(screen, {screen.width / 2 - sin(A) * 4., screen.height / 2. + sin(A * 0.5) * 10}, {60, 10}, {100, 40});
		A += 0.007;
		B -= 0.009;
		C -= 0.005;
		render_buffer(screen);
	}

	return 1;
}