#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "Vector.h"
#include "olcPixelGameEngine.h"
#include "Display.h"
#include "Texture.h"

typedef struct
{
	int a;
	int b;
	int c;
	Tex2_t a_uv;
	Tex2_t b_uv;
	Tex2_t c_uv;
	uint32_t color;

}Face_t;

typedef struct
{
	
	vec4_t pointsv4[3];
	
	Tex2_t texcoords[3];
	
	uint32_t color;
	float avg_depth;
	
	
}Triangle_t;



void int_swap(int* a, int* b);
void float_swap(float* a, float* b);


void draw_textured_triangle(
	olc::PixelGameEngine* pge,
	int x0, int y0,float z0, float w0, float u0, float v0,
	int x1, int y1,float z1, float w1, float u1, float v1,
	int x2, int y2,float z2, float w2, float u2, float v2,
	uint32_t* color
);

vec3_t barycentric_weights(vec2_t a, vec2_t b, vec2_t c, vec2_t p);



void draw_texel(olc::PixelGameEngine* pge,
	int x, int y, uint32_t* texture,
	vec4_t point_a, vec4_t point_b, vec4_t point_c,
	Tex2_t a_uv, Tex2_t b_uv, Tex2_t c_uv);
#endif // !TRIANGLE_H


