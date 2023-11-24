#include "Vector.h"

float Vec2_length(vec2_t v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}

vec2_t Vec2_add(vec2_t a, vec2_t b)
{
	vec2_t result = {
		a.x + b.x,
		a.y + b.y
	};

	return result;
}

vec2_t Vec2_sub(vec2_t a, vec2_t b)
{
	vec2_t result = {
		a.x - b.x,
		a.y - b.y
	};

	return result;
}

vec2_t Vec2_multi(vec2_t a, float factor)
{
	vec2_t result = {
		a.x * factor,
		a.y * factor
	};

	return result;
}

vec2_t Vec2_div(vec2_t a, float factor)
{
	vec2_t result = {
		a.x / factor,
		a.y / factor
	};

	return result;
}

float Vec2_dot(vec2_t a, vec2_t b)
{
	return (a.x * b.x) + (a.y * b.y);
}

void Vec2_normalize(vec2_t* v)
{
	float length = sqrt(v->x * v->x + v->y * v->y);

	v->x /= length;
	v->y /= length;
}

float Vec2_mag(vec2_t a, vec2_t b)
{
	vec2_t result;
	result.x = a.x - b.x;
	result.y = a.y - b.y;

	return sqrtf(result.x * result.x + result.y * result.y);;
}



float Vec3_length(vec3_t v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);


}

vec3_t Vec3_add(vec3_t a, vec3_t b)
{
	vec3_t result = {
		a.x + b.x,
		a.y + b.y,
		a.z + b.z
	};

	return result;
}

vec3_t Vec3_sub(vec3_t a, vec3_t b)
{
	vec3_t result = {
		a.x - b.x,
		a.y - b.y,
		a.z - b.z
	};

	return result;
}

vec3_t Vec3_multi(vec3_t a, float factor)
{
	vec3_t result = {
		a.x * factor,
		a.y * factor,
		a.z * factor
	};

	return result;
}

vec3_t Vec3_div(vec3_t a, float factor)
{
	vec3_t result = {
		a.x / factor,
		a.y / factor,
		a.z / factor
	};

	return result;
}

vec3_t Vec3_cross(vec3_t a, vec3_t b)
{
	vec3_t result = {
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	};

	return result;
}

float Vec3_dot(vec3_t a, vec3_t b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

void Vec3_normalize(vec3_t* v)
{
	float length = sqrt((v->x * v->x) + (v->y * v->y) + (v->z * v->z));

	v->x /= length;
	v->y /= length;
	v->z /= length;
}

vec3_t Vec3_rotate_x(vec3_t v, float angle)
{
	vec3_t rotated_vector = {
			 v.x,
			 v.y * cos(angle) - v.z * sin(angle),
			 v.y * sin(angle) + v.z * cos(angle)
	};

	return rotated_vector;
}

vec3_t Vec3_rotate_y(vec3_t v, float angle)
{
	vec3_t rotated_vector = {
			v.x * cos(angle) - v.z * sin(angle),
			v.y,
			v.x * sin(angle) + v.z * cos(angle)
	};

	return rotated_vector;
}

vec3_t Vec3_rotate_z(vec3_t v, float angle)
{
	vec3_t rotated_vector = {
			v.x * cos(angle) - v.y * sin(angle),
			v.x * sin(angle) + v.y * cos(angle),
			v.z
	};

	return rotated_vector;
}

vec4_t vec4_from_vec3(vec3_t v)
{
	vec4_t result = { v.x, v.y, v.z, 1.0 };
	return result;
}

vec3_t vec3_from_vec4(vec4_t v)
{
	vec3_t result = { v.x, v.y, v.z };
	return result;
}

vec2_t vec2_from_vec4(vec4_t v)
{
	vec2_t result = { v.x, v.y };
	return result;
}

vec2_t& Vec2_from_vec4(vec4_t& v)
{
	vec2_t result = { v.x, v.y };
	return result;
}

float Vec4_mag(vec4_t a, vec4_t b)
{

	vec4_t result;
	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	result.w = a.w - b.w;

	return sqrtf((result.x * result.x) + (result.y * result.y) + (result.z * result.z) + (result.w * result.w));
}

float V4_mag(vec4_t a, vec2_t b)
{
	vec2_t result;
	result.x = a.x - b.x;
	result.y = a.y - b.y;

	return sqrtf(result.x * result.x + result.y * result.y);
}

