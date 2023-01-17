#include "Texture.h"

Texture::Texture(SDL_Renderer *R)
{
	char H[4][20] = { "assets/dragon0.png", "assets/dragon1.png", "assets/dragon2.png", "assets/dragon3.png" };
	char E[4][20] = { "assets/fragon0.png", "assets/fragon1.png", "assets/fragon2.png", "assets/fragon3.png" };
	char I[2][30] = { "assets/ice_right.png" ,"assets/ice_left.png" };
	char F[2][26] = { "assets/fireball_right.png" ,"assets/fireball_left.png" };
	char b[13] = "assets/_.png";
	char L[14] = "assets/l_.png";
	SDL_Surface* surf = NULL;
	for (int i = 0; i < 4; i++)
	{
		surf = IMG_Load(H[i]);
		Hero[i] = SDL_CreateTextureFromSurface(R, surf);
		SDL_FreeSurface(surf);
	}
	for (int i = 0; i < 4; i++)
	{
		surf = IMG_Load(E[i]);
		Enemy[i] = SDL_CreateTextureFromSurface(R, surf);
		SDL_FreeSurface(surf);
	}
	for (int i = 0; i < 7; i++)
	{
		b[7] = i+48;
		surf = IMG_Load(b);
		Backgrounds[i] = SDL_CreateTextureFromSurface(R, surf);
	}
	for (int i = 0; i < 2; i++)
	{
		surf = IMG_Load(F[i]);
		fire[i] = SDL_CreateTextureFromSurface(R, surf);
		SDL_FreeSurface(surf);
	}
	for (int i = 0; i < 2; i++)
	{
		surf = IMG_Load(I[i]);
		ice[i] = SDL_CreateTextureFromSurface(R, surf);
		SDL_FreeSurface(surf);
	}
	for (int i = 0; i < 4; i++)
	{
		L[8] = i + 49;
		surf = IMG_Load(L);
		level[i]= SDL_CreateTextureFromSurface(R, surf);
		SDL_FreeSurface(surf);
	}
}

Texture::~Texture()
{
	for (int i = 0; i < 4; i++)
	{
		SDL_DestroyTexture(Hero[i]);
		Hero[i] = NULL;
	}
	
	for (int i = 0; i < 4; i++)
	{
		SDL_DestroyTexture(Enemy[i]);
		Enemy[i] = NULL;
	}

	for (int i = 0; i < 5; i++)
	{
		SDL_DestroyTexture(Backgrounds[i]);
		Backgrounds[i] = NULL;
	}
	
	for (int i = 0; i < 2; i++)
	{
		SDL_DestroyTexture(fire[i]);
		fire[i] = NULL;
	}

	for (int i = 0; i < 2; i++)
	{
		SDL_DestroyTexture(ice[i]);
		ice[i] = NULL;
	}

}