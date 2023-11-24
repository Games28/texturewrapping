#include "Mesh.h"

#define BLUE 0xff0000ff
#define GREEN 0xff00ff00
#define PURPLE 0xffff00ff
#define RED 0xffff0000
#define YELLOW 0xffffff00


Mesh_t mesh = 
{
	{ 0, 0, 0 },
	{ 1.0, 1.0, 1.0 },
	{ 0, 0, 0 }
};
vec3_t cube_vertices[N_CUBE_VERTICES] = {
		{-1,-1,-1},
		{-1,1,-1},
		{1,1,-1},
		{1,-1,-1},
		{1,1,1},
		{1,-1,1},
		{-1,1,1},
		{-1,-1,1}
};

Face_t cube_faces[N_CUBE_FACES] = {
	// front
   {1, 2, 3, { 0, 1 },{ 0, 0 }, { 1, 0 },0xFFFFFFFF },
   { 1, 3, 4, { 0, 1 },{ 1, 0 }, { 1, 1 },0xFFFFFFFF },
   // right
   {4, 3, 5, { 0, 1 },{ 0, 0 }, { 1, 0 },0xFFFFFFFF },
   {4, 5, 6, { 0, 1 },{ 1, 0 }, { 1, 1 },0xFFFFFFFF },
   // back
   {6, 5, 7, { 0, 1 },{ 0, 0 }, { 1, 0 },0xFFFFFFFF },
   {6, 7, 8, { 0, 1 },{ 1, 0 }, { 1, 1 },0xFFFFFFFF },
   // left
   {8, 7, 2, { 0, 1 },{ 0, 0 }, { 1, 0 },0xFFFFFFFF },
   { 8, 2, 1, { 0, 1 },{ 1, 0 }, { 1, 1 },0xFFFFFFFF },
   // top
   {2, 7, 5, { 0, 1 },{ 0, 0 }, { 1, 0 },0xFFFFFFFF },
   { 2, 5, 3, { 0, 1 },{ 1, 0 }, { 1, 1 },0xFFFFFFFF },
   // bottom
   { 6, 8, 1, { 0, 1 },{ 0, 0 }, { 1, 0 },0xFFFFFFFF },
   {6, 1, 4, { 0, 1 },{ 1, 0 }, { 1, 1 },0xFFFFFFFF }

};

void load_cube_mesh_data()
{
	for (int i = 0; i < N_CUBE_VERTICES; i++)
	{
		vec3_t cube_vertex = cube_vertices[i];
		mesh.vertices.push_back(cube_vertex);
	}

	for (int i = 0; i < N_CUBE_FACES; i++)
	{
		Face_t cube_face = cube_faces[i];
		mesh.faces.push_back(cube_face);
	}
}

