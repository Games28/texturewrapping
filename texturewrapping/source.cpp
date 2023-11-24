#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Vector.h"
#include "Mesh.h"
#include "Display.h"
#include "matrix.h"
#include "Vector.h"
#include "Texture.h"
#include "Mesh.h"
#include "Triangle.h"
#include "light.h"
#include "upng.h"

#define M_PI       3.14159265358979323846   // pi
#define window_width 800
#define window_height 600
enum cull_method
{
	CULL_NONE,
	CULL_BACKFACE
}cull_method;

enum render_method
{
	RENDER_WIRE,
	RENDER_WIRE_VERTEX,
	RENDER_FILL_TRIANGLE,
	RENDER_FILL_TRIANGLE_WIRE,
	RENDER_TEXTURED,
	RENDER_TEXTURED_WIRE
}render_method;


class graphics3D : public olc::PixelGameEngine
{
public:
	graphics3D()
	{
		sAppName = "3d Graphics";
	}
public:
	
	
	vec3_t camera_position = { 0,0,0 };
	
	
	
	std::vector<Triangle_t> triangles_to_render;
	mat4_t proj_matrix;
	vec4_t* pSelected = nullptr;

public:
	

	

	void input(float deltatime)
	{
		if (GetKey(olc::NP1).bPressed)
		{
			render_method = RENDER_WIRE_VERTEX;
		}
		if (GetKey(olc::NP2).bPressed)
		{
			render_method = RENDER_WIRE;
		}
		if (GetKey(olc::NP3).bPressed)
		{
			render_method = RENDER_FILL_TRIANGLE;
		}
		if (GetKey(olc::NP4).bPressed)
		{
			render_method = RENDER_FILL_TRIANGLE_WIRE;
		}
		if (GetKey(olc::NP5).bPressed)
		{
			cull_method = CULL_BACKFACE;
		}
		if (GetKey(olc::NP6).bPressed)
		{
			cull_method = CULL_NONE;
		}
		if (GetKey(olc::NP7).bPressed)
		{
			render_method = RENDER_TEXTURED;
		}
		if (GetKey(olc::NP8).bPressed)
		{
			render_method = RENDER_TEXTURED_WIRE;
		}
		if (GetKey(olc::NP7).bPressed)
		{
			render_method = RENDER_TEXTURED;
		}
		if (GetKey(olc::NP8).bPressed)
		{
			render_method = RENDER_TEXTURED_WIRE;
		}

		switch (render_method)
		{
		case RENDER_WIRE:
		{
			DrawString(10, 10, "Render_method: RENDER_WIRE" );
		}break;
		case RENDER_WIRE_VERTEX:
		{
			DrawString(10, 10, "Render_method: RENDER_WIRE_VERTEX");
		}break;
		case RENDER_FILL_TRIANGLE:
		{
			DrawString(10, 10, "Render_method: RENDER_FILL_TRIANGLE");
		}break;
		case RENDER_FILL_TRIANGLE_WIRE:
		{
			DrawString(10, 10, "Render_method: RENDER_FILL_TRIANGLE_WIRE");
		}break;
		}

		switch (cull_method)
		{
		case CULL_NONE:
		{
			DrawString(10, 20, "cull_method: CULL_NONE");
		}break;
		case CULL_BACKFACE:
		{
			DrawString(10, 20, "cull_method: CULL_BACKFACE");
		}break;
		}
	}
public:

