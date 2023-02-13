#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include "res_path.h"

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y)
{
	// Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	// Query the texture to get its width and height to use
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(ren, tex, NULL, &dst);
}
int main()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Window *win = SDL_CreateWindow("żółw", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1700, 200, SDL_WINDOW_FULLSCREEN);

	if (win == nullptr)
	{
		std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl; // binarny or
		SDL_Quit();
		return 1;
	}
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr)
	{
		SDL_DestroyWindow(win);
		std::cout << "logSDLError: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	const char *image_path = "resources/water.bmp";
	SDL_Surface *image = SDL_LoadBMP(image_path);
	if (!image)
	{
		printf("Failed to load image at %s: %s\n", image_path, SDL_GetError());
		return 0;
	}
	SDL_FreeSurface(image);

	SDL_Texture *loadTexture = SDL_CreateTextureFromSurface(ren, SDL_LoadBMP(image_path));
	SDL_FreeSurface(NULL);
	if (loadTexture == nullptr)
	{
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_Texture *tex_2 = SDL_CreateTextureFromSurface(ren, SDL_LoadBMP("resources/zolw.bmp"));
	SDL_FreeSurface(NULL);
	if (tex_2 == nullptr)
	{
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_Rect mniejszy_zolw;
	mniejszy_zolw.x = 200;
	mniejszy_zolw.y = 200;
	mniejszy_zolw.h = 200;
	mniejszy_zolw.w = 210;
	SDL_Rect *wskaznik_do_mniejszy_zolw = &mniejszy_zolw;
	// SDL_Rect kopia_mniejszego_zolwia= *wskaznik_do_mniejszy_zolw;

	for (int i = 0; i < 3; ++i)
	{
		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, loadTexture, NULL, NULL);
		SDL_RenderCopy(ren, tex_2, NULL, wskaznik_do_mniejszy_zolw); //&mniejszy_zolw
		SDL_RenderPresent(ren);
		SDL_Delay(1000);
	}
	SDL_DestroyTexture(loadTexture);
	SDL_DestroyTexture(tex_2);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}