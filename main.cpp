#include "Game.h"
#include "Meniu.h"

int HEIGHT = 800;
int WIDTH = 1000;

SDL_Window* window = SDL_CreateWindow("window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
SDL_Renderer* drawable::R = renderer;
SDL_Renderer* Game::R = renderer;
Texture* t = new Texture(renderer);

int main(int argc, char* argv[])
{

    SDL_Init(SDL_INIT_EVERYTHING);
    int FPS = 60;
    int frameDelay = 1000 / FPS;
    int framestart = 0, frametime = 0;
    int level=0;

    while (true)
    {
        Meniu* m = new Meniu(renderer, t->Backgrounds, t->level);
        while (m->display)
        {
            m->Draw();
            int x = m->handleEvents();
            if (x == -1)
                return 0;
            else if (x != 0)
                level = x;
        }
        delete m;

        Game* g = new Game(t, 5, level);
        while (g->gameOver == false)
        {
            framestart = SDL_GetTicks();
            g->handleEvents();
            if (g->gameOver == false)
                g->draw();
            frametime = SDL_GetTicks() - framestart;
            if (frametime < frameDelay)
                SDL_Delay(frameDelay - frametime);
        }
        int x;
        if (g->win == true)
            x = 5;
        else
            x = 6;

        Background* outcome = new Background(t->Backgrounds, x);
        outcome->Draw();
        SDL_RenderPresent(renderer);
        SDL_Delay(3000);
        delete outcome;
        delete g;

    }
    delete t;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}


