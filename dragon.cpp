#include "dragon.h"

Dragon::Dragon(SDL_Texture* t[4], SDL_Rect rect, bool right, int health)
{
	dx = dy = cnt=0;
	alive = true;
	this->right = right;
	this->health = health;
	this->rect = rect;
	for (int i = 0; i < 4; i++)
		texture[i] = t[i];
}
Dragon& Dragon::operator=(const Dragon& d)
{
	this->cnt = 0;
	this->right = d.right;
	this->dx = d.dx;
	this->dy = d.dy;
	this->alive = true;
	this->health = d.health;
	this->rect = d.rect;
	for (int i = 0; i < 4; i++)
		this->texture[i] = d.texture[i];

	return *this;
}
void Dragon::Draw() 
{
	cnt++;
	if (dx == 0)
	{
		if (right == true)
			SDL_RenderCopy(R, texture[0], NULL, &rect);
		else
			SDL_RenderCopy(R, texture[1], NULL, &rect);
	}
	else
	{
		if (dx > 0)
			SDL_RenderCopy(R, texture[2], NULL, &rect);
		else
			SDL_RenderCopy(R, texture[3], NULL, &rect);
	}

	SDL_Rect e;
	e.x = rect.x;
	e.y = rect.y + 2;
	e.h = 2;
	e.w = 10 * health;
	SDL_SetRenderDrawColor(this->R, 255, 0, 0, 0);
	SDL_RenderFillRect(this->R, &e);
}

SDL_Rect Dragon::positon()
{
	SDL_Rect tmp;
	tmp.x = this->rect.x;
	tmp.y = this->rect.y;
	tmp.w = tmp.h = 100;
	return tmp;
}
void Dragon::actualPosition(int x, int y)
{
	dx += x;
	dy += y;
	if (0 < rect.x + dx && rect.x + dx <= 900)
	{
		rect.x += dx;
	}
	else
	{
		if (dx > 0)
		{
			rect.x = 900;
			dx = 0;
		}
		else if (dx < 0)
		{
			rect.x = 0;
			dx = 0;
		}
	}

	if (0 < rect.y + dy && rect.y + dy <= 700)
	{
		rect.y += dy;
	}
	else
	{
		if (dy > 0)
		{
			rect.y = 700;
			dy = 0;
		}
		else if (dy < 0)
		{
			rect.y = 0;
			dy = 0;
		}
	}

	if (dx > 0)
	{
		dx--;
		right = true;
	}
	else if (dx < 0)
	{
		dx++;
		right = false;
	}
	if (dy > 0)
		dy--;
	else if (dy < 0)
		dy++;
}

void Dragon::stopMove()
{
	dx = dy = 0;
}

void Dragon::isHit()
{
	this->health--;
	if (this->health == 0)
		alive = false;
}

void Dragon::setWay(bool right)
{
	this->right = right;
}
