#pragma once
#include "buton.h"

class Dragon:public Buton{
	int dx, dy;
	int health;
	bool alive;
	bool right;
	SDL_Texture* texture[4];
public:
	int cnt;
	Dragon() {};
	Dragon(SDL_Texture* t[4], SDL_Rect rect, bool right, int health);
	Dragon& operator=(const Dragon& d);
	void Draw();
	void stopMove();
	bool way() { return right; }
	bool isAlive() { return alive; }
	void isHit();
	void actualPosition(int x, int y);
	void setWay(bool right);
	SDL_Rect positon();
};
