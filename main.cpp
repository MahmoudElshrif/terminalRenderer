#include "terminalDraw.cpp"
#include "3DCube.cpp"
#include "shapeDraw.cpp"

int main()
{
	Screen screen;
	// screen.width = 3200;
	// screen.height = 170;
	init_buffer(screen);
	double A = 0;
	double B = 0.4;
	double C = 1.2;
	std::cout << "\033[?25l";

	while (true)
	{
		clear_buffer(screen);
		// draw_cube(screen, 0, 0, 30, 10, A, B, C);
		// draw_cube(screen, -0.5, 0, 60, 10, A, B, C);
		// draw_circle(screen, screen.width / 2., screen.height / 2., 10);
		Triangle tri = {
			{screen.width / 2 - sin(A) * 4., screen.height / 2. + sin(A * 0.5) * 10}, {60 - sin(B * 0.3) * 40, 10 + cos(B * 3) * 2}, {100 + cos(C * 0.7) * 130, 40 - sin(C * 0.1)}};
		draw_triangle(screen, tri);
		A += 0.007;
		B -= 0.009;
		C -= 0.005;
		render_buffer(screen);
	}

	return 1;
}