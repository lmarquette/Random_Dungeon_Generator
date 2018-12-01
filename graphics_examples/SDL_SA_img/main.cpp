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

namespace Game
{
	SDL_Renderer *renderer = NULL;
	int screen_width = 800;
	int screen_height = 600;

	unsigned char prev_key_state[256];
	unsigned char *keys = NULL;
	SDL_Window *window = NULL;

	SDL_Surface *scratch;
	SDL_Surface *screen;


	int *grid = NULL;
	int *px, *py;
	Pixel *color;


	const int num_dungeons = 5;
	SDL_Rect Rect[num_dungeons];
	int overlapping_rooms = 0;



	void init()
	{
		SDL_Init(SDL_INIT_VIDEO);

		prev_key_state[256];
		keys = (unsigned char*)SDL_GetKeyboardState(NULL);

		window = SDL_CreateWindow("Random Dungeon Generator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_height, SDL_WINDOW_SHOWN);

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);


		scratch = SDL_CreateRGBSurfaceWithFormat(0, screen_width, screen_height, 24, SDL_PIXELFORMAT_RGB24);

		screen = SDL_GetWindowSurface(window);

		grid = (int*)malloc(scratch->w*scratch->h * sizeof(int));
		memset(grid, 0, sizeof(int)*scratch->w*scratch->h);


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
		/*
		SDL_Rect fillrect = { 100,100,100,100 };
		SDL_SetRenderDrawColor(renderer, 255, 255, 100, 255);
		SDL_RenderFillRect(renderer, &fillrect);*/

		
		for (int i = 0; i < num_dungeons; i++)
		{

			cout << "Creating" << endl;
			Game::Rect[i].x = (Game::screen_height / 2) + rand() % 200;
			Game::Rect[i].y = (Game::screen_width / 2) + rand() % 200;
			Game::Rect[i].w = rand() % 150;
			Game::Rect[i].h = rand() % 100;

			cout << "x: " << Rect[i].x << endl;
			cout << "y: " << Rect[i].y << endl;
			cout << "w: " << Rect[i].w << endl;
			cout << "h: " << Rect[i].h << endl << endl;

			SDL_SetRenderDrawColor(renderer, rand() % 255, rand() % 255, rand() % 255, 255);
			SDL_FillRect(screen, &Game::Rect[i], 255);
			SDL_RenderFillRect(renderer, &Game::Rect[i]);
		}

		SDL_RenderPresent(renderer);
		system("pause");
	}

	void Count_Overlapping_Rooms()
	{
		for (int i = 0; i < num_dungeons; i++)
		{
			for (int j = i + 1; j < num_dungeons; j++)
			{
				cout << "Box " << i << endl;
				cout << "x: " << Rect[i].x << " vs " << "x1: " << Rect[i + 1].x << endl;
				cout << "y: " << Rect[i].y << " vs " << "y1: " << Rect[i + 1].y << endl;
				cout << "w: " << Rect[i].w << " vs " << "w1: " << Rect[i + 1].w << endl;
				cout << "h: " << Rect[i].h << " vs " << "h1: " << Rect[i + 1].h << endl;
				cout << endl;

				//Checking sides of rectangles
				if()




				if (Rect[i].x > (Rect[j].x + Rect[j].w) || Rect[j].x > (Rect[i].x + Rect[i].w))
				{
					overlapping_rooms = 0;
				}
				//checking above/below
				if (Rect[i].y < (Rect[j].y + Rect[j].h) || Rect[j].y < (Rect[i].y + Rect[i].h))
				{
					overlapping_rooms = 0;
				}
				else
				{
					overlapping_rooms++;
					cout << "Overlapping room: " << overlapping_rooms << endl;
				}
			}
		}
		system("pause");
	}

	void Push_Rooms()
	{
		for (int i = 0; i < num_dungeons; i++)
		{
			if (overlapping_rooms > 0)
			{
				Rect[i].x += rand() % 5 + (-5);
				Rect[i].y += rand() % 5 + (-5);

				cout << "Updating position: " << Rect[i].x << endl;

				Count_Overlapping_Rooms();
			}
			else
			{
				cout << "No overlapping rooms" << endl;
				break;
			}
		}

	}

}
int main(int argc, char **argv)
{


	Game::init();



	Game::update();

	Game::Spawn_Rooms();
	Game::Count_Overlapping_Rooms();
	Game::Push_Rooms();

	system("pause");

	return 0;
}