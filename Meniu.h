#pragma once
#include "buton.h"

class Meniu {
	SDL_Renderer* R;
	Background* F;
	Buton* b[4];
public:
	bool display;
	Meniu(SDL_Renderer* r,SDL_Texture* back[], SDL_Texture* but[])
	{
		this->R = r;
		display = true;
		SDL_Rect e;
		e.w = 150;
		e.h = 220;
		e.y = 500;
		e.x = 70;
		F = new Background(back, 0);
		for (int i = 0; i < 4; i++)
		{
			b[i] = new Buton(but, i, e);
			e.x += 250;
		}
	}
	int handleEvents()
	{
		SDL_Event event;
		SDL_PollEvent(&event);
		if (event.type== SDL_QUIT)
		{
			display = false;
			return -1;
		}
		for (int i = 0; i < 4; i++)
		{
			b[i]->checkClick(event);
			if (b[i]->isClicked())
			{
				display = false;
				return i + 1;
			}
		}
		return 0;
	}
	void Draw()
	{
		F->Draw();
		for (int i = 0; i < 4; i++)
			b[i]->Draw();
		SDL_RenderPresent(R);
	}
	~Meniu()
	{
		delete F;
		for (int i = 0; i < 4; i++)
		{
			if (b[i] != NULL)
				delete b[i];
			b[i] = NULL;
		}
	}
};
