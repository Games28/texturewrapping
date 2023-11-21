#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "Vector.h"
#include "olcPixelGameEngine.h"
#include "Display.h"

typedef struct
{
	int a;
	int b;
	int c;
	
	uint32_t color;

}Face_t;

typedef struct
{
	Vec2_t points[3];
	uint32_t color;

}Triangle_t;

void swap(int* a, int* b);
void draw_triangle(olc::PixelGameEngine* pge, int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
void draw_filled_triangle(olc::PixelGameEngine* pge, int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);

void fill_flat_bottom_triangle(olc::PixelGameEngine* pge, int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
void fill_flat_top_triangle(olc::PixelGameEngine* pge, int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
#endif // !TRIANGLE_H


