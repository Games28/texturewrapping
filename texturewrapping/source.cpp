#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Vector.h"
#include "Mesh.h"
#include "Display.h"
#include "Array.h"
#include "Vector.h"
#include "Texture.h"

enum cull_method
{
	CULL_NONE,
	CULL_BACKFRACE
}cull_method;

enum render_method
{
	RENDER_WIRE,
	RENDER_WIRE_VERTEX,
	RENDER_FILL_TRIANGLE,
	RENDER_FILL_TRIANGLE_WIRE
}render_method;


class graphics3D : public olc::PixelGameEngine
{
public:
	graphics3D()
	{
		sAppName = "3d Graphics";
	}
public:
	
	float fov_factor = 640;
	Vec3_t camera_position = { 0,0,0 };
	
	int Indexpoint = 0;
	int IndexT = 0;
	Vec2_t coords = { 0.0f,0.0f };
	std::vector<Triangle_t> triangles_to_render;
	
	Vec2_t* pSelected = nullptr;

public:
	

	Vec2_t project(Vec3_t point)
	{
		Vec2_t projected_point = {
			(fov_factor * point.x) / point.z,
			(fov_factor * point.y) / point.z,
		};

		return projected_point;
	}

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
			cull_method = CULL_BACKFRACE;
		}
		if (GetKey(olc::NP6).bPressed)
		{
			cull_method = CULL_NONE;
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
		case CULL_BACKFRACE:
		{
			DrawString(10, 20, "cull_method: CULL_BACKFACE");
		}break;
		}
	}
public:

	bool OnUserCreate() override
	{
		mesh.rotation = { 0,0,0 };
		render_method = RENDER_WIRE;
		cull_method = CULL_BACKFRACE;
		load_cube_mesh_data();
		//load_obj_file_data("./assets/cube.obj");

		int num_faces = mesh.faces.size();

		for (int i = 0; i < 2; i++)
		{
			Face_t mesh_face = mesh.faces[i];

			Vec3_t face_vertices[3];

			face_vertices[0] = mesh.vertices[mesh_face.a - 1];
			face_vertices[1] = mesh.vertices[mesh_face.b - 1];
			face_vertices[2] = mesh.vertices[mesh_face.c - 1];



			Vec3_t transformed_vertices[3];


			for (int j = 0; j < 3; j++)
			{
				Vec3_t transformed_vertex = face_vertices[j];


				transformed_vertex = Vec3_rotate_x(transformed_vertex, mesh.rotation.x);
				transformed_vertex = Vec3_rotate_y(transformed_vertex, mesh.rotation.y);
				transformed_vertex = Vec3_rotate_z(transformed_vertex, mesh.rotation.z);


				transformed_vertex.z += 5;

				transformed_vertices[j] = transformed_vertex;
			}

			if (cull_method == CULL_BACKFRACE)
			{
				Vec3_t vector_a = transformed_vertices[0];
				Vec3_t vector_b = transformed_vertices[1];
				Vec3_t vector_c = transformed_vertices[2];

				Vec3_t vector_ab = Vec3_sub(vector_b, vector_a);
				Vec3_t vector_ac = Vec3_sub(vector_c, vector_a);

				Vec3_t normal = Vec3_cross(vector_ab, vector_ac);

				Vec3_normalize(&normal);

				Vec3_t camera_ray = Vec3_sub(camera_position, vector_a);

				float dot_normal_camera = Vec3_dot(normal, camera_ray);

				if (dot_normal_camera < 0)
				{
					continue;
				}
			}



			Vec2_t projected_points[3];

			for (int j = 0; j < 3; j++)
			{
				projected_points[j] = project(transformed_vertices[j]);

				projected_points[j].x += (window_width / 2);
				projected_points[j].y += (window_height / 2);



			}

			Triangle_t projected_trangle
			{
				{
					{projected_points[0].x,projected_points[0].y},
					{projected_points[1].x,projected_points[1].y},
					{projected_points[2].x,projected_points[2].y}
				},
				mesh_face.color
			};

			triangles_to_render.push_back(projected_trangle);

		}
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		Clear(olc::BLACK);
		
		input(fElapsedTime);

		
		

		//mesh.rotation.y += 0.5f * fElapsedTime;
		//mesh.rotation.x += 0.5f * fElapsedTime;
		//mesh.rotation.z += 0.5f * fElapsedTime;
		
		
		
		int num_triangles = triangles_to_render.size();
		Vec2_t mouse = { GetMouseX(),GetMouseY() };


		for (int i = 0; i < num_triangles; i++)
		{
			Triangle_t& triangle = triangles_to_render[i];

			if (GetMouse(0).bPressed)
			{
				pSelected = nullptr;
				for (int j = 0; j < 3; j++)
				{
					
						if (Vec2_mag(triangle.points[j], mouse) < 10)
						{
							pSelected = &triangle.points[j];
							Indexpoint = j;
							IndexT = i;
				
						}
					
				}

				
			}
			
			if (GetMouse(0).bReleased)
			{
				
				pSelected = nullptr;
			}

			if (pSelected != nullptr)
			{
				*pSelected = mouse;
				
				//if (IndexT == 0 && Indexpoint == 1)
				//{
				//	triangles_to_render[0].points[1] = mouse;
				//}
				
				
				
				DrawString(30, 40, "triangle: " + std::to_string(IndexT) + " point: " + std::to_string(Indexpoint));
				DrawString(30, 50, "pSelectedx: " + std::to_string(pSelected->x) + "pSelectedy: " + std::to_string(pSelected->y));
			}
			triangles_to_render[0].points[0] = triangles_to_render[1].points[0];
			triangles_to_render[0].points[2] = triangles_to_render[1].points[1];
			//triangles_to_render[0].points[1] = triangles_to_render[0].points[1];
			DrawString(30, 60, "0x: " + std::to_string(triangle.points[0].x) + "0y: " + std::to_string(triangle.points[0].y));
			DrawString(30, 70, "1x: " + std::to_string(triangle.points[1].x) + "1y: " + std::to_string(triangle.points[1].y));
			DrawString(30, 80, "2x: " + std::to_string(triangle.points[2].x) + "2y: " + std::to_string(triangle.points[2].y));

			

			if (render_method == RENDER_FILL_TRIANGLE || render_method == RENDER_FILL_TRIANGLE_WIRE)
			{
				draw_filled_triangle(this, triangle.points[0].x, triangle.points[0].y,
					triangle.points[1].x, triangle.points[1].y,
					triangle.points[2].x, triangle.points[2].y,
					triangle.color);
			}

			if (render_method == RENDER_WIRE || render_method == RENDER_WIRE_VERTEX || render_method == RENDER_FILL_TRIANGLE_WIRE)
			{
				draw_triangle(this, triangle.points[0].x, triangle.points[0].y,
					triangle.points[1].x, triangle.points[1].y,
					triangle.points[2].x, triangle.points[2].y,
					0xffffffff);
			}

			if (render_method == RENDER_WIRE_VERTEX)
			{
				draw_rect(this, triangle.points[0].x, triangle.points[0].y, 4, 4, 0xff00ff00);
				draw_rect(this, triangle.points[1].x, triangle.points[1].y, 4, 4, 0xffff00ff);
				draw_rect(this, triangle.points[2].x, triangle.points[2].y, 4, 4, 0xffff0000);

			}
			
			for (int i = 0; i < 3; i++)
			{
				FillCircle({ int(triangle.points[i].x),int(triangle.points[i].y) }, 4, olc::CYAN);
			}

			
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