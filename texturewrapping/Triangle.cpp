#include "Triangle.h"

void swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void draw_triangle(olc::PixelGameEngine* pge, int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color)
{
	draw_line(pge, x0, y0, x1, y1, color);
	draw_line(pge, x1, y1, x2, y2, color);
	draw_line(pge, x2, y2, x0, y0, color);

}

void draw_filled_triangle(olc::PixelGameEngine* pge, int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color)
{
	if (y0 > y1)
	{
		swap(&y0, &y1);
		swap(&x0, &x1);
	}
	if (y1 > y2)
	{
		swap(&y1, &y2);
		swap(&x1, &x2);
	}
	
	if (y0 > y1)
	{
		swap(&y0, &y1);
		swap(&x0, &x1);
	}

	if (y1 == y2)
	{
		fill_flat_bottom_triangle(pge,x0, y0, x1, y1, x2, y2, color);
	}
	else if (y0 == y1)
	{
		fill_flat_top_triangle(pge,x0, y0, x1, y1, x2, y2, color);
	}
	else
	{
        int My = y1;
		int Mx = (((x2 - x0) * (y1 - y0)) / (y2 - y0)) + x0;

		fill_flat_bottom_triangle(pge, x0, y0, x1, y1, Mx, My, color);
		fill_flat_top_triangle(pge, x1, y1, Mx, My, x2, y2, color);
	}
}

void fill_flat_bottom_triangle(olc::PixelGameEngine* pge, int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color)
{
	float inv_slope_1 = (float)(x1 - x0) / (y1 - y0);
	float inv_slope_2 = (float)(x2 - x0) / (y2 - y0);

	float x_start = x0;
	float x_end = x0;

	for (int y = y0; y <= y2; y++)
	{
		draw_line(pge,x_start, y, x_end, y, color);
		x_start += inv_slope_1;
		x_end += inv_slope_2;

	}
}

void fill_flat_top_triangle(olc::PixelGameEngine* pge, int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color)
{
	float inv_slope_1 = (float)(x2 - x0) / (y2 - y0);
	float inv_slope_2 = (float)(x2 - x1) / (y2 - y1);

	float x_start = x2;
	float x_end = x2;

	for (int y = y2; y >= y0; y--)
	{
		draw_line(pge,x_start, y, x_end, y,color);
		x_start -= inv_slope_1;
		x_end -= inv_slope_2;
	}
}

