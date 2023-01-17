#include "Game.h"
int drag_positionx[4] = {150,140,700,600};
int drag_positiony[4] = {120,500,210,700};
int dx[4] = { -370,-260,380,290 };
int dy[4] = { 0,10,-10,15 };
Game::Game(Texture* T,int dif_factor, int level)
{
	gameOver = false;
	win = false;
	this->dif_factor = dif_factor;
	this->level = level;
    t = T;
	b = new Background(t->Backgrounds, level);
    SDL_Rect e;
    e.w = e.h = 100;
    e.x = e.y = 410;
    Dragon *tmp=new Dragon(t->Hero, e, true, 5+level-1);
    Hero = *tmp;
    delete tmp;
    for (int i = 1; i <= level; i++)
    {
        e.x = drag_positionx[i-1];
        e.y = drag_positiony[i-1];
        tmp = new Dragon(t->Enemy, e, true, 3);
        enemies.push_back(*tmp);
    }
}

Game::~Game()
{
    delete b;
}

SDL_Rect Game::input(SDL_Event event)
{
	SDL_Rect e;
	e.x = e.y = e.w = e.h = 0;
    switch (event.type)
    {
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_a:
            e.x = -1;
            break;
        case SDLK_s:
            e.y = 1;
            break;
        case SDLK_w:
            e.y = -1;
            break;
        case SDLK_d:
            e.x = 1;
            break;
        case SDLK_SPACE:
            if (Hero.cnt > 70)
            {
                addProjectile(true, Hero);
                Hero.cnt = 0;
            }
            break;
        default:
            break;
        }
    break;
    case SDL_QUIT:
        gameOver = true;
        break;

    default:
        break;
    }
	return e;
}


void Game::addProjectile(bool hero, Dragon &d)
{
    int aux;
    projectile* p;
    SDL_Rect e;
    e.w = e.h = 50;
    if (d.way() == true)
    {
        aux = 1;
        e.x = d.positon().x + 45;
        e.y = d.positon().y - 12;
    }
    else
    {
        aux = -1;
        e.x = d.positon().x - 10;
        e.y = d.positon().y - 11;           
    }

    if (hero == true)
    {
        p = new projectile(aux * dif_factor, e, t->fire);
        fire.push_back(*p);
    }
    else
    {
        p = new projectile(aux * dif_factor, e, t->ice);
        ice.push_back(*p);
    }

    delete p;
}

void Game::draw()
{
    b->Draw();

    Hero.Draw();

    std::list<Dragon>::iterator i;
    for (i = enemies.begin(); i != enemies.end(); i++)
        i->Draw();

    std::list<projectile>::iterator j;
    for (j = fire.begin(); j != fire.end(); j++)
        j->Draw();
    for (j = ice.begin(); j != ice.end(); j++)
        j->Draw();

    SDL_RenderPresent(R);
}

void Game::handleEvents()
{
    int m = 0;
    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
        SDL_Rect tmp = this->input(event);
        Hero.actualPosition(tmp.x*dif_factor, tmp.y*dif_factor);
    }
    else
    {
        Hero.actualPosition(0, 0);
    }

    std::list<projectile>::iterator i,j;
    std::list<Dragon>::iterator k,l;
    for (k = enemies.begin(); k != enemies.end(); k++, m++)
    {
        int x = isNearX(Hero, *k, dx[m]);
        int y = isNearY(Hero, *k, dy[m]);
            if (x != 1)
            {
                if (x == -1)
                    k->actualPosition(3, 0);
                else if (x == -2)
                    k->actualPosition(-3, 0);
            }
            else if (y != 1)
            {
                if (y == -1)
                    k->actualPosition(0, 3);
                else if (y == -2)
                    k->actualPosition(0, -3);
            }
            else
                k->actualPosition(0, 0);

        if (k->cnt > 60 + (level - 1) * 30 && isNearY(Hero,*k, 5) > 0)
        {
            if (k->positon().x > Hero.positon().x)
                k->setWay(false);
            else
                k->setWay(true);
            addProjectile(false, *k);
            k->cnt = 0;
            k->stopMove();
        }
    }
    i = fire.begin();
    while (i != fire.end())
    {
        if (i->handleEvents() == 1)
        {
            j = i;
            i++;
            fire.erase(j);
        }
        else
        {
            int ok = 0;
            k = enemies.begin();
            while (k != enemies.end()&&!ok)
            {
                if (i->checkColison(k->positon()))
                {
                    k->isHit();
                    ok = 1;
                    j = i;
                    i++;
                    fire.erase(j);
                }
                k++;
            }
            if (!ok)
                i++;
        }
    }
    i = ice.begin();
    while (i != ice.end())
    {
        if (i->handleEvents() == 1)
        {
            j = i;
            i++;
            ice.erase(j);
        }
        else
        {
            if (i->checkColison(Hero.positon()))
            {
                Hero.isHit();
                j = i;
                i++;
                ice.erase(j);
            }
            else
                i++;
        }
    }
    if (Hero.isAlive() == false)
        gameOver = true;

    k = enemies.begin();
    while (k != enemies.end())
    {
        if (k->isAlive() == false)
        {
            l = k;
            k++;
            enemies.erase(l);
        }
        else
            k++;
    }
    if (enemies.empty())
    {
        gameOver = true;
        win = true;
    }
}


int isNearY(Dragon& d1, Dragon& d2,int y)
{
    int e = d1.positon().y + y;
    if (e >= d2.positon().y && e - d2.positon().y < 20)
        return 1;
    if (d2.positon().y > e && d2.positon().y - e < 20)
        return 1;
    if (e > d2.positon().y)
        return -1;
    if (d2.positon().y > e)
        return -2;
}

int isNearX(Dragon& d1, Dragon& d2,int x)
{
    int e = d1.positon().x + x;
    if (e >= d2.positon().x && e - d2.positon().x < 60)
        return 1;
    if (d2.positon().x > e && d2.positon().x - e < 60)
        return 1;
    if (e > d2.positon().x)
        return -1;
    if (d2.positon().x > e)
        return -2;
}