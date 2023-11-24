#ifndef VECTOR_H
#define VECTOR_H
#include <math.h>

typedef struct
{
	float x;
	float y;
}vec2_t;

typedef struct
{
	float x;
	float y;
	float z;
}vec3_t;

typedef struct {
	float x; 
	float y; 
	float z;
	float w;
} vec4_t;


//Vec2
float Vec2_length(vec2_t v);
vec2_t Vec2_add(vec2_t a, vec2_t b);
vec2_t Vec2_sub(vec2_t a, vec2_t b);
vec2_t Vec2_multi(vec2_t a, float factor);
vec2_t Vec2_div(vec2_t a, float factor);
float Vec2_dot(vec2_t a, vec2_t b);
void Vec2_normalize(vec2_t* v);
float Vec2_mag(vec2_t a, vec2_t b);

//Vec3
float Vec3_length(vec3_t v);
vec3_t Vec3_add(vec3_t a, vec3_t b);
vec3_t Vec3_sub(vec3_t a, vec3_t b);
vec3_t Vec3_multi(vec3_t a, float factor);
vec3_t Vec3_div(vec3_t a, float factor);
vec3_t Vec3_cross(vec3_t a, vec3_t b);
float Vec3_dot(vec3_t a, vec3_t b);
void Vec3_normalize(vec3_t* v);

vec3_t Vec3_rotate_x(vec3_t v, float angle);

vec3_t Vec3_rotate_y(vec3_t v, float angle);

vec3_t Vec3_rotate_z(vec3_t v, float angle);

//Vec4
vec4_t vec4_from_vec3(vec3_t v);
vec3_t vec3_from_vec4(vec4_t v);
vec2_t vec2_from_vec4(vec4_t v);
vec2_t& Vec2_from_vec4(vec4_t& v);

float Vec4_mag(vec4_t a, vec4_t b);
float V4_mag(vec4_t a, vec2_t b);

#endif // !VECTOR_H


