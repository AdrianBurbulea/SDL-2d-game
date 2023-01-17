#pragma once
#include "buton.h"

class projectile :public Buton{
	int dx;
public:
	projectile() {}
	projectile(const projectile& d)
	{
		this->t = d.t;
		this->dx = d.dx;
		this->rect = d.rect;
	}
	projectile(int dx, SDL_Rect r, SDL_Texture* T[2])
	{
		this->dx = dx;
		if (dx > 0)
			t = T[0];
		else
			t = T[1];
		this->rect = r;
	}
	int handleEvents()
	{
		rect.x += dx;
		if (rect.x < -50 || rect.x>1000)
			return 1;
		return 0;
	}
	int checkColison(SDL_Rect e)
	{
		SDL_Rect aux = this->rect;
		if (SDL_HasIntersection(&e, &aux))
			return 1;
		else
			return 0;
	}
};
