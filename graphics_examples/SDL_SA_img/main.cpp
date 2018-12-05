#include <iostream>
#include <assert.h>
#include <time.h>
using namespace std;

//include SDL header
#include "SDL2-2.0.8\include\SDL.h"
#include "SDL2-2.0.8\include\SDL_image.h"

//load libraries
#pragma comment(lib,"SDL2-2.0.8\\lib\\x86\\SDL2.lib")
#pragma comment(lib,"SDL2-2.0.8\\lib\\x86\\SDL2main.lib")
#pragma comment(lib,"SDL2-2.0.8\\lib\\x86\\SDL2_image.lib")

#pragma comment(linker,"/subsystem:console")

struct Rect
{
	float x, y, w, h;
};

namespace Utility
{
	int collision(Rect *a, Rect *b)
	{
		if (a->x + a->w < b->x) return 0;
		if (a->x > b->x + b->w) return 0;
		if (a->y + a->h < b->y) return 0;
		if (a->y > b->y + b->h) return 0;
		return 1;
	}

	void make_Random_Matrix(int **m, int size)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = i + 1; j < size; j++)
			{
				m[i][j] = rand() % 2;
				m[j][i] = m[i][j];//u need to mirror it
			}
		}
	}
}

namespace Game
{
	SDL_Renderer *renderer = NULL;
	int screen_width = 800;
	int screen_height = 600;

	unsigned char prev_key_state[256];
	unsigned char *keys = NULL;
	SDL_Window *window = NULL;

	const int num_dungeons = 5;
	Rect dungeons[num_dungeons];
	int **connection_matrix = NULL;
	int *visited_array = NULL;

	int min_room_size = 10;
	int max_room_size = 80;

	

	void spawn_Rooms()
	{

		for (int i = 0; i < num_dungeons; i++)
		{

			cout << "Creating" << endl;
			dungeons[i].w = min_room_size + rand() % (max_room_size - min_room_size);
			dungeons[i].h = min_room_size + rand() % (max_room_size - min_room_size);
			dungeons[i].x = -max_room_size + rand() % max_room_size + screen_width / 2.0;
			dungeons[i].y = -max_room_size + rand() % max_room_size + screen_height / 2.0;
		}

	}

	void init()
	{
		SDL_Init(SDL_INIT_VIDEO);
		srand(time(0));

		prev_key_state[256];
		keys = (unsigned char*)SDL_GetKeyboardState(NULL);

		window = SDL_CreateWindow("Random Dungeon Generator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_height, SDL_WINDOW_SHOWN);

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		connection_matrix = (int**)malloc(sizeof(int*)*num_dungeons);
		visited_array = (int*)malloc(sizeof(int*)*num_dungeons);

		for (int i = 0; i < num_dungeons; i++)
		{
			connection_matrix[i] = (int*)malloc(sizeof(int)*num_dungeons);
		}

		spawn_Rooms();
		Utility::make_Random_Matrix(connection_matrix, num_dungeons);
	}



	int resolve_Overlapping_Rooms(float margin, float dt)
	{
		float bump_amount = 0.01;

		int n_overlapping_rooms = 0;
		for (int i = 0; i < num_dungeons; i++)
		{
			for (int j = i + 1; j < num_dungeons; j++)
			{
				Rect irect = { dungeons[i].x - margin, dungeons[i].y - margin,dungeons[i].w + 2.0*margin,dungeons[i].h + 2.0*margin };
				Rect jrect = { dungeons[j].x - margin, dungeons[j].y - margin,dungeons[j].w + 2.0*margin,dungeons[j].h + 2.0*margin };
				if (Utility::collision(&irect, &jrect))
				{
					n_overlapping_rooms++;
					float deltaX = (dungeons[j].x + dungeons[j].w*0.5) - (dungeons[i].x + dungeons[i].w*0.5);
					float deltaY = (dungeons[j].y + dungeons[j].h*0.5) - (dungeons[i].y + dungeons[i].h*0.5);
					float magnitude = sqrt(deltaX * deltaX + deltaY * deltaY);

					float norm_deltaX = 0.0;
					float norm_deltaY = 0.0;
					if (magnitude != 0.0)
					{
						norm_deltaX = deltaX / magnitude;
						norm_deltaY = deltaY / magnitude;
					}

					dungeons[j].x += norm_deltaX * bump_amount*dt;
					dungeons[j].y += norm_deltaY * bump_amount*dt;

					dungeons[i].x -= norm_deltaX * bump_amount*dt;
					dungeons[i].y -= norm_deltaY * bump_amount*dt;
				}
			}

		}

		for (int i = 0; i < num_dungeons; i++)
		{
			if (dungeons[i].x < 0) dungeons[i].x = 0;
			if (dungeons[i].x > screen_width - dungeons[i].w) dungeons[i].x = screen_width - dungeons[i].w;
			if (dungeons[i].y < 0) dungeons[i].y = 0;
			if (dungeons[i].y > screen_height - dungeons[i].h) dungeons[i].y = screen_height - dungeons[i].h;
		}

		return n_overlapping_rooms;
	}

	void prim()
	{
		visited_array[0] = 1;
		for (;;)
		{
			int min_index_i = 0;
			int min_index_j = 0;
			float key = DBL_MAX;
			int count = 0;

			float min_dist = 0;
			

			for (int i = 0; i < num_dungeons; i++)
			{
				if (visited_array[i] == 0) continue;
				count++;

				for (int j = 0; j < num_dungeons; j++)
				{
					if (visited_array[j] == 1) continue;
					
					float min_distance = sqrt(pow((dungeons[j].x - dungeons[i].x), 2) + pow((dungeons[j].y - dungeons[i].y), 2));

					
				}
			}
		}
	}

	void draw_Paths()
	{
		for (int i = 0; i < num_dungeons; i++)
		{
			for (int j = i + 1; j < num_dungeons; j++)
			{
				if (connection_matrix[i][j] == 1)
				{
					
					SDL_RenderDrawLine(renderer, dungeons[i].x + dungeons[i].w*0.5, dungeons[i].y + dungeons[i].h*0.5,
						dungeons[j].x + dungeons[j].w*0.5, dungeons[j].y + dungeons[j].h*0.5);

				}
			}
		}
	}

	void update()
	{
		
		memcpy(prev_key_state, keys, 256);

		//consume all window events first
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				exit(0);
			}
		}

		int n_overlapping = resolve_Overlapping_Rooms(5.0, 1.0);
		printf("n_overlapping = %d\n", n_overlapping);
		
	}

	void draw()
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
		for (int i = 0; i < num_dungeons; i++)
		{
			SDL_Rect rect;
			rect.x = dungeons[i].x;
			rect.y = dungeons[i].y;
			rect.w = dungeons[i].w;
			rect.h = dungeons[i].h;
			SDL_RenderFillRect(renderer, &rect);
		}

		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		draw_Paths();

		SDL_RenderPresent(renderer);
	}

}



int main(int argc, char **argv)
{
	Game::init();

	for (;;)
	{	
		Game::update();
		Game::draw();
	}
	
	getchar();
	return 0;
}