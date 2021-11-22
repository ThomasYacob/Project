//Car.c C file for Car

#include "car.h"

#define PUBLIC
#define PRIVATE static

PUBLIC void lifesCars(SDL_Renderer *gRenderer, SDL_Window *gWindow, SDL_Texture **heartsP1, SDL_Texture **heartsP2, int p1Lifes, int p2Lifes)
{

    if (p1Lifes == 0)
    {
        SDL_DestroyTexture(*heartsP1);
        SDL_Surface *lifeZero = IMG_Load("resources/lifes/3Tomma.png"); // Displays zero filled hearts for player 1
        *heartsP1 = SDL_CreateTextureFromSurface(gRenderer, lifeZero);
    }
    else if (p1Lifes == 1)
    {
        SDL_DestroyTexture(*heartsP1);
        SDL_Surface *lifeOne = IMG_Load("resources/lifes/2Tomma.png"); // Displays one filled heart for player 1
        *heartsP1 = SDL_CreateTextureFromSurface(gRenderer, lifeOne);
    }
    else if (p1Lifes == 2)
    {
        SDL_DestroyTexture(*heartsP1);
        SDL_Surface *lifeTwo = IMG_Load("resources/lifes/1TomtHjarta.png"); // Displays two filled hearts for player 1
        *heartsP1 = SDL_CreateTextureFromSurface(gRenderer, lifeTwo);
    }
    else if (p1Lifes == 3)
    {
        SDL_DestroyTexture(*heartsP1);
        SDL_Surface *lifeThree = IMG_Load("resources/lifes/TreHela.png"); // Displays three filled hearts for player 1
        *heartsP1 = SDL_CreateTextureFromSurface(gRenderer, lifeThree);
    }
    if (p2Lifes == 0)
    {
        SDL_DestroyTexture(*heartsP2);
        SDL_Surface *lifeZeroP2 = IMG_Load("resources/lifes/3Tomma.png"); // Displays zero filled hearts for player 2
        *heartsP2 = SDL_CreateTextureFromSurface(gRenderer, lifeZeroP2);
    }
    else if (p2Lifes == 1)
    {
        SDL_DestroyTexture(*heartsP2);
        SDL_Surface *p2LifeOne = IMG_Load("resources/lifes/2Tomma.png"); // Displays one filled heart for player 2
        *heartsP2 = SDL_CreateTextureFromSurface(gRenderer, p2LifeOne);
    }
    else if (p2Lifes == 2)
    {
        SDL_DestroyTexture(*heartsP2);
        SDL_Surface *p2LifeTwo = IMG_Load("resources/lifes/1TomtHjarta.png"); // Displays two filled hearts for player 2
        *heartsP2 = SDL_CreateTextureFromSurface(gRenderer, p2LifeTwo);
    }
    else if (p2Lifes == 3)
    {
        SDL_DestroyTexture(*heartsP2);
        SDL_Surface *p2LifeThree = IMG_Load("resources/lifes/TreHela.png"); // Displays three filled hearts for player 2
        *heartsP2 = SDL_CreateTextureFromSurface(gRenderer, p2LifeThree);
    }
}

// Counts down the lights to begin the game
PUBLIC int countdown(SDL_Renderer *gRenderer, SDL_Texture *gBackground, SDL_Texture **light, SDL_Rect lightR)
{
    int minutes = 0;
    int seconds = 0;
    int milliseconds = 0;
    int countdownInSec = 0, timeLeft = 0;
    int secondsr = 2;

    clock_t startTime, countTime;
    countdownInSec = 10;

    startTime = clock();
    timeLeft = countdownInSec - seconds;

    while (timeLeft > 0)
    {
        countTime = clock();
        milliseconds = countTime - startTime;
        seconds = (milliseconds / (CLOCKS_PER_SEC)) - (minutes * 60);

        if (seconds == 2 && secondsr == 2)
        {
            // Displays the light at second one
            SDL_Surface *Light = IMG_Load("resources/counter/1rod.png");
            *light = SDL_CreateTextureFromSurface(gRenderer, Light);

            SDL_RenderCopyEx(gRenderer, *light, NULL, &lightR, 0, NULL, SDL_FLIP_NONE);
            SDL_RenderPresent(gRenderer);
            secondsr = 3;
        }

        if (seconds == 3 && secondsr == 3)
        {
            // Displays the light at second two
            SDL_DestroyTexture(*light);
            SDL_Surface *light2 = IMG_Load("resources/counter/2rod.png");
            *light = SDL_CreateTextureFromSurface(gRenderer, light2);

            SDL_RenderCopyEx(gRenderer, *light, NULL, &lightR, 0, NULL, SDL_FLIP_NONE);
            SDL_RenderPresent(gRenderer);
            secondsr = 4;
        }

        if (seconds == 4 && secondsr == 4)
        {
            // Displays the light at second three
            SDL_DestroyTexture(*light);
            SDL_Surface *light3 = IMG_Load("resources/counter/3rod.png");
            *light = SDL_CreateTextureFromSurface(gRenderer, light3);

            SDL_RenderCopyEx(gRenderer, *light, NULL, &lightR, 0, NULL, SDL_FLIP_NONE);
            SDL_RenderPresent(gRenderer);
            secondsr = 5;
        }

        if (seconds == 5 && secondsr == 5)
        {
            // Displays the lights that the cars are ready to run
            SDL_DestroyTexture(*light);
            SDL_Surface *light4 = IMG_Load("resources/counter/tregrona.png");
            *light = SDL_CreateTextureFromSurface(gRenderer, light4);

            SDL_RenderCopyEx(gRenderer, *light, NULL, &lightR, 0, NULL, SDL_FLIP_NONE);
            SDL_RenderPresent(gRenderer);
            secondsr = 6;
        }

        if (seconds == 6)
        {
            SDL_DestroyTexture(*light);
            return 1;
        }
    }
    return 1;
}

PUBLIC int checkIfGameOver(int p1Lives, int p2Lives)
{
    if (p1Lives == 0 || p2Lives == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}