	bool OnUserCreate() override
	{
		render_method = RENDER_TEXTURED_WIRE;
		cull_method = CULL_BACKFACE;
		float fov = M_PI / 2.0; // the same as 180/3, or 60deg
		float aspect = (float)window_height / (float)window_width;
		float znear = 0.0;
		float zfar = 0.0;
		proj_matrix = mat4_make_perspective(fov, aspect, znear, zfar);

		// Loads the vertex and face values for the mesh data structure
		load_cube_mesh_data();
		// load_obj_file_data("./assets/f22.obj");
		load_png_texture_data("saber.png");

		// Load the hardcoded texture array in the global mesh texture variable
		//mesh_texture = (uint32_t*)REDBRICK_TEXTURE;


		/////////////////////////////
		
		mesh.translation.z = 5.0;

		mat4_t scale_matrix = mat4_make_scale(mesh.scale.x, mesh.scale.y, mesh.scale.z);
		mat4_t translation_matrix = mat4_make_translation(mesh.translation.x, mesh.translation.y, mesh.translation.z);
		mat4_t rotation_matrix_x = mat4_make_rotation_x(mesh.rotation.x);
		mat4_t rotation_matrix_y = mat4_make_rotation_y(mesh.rotation.y);
		mat4_t rotation_matrix_z = mat4_make_rotation_z(mesh.rotation.z);

		int num_faces = mesh.faces.size();
		for (int i = 0; i < 2; i++) {
			Face_t mesh_face = mesh.faces[i];

			vec3_t face_vertices[3];
			face_vertices[0] = mesh.vertices[mesh_face.a - 1];
			face_vertices[1] = mesh.vertices[mesh_face.b - 1];
			face_vertices[2] = mesh.vertices[mesh_face.c - 1];

			vec4_t transformed_vertices[3];

			// Loop all three vertices of this current face and apply transformations
			for (int j = 0; j < 3; j++) {
				vec4_t transformed_vertex = vec4_from_vec3(face_vertices[j]);

				// Create a World Matrix combining scale, rotation, and translation matrices
				mat4_t world_matrix = mat4_identity();

				// Order matters: First scale, then rotate, then translate. [T]*[R]*[S]*v
				world_matrix = mat4_mul_mat4(scale_matrix, world_matrix);
				world_matrix = mat4_mul_mat4(rotation_matrix_z, world_matrix);
				world_matrix = mat4_mul_mat4(rotation_matrix_y, world_matrix);
				world_matrix = mat4_mul_mat4(rotation_matrix_x, world_matrix);
				world_matrix = mat4_mul_mat4(translation_matrix, world_matrix);

				// Multiply the world matrix by the original vector
				transformed_vertex = mat4_mul_vec4(world_matrix, transformed_vertex);

				// Save transformed vertex in the array of transformed vertices
				transformed_vertices[j] = transformed_vertex;
			}

			// Get individual vectors from A, B, and C vertices to compute normal
			vec3_t vector_a = vec3_from_vec4(transformed_vertices[0]); /*   A   */
			vec3_t vector_b = vec3_from_vec4(transformed_vertices[1]); /*  / \  */
			vec3_t vector_c = vec3_from_vec4(transformed_vertices[2]); /* C---B */
			
			// Get the vector subtraction of B-A and C-A
			vec3_t vector_ab = Vec3_sub(vector_b, vector_a);
			vec3_t vector_ac = Vec3_sub(vector_c, vector_a);
			Vec3_normalize(&vector_ab);
			Vec3_normalize(&vector_ac);
			//
			//// Compute the face normal (using cross product to find perpendicular)
			vec3_t normal = Vec3_cross(vector_ab, vector_ac);
			


			vec4_t projected_points[3];

			// Loop all three vertices to perform projection
			for (int j = 0; j < 3; j++) {
				// Project the current vertex
				projected_points[j] = mat4_mul_vec4_project(proj_matrix, transformed_vertices[j]);

				// Flip vertically since the y values of the 3D mesh grow bottom->up and in screen space y values grow top->down
				projected_points[j].y *= -1;

				// Scale into the view
				projected_points[j].x *= (window_width / 2.0);
				projected_points[j].y *= (window_height / 2.0);

				// Translate the projected points to the middle of the screen
				projected_points[j].x += (window_width / 2.0);
				projected_points[j].y += (window_height / 2.0);
			}

			// Calculate the average depth for each face based on the vertices after transformation
			float avg_depth = (transformed_vertices[0].z + transformed_vertices[1].z + transformed_vertices[2].z) / 3.0;

			// Calculate the shade intensity based on how aliged is the normal with the flipped light direction ray
			float light_intensity_factor = -Vec3_dot(normal, light.direction);

			// Calculate the triangle color based on the light angle
			uint32_t triangle_color = light_apply_intensity(mesh_face.color, light_intensity_factor);

			Triangle_t projected_triangle = {
				{
					{ projected_points[0].x, projected_points[0].y,projected_points[0].z, projected_points[0].w },
					{ projected_points[1].x, projected_points[1].y,projected_points[1].z, projected_points[1].w },
					{ projected_points[2].x, projected_points[2].y,projected_points[2].z, projected_points[2].w }
				},
			{
					{ mesh_face.a_uv.u, mesh_face.a_uv.v },
					{ mesh_face.b_uv.u, mesh_face.b_uv.v },
					{ mesh_face.c_uv.u, mesh_face.c_uv.v }
				},
				
				triangle_color,
				avg_depth
			};

			triangles_to_render.push_back(projected_triangle);

		}

		

		int num_triangles = triangles_to_render.size();
		for (int i = 0; i < num_triangles; i++) {
			for (int j = i; j < num_triangles; j++) {
				if (triangles_to_render[i].avg_depth < triangles_to_render[j].avg_depth) {
					// Swap the triangles positions in the array
					Triangle_t temp = triangles_to_render[i];
					triangles_to_render[i] = triangles_to_render[j];
					triangles_to_render[j] = temp;
				}
			}
		}
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::BLACK);
		
