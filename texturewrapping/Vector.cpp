#include "Vector.h"

float Vec2_length(Vec2_t v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}

Vec2_t Vec2_add(Vec2_t a, Vec2_t b)
{
	Vec2_t result = {
		a.x + b.x,
		a.y + b.y
	};

	return result;
}

Vec2_t Vec2_sub(Vec2_t a, Vec2_t b)
{
	Vec2_t result = {
		a.x - b.x,
		a.y - b.y
	};

	return result;
}

Vec2_t Vec2_multi(Vec2_t a, float factor)
{
	Vec2_t result = {
		a.x * factor,
		a.y * factor
	};

	return result;
}

Vec2_t Vec2_div(Vec2_t a, float factor)
{
	Vec2_t result = {
		a.x / factor,
		a.y / factor
	};

	return result;
}

float Vec2_dot(Vec2_t a, Vec2_t b)
{
	return (a.x * b.x) + (a.y * b.y);
}

void Vec2_normalize(Vec2_t* v)
{
	float length = sqrt(v->x * v->x + v->y * v->y);

	v->x /= length;
	v->y /= length;
}

float Vec2_mag(Vec2_t a, Vec2_t b)
{
	Vec2_t result;
	result.x = a.x - b.x;
	result.y = a.y - b.y;

	return sqrtf(result.x * result.x + result.y * result.y);;
}



float Vec3_length(Vec3_t v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);


}

Vec3_t Vec3_add(Vec3_t a, Vec3_t b)
{
	Vec3_t result = {
		a.x + b.x,
		a.y + b.y,
		a.z + b.z
	};

	return result;
}

Vec3_t Vec3_sub(Vec3_t a, Vec3_t b)
{
	Vec3_t result = {
		a.x - b.x,
		a.y - b.y,
		a.z - b.z
	};

	return result;
}

Vec3_t Vec3_multi(Vec3_t a, float factor)
{
	Vec3_t result = {
		a.x * factor,
		a.y * factor,
		a.z * factor
	};

	return result;
}

Vec3_t Vec3_div(Vec3_t a, float factor)
{
	Vec3_t result = {
		a.x / factor,
		a.y / factor,
		a.z / factor
	};

	return result;
}

Vec3_t Vec3_cross(Vec3_t a, Vec3_t b)
{
	Vec3_t result = {
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	};

	return result;
}

float Vec3_dot(Vec3_t a, Vec3_t b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

void Vec3_normalize(Vec3_t* v)
{
	float length = sqrt((v->x * v->x) + (v->y * v->y) + (v->z * v->z));

	v->x /= length;
	v->y /= length;
	v->z /= length;
}

Vec3_t Vec3_rotate_x(Vec3_t v, float angle)
{
	Vec3_t rotated_vector = {
			 v.x,
			 v.y * cos(angle) - v.z * sin(angle),
			 v.y * sin(angle) + v.z * cos(angle)
	};

	return rotated_vector;
}

Vec3_t Vec3_rotate_y(Vec3_t v, float angle)
{
	Vec3_t rotated_vector = {
			v.x * cos(angle) - v.z * sin(angle),
			v.y,
			v.x * sin(angle) + v.z * cos(angle)
	};

	return rotated_vector;
}

Vec3_t Vec3_rotate_z(Vec3_t v, float angle)
{
	Vec3_t rotated_vector = {
			v.x * cos(angle) - v.y * sin(angle),
			v.x * sin(angle) + v.y * cos(angle),
			v.z
	};

	return rotated_vector;
}
