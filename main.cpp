#include <iostream>
#include <SDL2/SDL.h>

int main() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0){
    std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
    return 1;
  }

  SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);

  if (win == nullptr){
    std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  SDL_Delay(5 * 1000);
  SDL_DestroyWindow(win);
  SDL_Quit();
  return 0;
}