#pragma once
#include "drawable.h"

class Background:public drawable {
protected:
	SDL_Texture* t;
public:
	Background(){}
	Background(SDL_Texture* vec[], int nr)
	{
		t = vec[nr];
	}
	virtual void Draw()
	{
		SDL_RenderCopy(R, t, NULL, NULL);
	}
};