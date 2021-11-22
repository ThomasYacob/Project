#include "menu.h"
#include "menuSystem.h"
#include "collision.h"
#include "car.h"
#include <time.h>

#define maxIP 30

bool init(SDL_Renderer **gRenderer);
void loadMedia(SDL_Texture **winNotification, SDL_Texture **loseNotification, SDL_Rect p1NotR, SDL_Rect p2NotR, SDL_Renderer *gRenderer, SDL_Window *gWindow, SDL_Texture **playerOne, SDL_Texture **playerTwo, SDL_Texture **gBackground, SDL_Texture **car, SDL_Texture **car1, SDL_Texture **enemyCar1, SDL_Texture **enemyCar2, SDL_Texture **enemyCar3);
void lifesCars(SDL_Renderer *gRenderer, SDL_Window *gWindow, SDL_Texture **heartsP1, SDL_Texture **heartsP2, int p1Lifes, int p2Lifes);
void renderBackground(int carLives, int car2Lives, SDL_Texture **winNotification, SDL_Texture **loseNotification, SDL_Rect p1NotR, SDL_Rect p2NotR, Enemies *enemie1, Enemies *enemie2, Enemies *enemie3, Enemies *enemie4, Enemies *enemie5, Enemies *enemie6, SDL_Renderer *gRenderer, SDL_Texture *gBackground, SDL_Texture **playerOne, SDL_Texture **playerTwo, SDL_Texture **heartsP1, SDL_Texture **heartsP2, SDL_Rect dest, SDL_Rect secondDest, SDL_Rect heartsRecP1, SDL_Rect heartsRecP2);
void close(SDL_Renderer *gRenderer, SDL_Texture *gBackground, SDL_Window *gWindow, SDL_Surface *gScreenSurface, SDL_Texture **playerOne, SDL_Texture **playerTwo);

int main(int argc, char *args[])
{
    menuSystem(argc, args);
    return 0;
}

bool init(SDL_Renderer **gRenderer)
{
    bool test = true;

    // Initiates the window
    SDL_Window *gWindow = NULL;
    SDL_Init(SDL_INIT_VIDEO);
    gWindow = SDL_CreateWindow("STREET RACE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    if (gWindow == 0)
    {
        printf("Couldn't create window: %s\n", SDL_GetError());
        SDL_Quit();
        test = false;
    }

    // Renders to produce an image
    *gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == 0)
    {
        printf("Can't open renderer: %s\n", SDL_GetError());
        SDL_Quit();
        test = false;
    }
    return test;
}

