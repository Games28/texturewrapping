#ifndef MESH_H
#define MESH_H
#include"Vector.h"
#include "Triangle.h"
#include <vector>

#define N_CUBE_VERTICES 8
#define N_CUBE_FACES (6 * 2)



    extern Vec3_t cube_vertices[N_CUBE_VERTICES];
 
    extern Face_t cube_faces[N_CUBE_FACES];

    typedef struct Mesh_t
    {
        std::vector<Vec3_t> vertices;
        std::vector<Face_t> faces;
        Vec3_t rotation;
    };

    extern Mesh_t mesh;

    void load_cube_mesh_data();

    void load_obj_file_data(const char* filename);
#endif // !MESH_H

