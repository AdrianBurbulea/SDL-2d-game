#pragma once
#include <SDL.h>
#include <list>
#include "Texture.h"
#include "background.h"
#include "buton.h"
#include "projectile.h"
#include "dragon.h"

class Game{
	static SDL_Renderer* R;
	Texture* t;
	Background* b;
	int dif_factor;
	int level;
	Dragon Hero;
	std::list<Dragon> enemies;
	std::list<projectile> fire;
	std::list<projectile> ice;
public:
	bool win;
	bool gameOver;
	Game(Texture *T,int dif_factor,int level);
	~Game();
	SDL_Rect input(SDL_Event event);
	void handleEvents();
	void addProjectile(bool hero, Dragon &d);
	void draw();
};

int isNearY(Dragon& d1, Dragon& d2,int y);
int isNearX(Dragon& d1, Dragon& d2,int x);