void loadMedia(SDL_Texture **winNotification, SDL_Texture **loseNotification, SDL_Rect p1NotR, SDL_Rect p2NotR, SDL_Renderer *gRenderer, SDL_Window *gWindow, SDL_Texture **playerOne, SDL_Texture **playerTwo, SDL_Texture **gBackground, SDL_Texture **car, SDL_Texture **car1, SDL_Texture **enemyCar1, SDL_Texture **enemyCar2, SDL_Texture **enemyCar3)
{
    bool test = true;

    // Uploads the player cars
    SDL_Surface *gScreenSurface = IMG_Load("resources/cars/car.png");
    if (gScreenSurface == 0)
    {
        printf("Can't open surface: %s\n", SDL_GetError());
        SDL_DestroyRenderer(gRenderer);
        SDL_DestroyWindow(gWindow);
        SDL_Quit();
        test = false;
    }

    *playerOne = SDL_CreateTextureFromSurface(gRenderer, gScreenSurface);
    *playerTwo = SDL_CreateTextureFromSurface(gRenderer, gScreenSurface);

    SDL_FreeSurface(gScreenSurface);
    if (playerOne == 0 || playerTwo == 0)
    {
        printf("error creating texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(gRenderer);
        SDL_DestroyWindow(gWindow);
        SDL_Quit();
        test = false;
    }

    // Loads the map
    SDL_Surface *gBackgroundSurface = IMG_Load("resources/raceTrack.png");
    *gBackground = SDL_CreateTextureFromSurface(gRenderer, gBackgroundSurface);

    // Game over screen
    SDL_Surface *winSurf = IMG_Load("resources/ending/Youwin.png");
    *winNotification = SDL_CreateTextureFromSurface(gRenderer, winSurf);

    SDL_Surface *loseSurf = IMG_Load("resources/ending/youLose.png");
    *loseNotification = SDL_CreateTextureFromSurface(gRenderer, loseSurf);

    // Enemy cars
    SDL_Surface *surf = IMG_Load("resources/cars/carArray.png"); // Loads enemycars
    *enemyCar1 = SDL_CreateTextureFromSurface(gRenderer, surf);
    SDL_FreeSurface(surf);
    surf = IMG_Load("resources/cars/carArray.png");
    if (!surf)
    {
        printf("All is lost\n");
    }

    *enemyCar2 = SDL_CreateTextureFromSurface(gRenderer, surf);
    SDL_FreeSurface(surf);
    surf = IMG_Load("resources/cars/carArray.png");
    if (!surf)
    {
        printf("All is lost\n");
    }

    *enemyCar3 = SDL_CreateTextureFromSurface(gRenderer, surf);
    SDL_FreeSurface(surf);
    surf = IMG_Load("resources/cars/carArray.png");
    if (!surf)
    {
        printf("All is lost\n");
    }

    // Positioning in picture of enemycars
    gCarsclips[0].x = (0);
    gCarsclips[0].y = 0;
    gCarsclips[0].w = 14;
    gCarsclips[0].h = 22;

    gCarsclips[1].x = (92 / 7);
    gCarsclips[1].y = 0;
    gCarsclips[1].w = 14;
    gCarsclips[1].h = 22;

    gCarsclips[2].x = ((92 / 7) * 2);
    gCarsclips[2].y = 0;
    gCarsclips[2].w = 14;
    gCarsclips[2].h = 22;

    gCarsclips[3].x = ((92 / 7) * 3);
    gCarsclips[3].y = 0;
    gCarsclips[3].w = 14;
    gCarsclips[3].h = 22;

    gCarsclips[4].x = ((92 / 7) * 4);
    gCarsclips[4].y = 0;
    gCarsclips[4].w = 14;
    gCarsclips[4].h = 22;

    gCarsclips[5].x = ((92 / 7) * 5);
    gCarsclips[5].y = 0;
    gCarsclips[5].w = 14;
    gCarsclips[5].h = 22;

    gCarsclips[6].x = ((92 / 7) * 6);
    gCarsclips[6].y = 0;
    gCarsclips[6].w = 14;
    gCarsclips[6].h = 22;

    //-----

    gCarsclips1[0].x = (0);
    gCarsclips1[0].y = 0;
    gCarsclips1[0].w = 14;
    gCarsclips1[0].h = 22;

    gCarsclips1[1].x = (92 / 7);
    gCarsclips1[1].y = 0;
    gCarsclips1[1].w = 14;
    gCarsclips1[1].h = 22;

    gCarsclips1[2].x = ((92 / 7) * 2);
    gCarsclips1[2].y = 0;

    gCarsclips1[2].w = 14;
    gCarsclips1[2].h = 22;

    gCarsclips1[3].x = ((92 / 7) * 3);
    gCarsclips1[3].y = 0;
    gCarsclips1[3].w = 14;
    gCarsclips1[3].h = 22;

    gCarsclips1[4].x = ((92 / 7) * 4);
    gCarsclips1[4].y = 0;
    gCarsclips1[4].w = 14;
    gCarsclips1[4].h = 22;

    gCarsclips1[5].x = ((92 / 7) * 5);
    gCarsclips1[5].y = 0;
    gCarsclips1[5].w = 14;
    gCarsclips1[5].h = 22;

    gCarsclips1[6].x = ((92 / 7) * 6);
    gCarsclips1[6].y = 0;
    gCarsclips1[6].w = 14;
    gCarsclips1[6].h = 22;
}

void renderBackground(int carLives, int car2Lives, SDL_Texture **winNotification, SDL_Texture **loseNotification, SDL_Rect p1NotR, SDL_Rect p2NotR, Enemies *enemie1, Enemies *enemie2, Enemies *enemie3, Enemies *enemie4, Enemies *enemie5, Enemies *enemie6, SDL_Renderer *gRenderer, SDL_Texture *gBackground, SDL_Texture **playerOne, SDL_Texture **playerTwo, SDL_Texture **heartsP1, SDL_Texture **heartsP2, SDL_Rect dest, SDL_Rect secondDest, SDL_Rect heartsRecP1, SDL_Rect heartsRecP2)
{
    SDL_RenderClear(gRenderer);
    SDL_RenderCopyEx(gRenderer, gBackground, NULL, NULL, 0, NULL, SDL_FLIP_NONE);

    SDL_RenderCopy(gRenderer, *playerOne, NULL, &dest);
    SDL_RenderCopy(gRenderer, *playerTwo, NULL, &secondDest);
    SDL_RenderCopy(gRenderer, *heartsP1, NULL, &heartsRecP1);
    SDL_RenderCopy(gRenderer, *heartsP2, NULL, &heartsRecP2);

    if (carLives == 0 || car2Lives == 0)
    {
        if (carLives == 0) // If player 1 loses all their lives, he loses and player 2 wins
        {
            SDL_RenderCopyEx(gRenderer, *winNotification, NULL, &p2NotR, 0, NULL, SDL_FLIP_NONE);
            SDL_RenderCopyEx(gRenderer, *loseNotification, NULL, &p1NotR, 0, NULL, SDL_FLIP_NONE);
        }
        // If player 2 loses all their lives, he loses and player 1 wins
        else if (car2Lives == 0)
        {
            SDL_RenderCopyEx(gRenderer, *winNotification, NULL, &p1NotR, 0, NULL, SDL_FLIP_NONE);
            SDL_RenderCopyEx(gRenderer, *loseNotification, NULL, &p2NotR, 0, NULL, SDL_FLIP_NONE);
        }
    }

    renderEnemies(gRenderer, enemie1, enemie2, enemie3, enemie4, enemie5, enemie6);
}

void close(SDL_Renderer *gRenderer, SDL_Texture *gBackground, SDL_Window *gWindow, SDL_Surface *gScreenSurface, SDL_Texture **playerOne, SDL_Texture **playerTwo)
{
    // Shuts down the program and frees up memory
    SDL_DestroyTexture(*playerOne);
    SDL_DestroyTexture(*playerTwo);
    SDL_DestroyTexture(enemyCar1);
    SDL_DestroyTexture(enemyCar2);
    SDL_DestroyTexture(enemyCar3);
    SDL_DestroyTexture(gBackground);
    SDL_DestroyRenderer(gRenderer);
    SDL_FreeSurface(gScreenSurface);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}