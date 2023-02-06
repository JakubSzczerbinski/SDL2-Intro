#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include "res_path.h"
//#include "cleanup.h"

void logSDLError(std::ostream &os, const std::string &msg){
	os << msg << " error: " << SDL_GetError() << std::endl;
}


SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren){

	SDL_Texture *texture = nullptr;
	
	SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());

	if (loadedImage != nullptr){
		texture = SDL_CreateTextureFromSurface(ren, loadedImage);
		SDL_FreeSurface(loadedImage);
		
		if (texture == nullptr){
			logSDLError(std::cout, "CreateTextureFromSurface");
		}
	}
	else {
		logSDLError(std::cout, "LoadBMP");
	}
	return texture;
}



void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y){
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	//Query the texture to get its width and height to use
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(ren, tex, NULL, &dst);
}



int main() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0){
    std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
    return 1;
  }
  
  SDL_Window *win = SDL_CreateWindow("kACZKA", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1700, 200, SDL_WINDOW_FULLSCREEN   );

  if (win == nullptr){
    std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl; //binarny or
    SDL_Quit();
    return 1;
  }
   SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
if (ren == nullptr){
	SDL_DestroyWindow(win);
	std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
	SDL_Quit();
	return 1;
}


const char *image_path = "water.bmp";
SDL_Surface *image = SDL_LoadBMP(image_path);
if (!image) {
    printf("Failed to load image at %s: %s\n", image_path, SDL_GetError());
    return 0;
}
SDL_FreeSurface(image);






SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, SDL_LoadBMP(image_path));
SDL_FreeSurface(NULL);
if (tex == nullptr){
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
	SDL_Quit();
	return 1;
}







SDL_Texture *tex_2 = SDL_CreateTextureFromSurface(ren, SDL_LoadBMP("zolw.bmp"));
SDL_FreeSurface(NULL);
if (tex_2 == nullptr){
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
	SDL_Quit();
	return 1;
}


 SDL_Rect mniejszy_zolw;
 mniejszy_zolw.x = 100;
 mniejszy_zolw.y = 250;
 mniejszy_zolw.h = 450;
 mniejszy_zolw.w = 260;
 SDL_Rect* wskaznik_do_mniejszy_zolw = &mniejszy_zolw;
 // SDL_Rect kopia_mniejszego_zolwia= *wskaznik_do_mniejszy_zolw; 

for (int i = 0; i < 3; ++i){


	SDL_RenderClear(ren);


	SDL_RenderCopy(ren, tex, NULL, NULL);
  SDL_RenderCopy(ren, tex_2, NULL, wskaznik_do_mniejszy_zolw); //&mniejszy_zolw



	SDL_RenderPresent(ren);


	SDL_Delay(1000);

  




}                     

SDL_DestroyTexture(tex);
SDL_DestroyTexture(tex_2);
SDL_DestroyRenderer(ren);
SDL_DestroyWindow(win);
SDL_Quit();





/*
// const int SCREEN_WIDTH  = 640;
// const int SCREEN_HEIGHT = 480;
if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
	logSDLError(std::cout, "SDL_Init");
	return 1;
}

SDL_Window *window = SDL_CreateWindow("Lesson 2", 100, 100, 640,
	480, SDL_WINDOW_SHOWN);
if (window == nullptr){
	logSDLError(std::cout, "CreateWindow");
	SDL_Quit();
	return 1;
}
SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
	SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
if (renderer == nullptr){
	logSDLError(std::cout, "CreateRenderer");
	cleanup(window);
  SDL_Quit();
	return 1;
}



const std::string resPath = getResourcePath("Lesson2");
SDL_Texture *background = loadTexture(resPath + "background.bmp", renderer);
SDL_Texture *image = loadTexture(resPath + "image.bmp", renderer);
if (background == nullptr || image == nullptr){
	cleanup(background, image, renderer, window);
	SDL_Quit();
	return 1;
}


SDL_RenderClear(renderer);

int bW, bH;
SDL_QueryTexture(background, NULL, NULL, &bW, &bH);
renderTexture(background, renderer, 0, 0);
renderTexture(background, renderer, bW, 0);
renderTexture(background, renderer, 0, bH);
renderTexture(background, renderer, bW, bH);


int iW, iH;
SDL_QueryTexture(image, NULL, NULL, &iW, &iH);
int x = 640 / 2 - iW / 2;
int y = 480 / 2 - iH / 2;
renderTexture(image, renderer, x, y);

SDL_RenderPresent(renderer);
SDL_Delay(1000);


cleanup(background, image, renderer, window);
SDL_Quit();

*/

  std::cout << 0x000000f;
  SDL_Delay(5 * 1000);
  SDL_DestroyWindow(win);
  SDL_Quit();

  return 0;
  
}