#pragma once

#include "include/Engine_core.h"
#include "include/Light_core.h"
#include "include/Actor_core.h"
#include "include/Particle_core.h"

namespace My_Game
{

	namespace World
	{

		namespace Parameters
		{
			Vec2D::Vec2D spawn_point;
			Vec2D::Vec2D end_point;

			
		}
		
		Vec2D::Vec2D avg_pos;

		Tileset::Tileset tileset;
		Font::Font text;

		Actor::Factory boids;

		Grid::Grid map;
		Grid::Grid collision;
		Grid::Grid imprint;
		Grid::Grid obstacles;

		Grid_Camera::Grid_Camera camera;

		Vec2D::Vec2D mouse_grid_point;

		unsigned char *neighbor_array = NULL;

		Actor::Factory indicator;

	}

	void init(int screen_w, int screen_h)
	{
		srand(time(0));
		//initialize all systems and open game window
		Engine::init("hello", screen_w, screen_h);

		Font::init(&World::text, "font_tileset.txt", Engine::renderer);

		Tileset::init(&World::tileset, "map_tileset.txt", Engine::renderer);

		Grid::load(&World::map, "giant_map_map.csv");
		Grid::init(&World::imprint, World::map.n_rows, World::map.n_cols);
		Grid::init(&World::obstacles, World::map.n_rows, World::map.n_cols);

		//World::neighbor_array = (unsigned char*)malloc(sizeof(unsigned char) * World::n_boids);

		Grid_Camera::init(&World::camera, Engine::screen_width, Engine::screen_height);

	}

	void begin_Play(unsigned int current_time)
	{
		World::camera.world_coord.x = 0;
		World::camera.world_coord.y = 0;
		World::camera.world_coord.w = 32;
		World::camera.world_coord.h = World::camera.world_coord.w * Engine::screen_height / Engine::screen_width;

		//SDL_Rect rect = {}
	}

	void update(unsigned int current_time, float dt)
	{

		Engine::event_Loop();
	}

	void draw(unsigned int current_time)
	{
		SDL_RenderClear(Engine::renderer);

		Tileset::draw_Grid(&World::tileset, &World::camera, &World::map, &RGBA::default, Engine::renderer);

		//flip buffers
		SDL_RenderPresent(Engine::renderer);
	}

}