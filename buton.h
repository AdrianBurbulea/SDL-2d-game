#pragma once
#include "background.h"

class Buton:public Background{
protected:
	bool clicked;
	SDL_Rect rect;
public:
	Buton(){}
	Buton(SDL_Texture* vec[], int nr, SDL_Rect r) : Background(vec,nr)
	{
		clicked = false;
		rect = r;
	}
	virtual void Draw()
	{
		SDL_RenderCopy(R, t, NULL, &rect);
	}
	void checkClick(SDL_Event event)
	{
		if (event.type== SDL_MOUSEBUTTONDOWN)
			if (event.button.x >= rect.x && event.button.x <= rect.x + rect.w && event.button.y >= rect.y && event.button.y <= rect.y + rect.h)
				clicked = true;
	}
	bool isClicked()
	{
		return clicked;
	}
};
