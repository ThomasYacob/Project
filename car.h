//Car.h header fil för Car

#ifndef car_h
#define car_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_net.h>

#include "collision.h"

typedef struct Car_type *Car;

void lifesCars(SDL_Renderer *gRenderer, SDL_Window *gWindow, SDL_Texture **heartsP1, SDL_Texture **heartsP2, int p1Lifes, int p2Lifes);
int countdown(SDL_Renderer *gRenderer, SDL_Texture *gBackground, SDL_Texture **light, SDL_Rect lightR);
int checkIfGameOver(int p1Lives, int p2Lives);

#endif