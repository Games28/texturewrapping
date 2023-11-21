#include "Mesh.h"

#define BLUE 0xff0000ff
#define GREEN 0xff00ff00
#define PURPLE 0xffff00ff
#define RED 0xffff0000
#define YELLOW 0xffffff00


Mesh_t mesh;
Vec3_t cube_vertices[N_CUBE_VERTICES] = {
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
	{1,2,3, BLUE},
	{1,3,4, BLUE},

	{4,3,5, YELLOW},
	{4,5,6, YELLOW},

	{6,5,7, PURPLE},
	{6,7,8, PURPLE},

	{8,7,2, RED},
	{8,2,1, BLUE},

	{2,7,5, BLUE},
	{2,5,3, PURPLE},

	{6,8,1,GREEN},
	{6,1,4, GREEN}

};

void load_cube_mesh_data()
{
	for (int i = 0; i < N_CUBE_VERTICES; i++)
	{
		Vec3_t cube_vertex = cube_vertices[i];
		mesh.vertices.push_back(cube_vertex);
	}

	for (int i = 0; i < N_CUBE_FACES; i++)
	{
		Face_t cube_face = cube_faces[i];
		mesh.faces.push_back(cube_face);
	}
}

void load_obj_file_data(const char* filename)
{
	FILE* file;
	fopen_s(&file,filename,"r");

	char line[1024];

	while (fgets(line, 1024, file))
	{
		//vertex info
		if (strncmp(line, "v ", 2) == 0)
		{
			Vec3_t vertex;
			sscanf_s(line, "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);
			mesh.vertices.push_back(vertex);
		}

		//face info
		if (strncmp(line, "f ", 2) == 0)
		{
			
			int vertex_indices[3];
			int texture_indices[3];
			int normal_indices[3];
			sscanf_s(
				line, "f %d/%d/%d %d/%d/%d %d/%d/%d",
				&vertex_indices[0], &texture_indices[0], &normal_indices[0],
				&vertex_indices[1], &texture_indices[1], &normal_indices[1],
				&vertex_indices[2], &texture_indices[2], &normal_indices[2]
				);

			Face_t face = {
				vertex_indices[0],
				vertex_indices[1],
				vertex_indices[2]
			};
			
			mesh.faces.push_back(face);
		}

	}



}
