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

struct Pixel
{
	unsigned char r, g, b;
};

int collision(SDL_Rect *a, SDL_Rect *b)
{
	if (a->x + a->w < b->x) return 0;
	if (a->x > b->x + b->w) return 0;
	if (a->y + a->h < b->y) return 0;
	if (a->y > b->y + b->h) return 0;
	return 1;
}

namespace Game
{
	SDL_Renderer *renderer = NULL;
	int screen_width = 800;
	int screen_height = 600;

	unsigned char prev_key_state[256];
	unsigned char *keys = NULL;
	SDL_Window *window = NULL;

	//SDL_Surface *scratch;//??????????????????????????????????
	//SDL_Surface *screen;//??????????????????????????????????


	//int *grid = NULL;//??????????????????????????????????
	//int *px, *py;//??????????????????????????????????
	//Pixel *color;//??????????????????????????????????


	const int num_dungeons = 5;
	SDL_Rect dungeons[num_dungeons];
	//int overlapping_rooms = 0;???????????????????????????????????



	void init()
	{
		SDL_Init(SDL_INIT_VIDEO);

		prev_key_state[256];
		keys = (unsigned char*)SDL_GetKeyboardState(NULL);

		window = SDL_CreateWindow("Random Dungeon Generator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_height, SDL_WINDOW_SHOWN);

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);


		//????????????????????????????

		/*scratch = SDL_CreateRGBSurfaceWithFormat(0, screen_width, screen_height, 24, SDL_PIXELFORMAT_RGB24);

		screen = SDL_GetWindowSurface(window);*/

		//grid = (int*)malloc(scratch->w*scratch->h * sizeof(int));//????????????????????
		//memset(grid, 0, sizeof(int)*scratch->w*scratch->h);//???????????????????????????????


		//Clear Screen
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
	}


	void update()
	{
		srand(time(0));
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

	
	}

	void Spawn_Rooms()
	{
		//????????????????????????????????????????????
		/*
		SDL_Rect fillrect = { 100,100,100,100 };
		SDL_SetRenderDrawColor(renderer, 255, 255, 100, 255);
		SDL_RenderFillRect(renderer, &fillrect);*/

		
		for (int i = 0; i < num_dungeons; i++)
		{

			cout << "Creating" << endl;
			Game::dungeons[i].x = Game::screen_height / 2;
			Game::dungeons[i].y = Game::screen_width / 2;
			Game::dungeons[i].w = rand() % 150;
			Game::dungeons[i].h = rand() % 100;

			//??????????????????????????????????
			/*SDL_SetRenderDrawColor(renderer, rand() % 255, rand() % 255, rand() % 255, 255);
			SDL_FillRect(screen, &Game::dungeons[i], 255);
			SDL_RenderFillRect(renderer, &Game::dungeons[i]);*/
		}

		//SDL_RenderPresent(renderer);//?????????????????????
		//system("pause");
	}

	int Count_Overlapping_Rooms()
	{
		int n_overlapping_rooms = 0;
		for (int i = 0; i < num_dungeons; i++)
		{
			for (int j = i + 1; j < num_dungeons; j++)
			{
				if (collision(&dungeons[i], &dungeons[j]))
				{
					n_overlapping_rooms++;
					int deltaX = Game::dungeons[j].x - Game::dungeons[i].x;
					int deltaY = Game::dungeons[j].y - Game::dungeons[i].y;
					int magnitude = sqrt(deltaX + deltaY);

					int norm_deltaX = deltaX / magnitude;
					int norm_deltaY = deltaY / magnitude;

					Game::dungeons[j].x = Game::dungeons[j].x + norm_deltaX;
					Game::dungeons[j].y = Game::dungeons[j].y + norm_deltaY;

					Game::dungeons[i].x = Game::dungeons[i].x - norm_deltaX;
					Game::dungeons[i].y = Game::dungeons[i].y - norm_deltaY;

					
				}
				else
				{
					////?????????????????????????????????
					//overlapping_rooms = 0;
					
				}
			}
		}
	
		return n_overlapping_rooms;
	}

	void Push_Rooms()
	{
		//????????????????????????????????????
		/*for (;;)
		{
			for (int i = 0; i < num_dungeons; i++)
			{
				if (overlapping_rooms > 0)
				{
					Rect[i].x += rand() % 5 + (-5);
					Rect[i].y += rand() % 5 + (-5);

					cout << "Updating position: " << Rect[i].x << endl;

					Count_Overlapping_Rooms();
					SDL_RenderPresent(renderer);
				}
				else
				{
					cout << "No overlapping rooms" << endl;
					break;
				}
			}
		}*/
	}

}
int main(int argc, char **argv)
{


	Game::init();

	//where is your game loop?????????????????????????????????????????????????

	Game::update();

	Game::Spawn_Rooms();
	int n_overlapping = Game::Count_Overlapping_Rooms();
	printf("n_overlapping = %d\n", n_overlapping);
	Game::Push_Rooms();

	getchar();
	return 0;
}