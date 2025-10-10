#include "terminalDraw.cpp"
#include "shapeDraw.cpp"

int main()
{
	Screen screen;

	while (true)
	{
		clear_buffer(screen);
		draw_square(screen, 40, 40, 100, 40);
		render_buffer(screen);
	}
}