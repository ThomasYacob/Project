#ifndef menuSystem_h
#define menuSystem_h

#define maxIP 30
#define starting1pos_x 163
#define starting1pos_y 429
#define starting2pos_x 424
#define starting2pos_y 429

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_net.h>
#include <time.h>

#include "menu.h"
#include "collision.h"
#include "car.h"

typedef struct enemies Enemies;

void mainMenu(int argc, char *args[]);
bool init(SDL_Renderer **gRenderer);
void loadMedia(SDL_Texture **p1Notification, SDL_Texture **p2Notification, SDL_Rect p1NotR, SDL_Rect p2NotR, SDL_Renderer *gRenderer, SDL_Window *gWindow, SDL_Texture **playerOne, SDL_Texture **playerTwo, SDL_Texture **gBackground, SDL_Texture **car, SDL_Texture **car1, SDL_Texture **enemyCar1, SDL_Texture **enemyCar2, SDL_Texture **enemyCar3);
void lifesCars(SDL_Renderer *gRenderer, SDL_Window *gWindow, SDL_Texture **heartsP1, SDL_Texture **heartsP2, int P1Lifes, int P2Lifes);
void renderBackground(int carLives, int car2Lives, SDL_Texture **p1Notification, SDL_Texture **p2Notification, SDL_Rect p1NotR, SDL_Rect p2NotR, Enemies *enemie1, Enemies *enemie2, Enemies *enemie3, Enemies *enemie4, Enemies *enemie5, Enemies *enemie6, SDL_Renderer *gRenderer, SDL_Texture *gBackground, SDL_Texture **playerOne, SDL_Texture **playerTwo, SDL_Texture **heartsP1, SDL_Texture **heartsP2, SDL_Rect dest, SDL_Rect secondDest, SDL_Rect heartsRecP1, SDL_Rect heartsRecP2);
void close(SDL_Renderer *gRenderer, SDL_Texture *gBackground, SDL_Window *gWindow, SDL_Surface *gScreenSurface, SDL_Texture **playerOne, SDL_Texture **playerTwo);
void renderEnemies(SDL_Renderer *gRenderer, Enemies *enemie1, Enemies *enemie2, Enemies *enemie3, Enemies *enemie4, Enemies *enemie5, Enemies *enemie6);

static SDL_Texture *gBackground = NULL;
static SDL_Texture *enemyCar1 = NULL;
static SDL_Texture *enemyCar2 = NULL;
static SDL_Texture *enemyCar3 = NULL;

SDL_Rect gCarsclips[7];
SDL_Rect gCarsclips1[7];

#endif