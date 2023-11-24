#ifndef MESH_H
#define MESH_H
#include"Vector.h"
#include "Triangle.h"
#include <vector>

#define N_CUBE_VERTICES 8
#define N_CUBE_FACES (6 * 2)



    extern vec3_t cube_vertices[N_CUBE_VERTICES];
 
    extern Face_t cube_faces[N_CUBE_FACES];

    typedef struct Mesh_t
    {
        vec3_t rotation;
        vec3_t scale;
        vec3_t translation;
        std::vector<vec3_t> vertices;
        std::vector<Face_t> faces;
        
        
    };

    extern Mesh_t mesh;

    void load_cube_mesh_data();

    
#endif // !MESH_H

