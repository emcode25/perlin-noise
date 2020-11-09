#include <SDL.h>

#include <stdio.h>
#include <math.h>
#include <time.h>

#include "perlin.h"

#define WIDTH 500
#define HEIGHT 500

SDL_Window* window;
SDL_Renderer* renderer;
float map[WIDTH][HEIGHT];

int p[PERMUTATION_SIZE]/* = { 151,160,137,91,90,15,
   131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
   190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
   88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
   77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
   102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
   135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
   5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
   223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
   129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
   251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
   49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
   138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
}*/;

int main(int argc, char** argv)
{
	int flags = SDL_INIT_VIDEO | SDL_INIT_AUDIO;
	int code = SDL_Init(flags);
	
	if(code != 0)
	{
		printf("ERROR! SDL_INIT() FAILED. %s", SDL_GetError());
		return code;
	}

	window = SDL_CreateWindow("Civilization", SDL_WINDOWPOS_UNDEFINED,	SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if(window == NULL)
	{
		printf("ERROR! SDL_CREATEWINDOW() FAILED. %s", SDL_GetError());
		return -1;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == NULL)
	{
		printf("ERROR! SDL_CREATERENDERER() FAILED. %s", SDL_GetError());
		return -1;
	}

	SDL_Event e;
	srand(time(NULL));

	reset:
	shuffleHash(p);

	SDL_RenderClear(renderer);

	for(int i = 0; i < WIDTH; ++i)
	{
		for(int j = 0; j < HEIGHT; ++j)
		{
			float n = noise2D_FBM(i, j, p, 200, 8, 2.0f, 0.5f);

			n += 1.0f;
			n /= 2.0f;

			n = clampf(n, 0, 1);

			int rgb = (int)roundf(0xFF * n);

			if(n < 0.5)
			{
				SDL_SetRenderDrawColor(renderer, 0x00, 0x00, rgb * 2, 0xFF);
			}
			else if(n < 0.9)
			{
				SDL_SetRenderDrawColor(renderer, 0x00, rgb, (int) roundf(rgb * 0.5), 0xFF);
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, rgb, rgb, rgb, 0xFF);
			}

			map[i][j] = n;

			SDL_Rect rect = {i, j, 1, 1};
			SDL_RenderFillRect(renderer, &rect);
		}
	}

	SDL_RenderPresent(renderer);

	while(1)
	{
		while(SDL_PollEvent(&e) != 0)
		{
			if(e.type == SDL_QUIT)
			{
				goto end;
			}
			else if(e.type == SDL_KEYDOWN)
			{
				switch(e.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						goto end;
					
					case SDLK_r:
						goto reset;
				}
			}
			else if(e.type == SDL_MOUSEBUTTONDOWN)
			{
				int x, y;
				SDL_GetMouseState(&x, &y);

				printf("x: %d\ny: %d\nnoise(x, y): %f\n", x, y, map[x][y]);
			}
		}
	}

	end:
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	return 0;
}
