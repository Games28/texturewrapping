#ifndef  DISPLAY_H
#define DISPLAY_H
#include <stdint.h>
#include "olcPixelGameEngine.h"


#define window_width 800
#define window_height 600



void draw_rect(olc::PixelGameEngine* pge, int x, int y, int width, int height, uint32_t color);
void draw_line(olc::PixelGameEngine* pge, int x0, int y0, int x1, int y1, uint32_t color);

#endif // ! DISPLAY_H