		input(fElapsedTime);

		

		int num_triangles = triangles_to_render.size();
		vec2_t mouse = { GetMouseX(),GetMouseY() };
		for (int i = 0; i < num_triangles; i++) {
			Triangle_t& triangle = triangles_to_render[i];


			if (GetMouse(0).bPressed)
			{
				pSelected = nullptr;
				for (int j = 0; j < 3; j++)
				{
					if (V4_mag( triangle.pointsv4[j], mouse) < 5)
					{
						
						pSelected = &triangle.pointsv4[j];

					}
				}
			}
			
			if (GetMouse(0).bReleased)
			{

				pSelected = nullptr;
			}

			if (GetMouse(1).bPressed)
			{
				int i = 0;
			}

			if (pSelected != nullptr)
			{
				pSelected->x = mouse.x;
				pSelected->y = mouse.y;
				int x = pSelected->x;
				int y = pSelected->y;
				DrawString(10, 30, "selectedx: " + std::to_string(x) + "selectedy: " + std::to_string(y));
			}
			DrawString(10, 40, "0x: " + std::to_string(triangle.pointsv4[0].x) + "0y: " + std::to_string(triangle.pointsv4[0].y));
			DrawString(10, 50, "1x: " + std::to_string(triangle.pointsv4[1].x) + "1y: " + std::to_string(triangle.pointsv4[1].y));
			DrawString(10, 60, "2x: " + std::to_string(triangle.pointsv4[2].x) + "2y: " + std::to_string(triangle.pointsv4[2].y));

			triangles_to_render[0].pointsv4[0] = triangles_to_render[1].pointsv4[0];
			triangles_to_render[0].pointsv4[2] = triangles_to_render[1].pointsv4[1];


          	draw_textured_triangle(this,
					triangle.pointsv4[0].x, triangle.pointsv4[0].y, triangle.pointsv4[0].z, triangle.pointsv4[0].w, triangle.texcoords[0].u, triangle.texcoords[0].v, // vertex A
					triangle.pointsv4[1].x, triangle.pointsv4[1].y, triangle.pointsv4[1].z, triangle.pointsv4[1].w, triangle.texcoords[1].u, triangle.texcoords[1].v, // vertex B
					triangle.pointsv4[2].x, triangle.pointsv4[2].y, triangle.pointsv4[2].z, triangle.pointsv4[2].w, triangle.texcoords[2].u, triangle.texcoords[2].v, // vertex C
					mesh_texture
				);
			

			// Draw triangle wireframe
		

			FillCircle(triangle.pointsv4[0].x, triangle.pointsv4[0].y, 5, 0xffff00ff);
			FillCircle(triangle.pointsv4[1].x, triangle.pointsv4[1].y, 5, olc::CYAN);
			FillCircle(triangle.pointsv4[2].x, triangle.pointsv4[2].y, 5, olc::CYAN);
			FillCircle(GetMouseX(), GetMouseY(), 5, olc::GREEN);
			
		}
		//triangles_to_render.clear();

		return true;
	}

	bool OnUserDestroy() override
	{
		mesh.faces.clear();
		mesh.vertices.clear();

		return true;
	}
};


int main()
{

	graphics3D demo;
	if (demo.Construct(window_width, window_height, 1, 1))
	{
		demo.Start();
	}
}