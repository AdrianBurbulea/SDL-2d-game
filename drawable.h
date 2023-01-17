#pragma once
#include <SDL.h>

class drawable{
protected:
	static SDL_Renderer* R;
public:
	virtual void Draw() = 0;
};