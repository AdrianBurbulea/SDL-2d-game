#pragma once
#include <SDL.h>
#include <SDL_image.h>

class Texture{
public:
	SDL_Texture* Backgrounds[7];
	SDL_Texture* Hero[4];
	SDL_Texture* Enemy[4];
	SDL_Texture* fire[2];
	SDL_Texture* ice[2];
	SDL_Texture* level[4];
	Texture(SDL_Renderer* R);
	~Texture();
};

