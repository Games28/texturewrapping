#ifndef VECTOR_H
#define VECTOR_H
#include <math.h>

typedef struct
{
	float x;
	float y;
}Vec2_t;

typedef struct
{
	float x;
	float y;
	float z;
}Vec3_t;

float Vec2_length(Vec2_t v);
Vec2_t Vec2_add(Vec2_t a, Vec2_t b);
Vec2_t Vec2_sub(Vec2_t a, Vec2_t b);
Vec2_t Vec2_multi(Vec2_t a, float factor);
Vec2_t Vec2_div(Vec2_t a, float factor);
float Vec2_dot(Vec2_t a, Vec2_t b);
void Vec2_normalize(Vec2_t* v);
float Vec2_mag(Vec2_t a, Vec2_t b);


float Vec3_length(Vec3_t v);
Vec3_t Vec3_add(Vec3_t a, Vec3_t b);
Vec3_t Vec3_sub(Vec3_t a, Vec3_t b);
Vec3_t Vec3_multi(Vec3_t a, float factor);
Vec3_t Vec3_div(Vec3_t a, float factor);
Vec3_t Vec3_cross(Vec3_t a, Vec3_t b);
float Vec3_dot(Vec3_t a, Vec3_t b);
void Vec3_normalize(Vec3_t* v);

Vec3_t Vec3_rotate_x(Vec3_t v, float angle);

Vec3_t Vec3_rotate_y(Vec3_t v, float angle);

Vec3_t Vec3_rotate_z(Vec3_t v, float angle);
#endif // !VECTOR_H


