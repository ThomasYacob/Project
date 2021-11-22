#include "menu.h"

struct enemies
{
    float x, y;
    float dy;
    float ang;
};

typedef struct enemies Enemies;

int menuSystem(int argc, char *args[])
{
    int width = 640;
    int heigth = 480;

    SDL_Texture *gBackground = NULL;
    SDL_Texture *start = NULL;
    SDL_Texture *instructions = NULL;
    SDL_Texture *quit = NULL;
    SDL_Texture *instructionPicture = NULL;
    SDL_Texture *closeInst = NULL;

    SDL_Event event;

    // Creates the coordinates for the mouse
    int Mx = 0;
    int My = 0;

    SDL_Window *gWindow = NULL;
    gWindow = SDL_CreateWindow("STREET RACE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, heigth, 0);

    SDL_Renderer *gRenderer = NULL;
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    int continuer = 1;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Surface *backgroundMenu = IMG_Load("resources/menu/streetrace.png");
    gBackground = SDL_CreateTextureFromSurface(gRenderer, backgroundMenu);

    // Creates the start button
    SDL_Surface *backgroundStart = IMG_Load("resources/menu/start.png");
    start = SDL_CreateTextureFromSurface(gRenderer, backgroundStart);

    SDL_Rect start_Rect;
    {
        start_Rect.x = 340;
        start_Rect.y = 70;
        start_Rect.w = 210;
        start_Rect.h = 110;
    }

    // Creates the instruction button
    SDL_Surface *backgroundInstructions = IMG_Load("resources/menu/instructions.png");
    instructions = SDL_CreateTextureFromSurface(gRenderer, backgroundInstructions);

    SDL_Rect instructions_Rect;
    {
        instructions_Rect.x = 260;
        instructions_Rect.y = 180;
        instructions_Rect.w = 370;
        instructions_Rect.h = 120;
    }

    // Creates the quit button
    SDL_Surface *backgroundQuit = IMG_Load("resources/menu/quit.png");
    quit = SDL_CreateTextureFromSurface(gRenderer, backgroundQuit);

    SDL_Rect quit_Rect;
    {
        quit_Rect.x = 340;
        quit_Rect.y = 320;
        quit_Rect.w = 190;
        quit_Rect.h = 90;
    }

    // Creates close instruction
    SDL_Surface *closeInstructions = IMG_Load("resources/menu/closeInstructions.png");
    closeInst = SDL_CreateTextureFromSurface(gRenderer, closeInstructions);

    SDL_Rect closeInstructions_Rect;
    {
        closeInstructions_Rect.x = 110;
        closeInstructions_Rect.y = 85;
        closeInstructions_Rect.w = 50;
        closeInstructions_Rect.h = 50;
    }

    SDL_Surface *bInstructions = IMG_Load("resources/menu/backgroundinstructions.png");
    instructionPicture = SDL_CreateTextureFromSurface(gRenderer, bInstructions);

    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);
    SDL_RenderCopyEx(gRenderer, gBackground, NULL, NULL, 0, NULL, SDL_FLIP_NONE);
    SDL_RenderCopyEx(gRenderer, start, NULL, &start_Rect, 0, NULL, SDL_FLIP_NONE);
    SDL_RenderCopyEx(gRenderer, instructions, NULL, &instructions_Rect, 0, NULL, SDL_FLIP_NONE);
    SDL_RenderCopyEx(gRenderer, quit, NULL, &quit_Rect, 0, NULL, SDL_FLIP_NONE);
    SDL_RenderPresent(gRenderer);

    while (continuer)
    {
        while (SDL_PollEvent(&event))
        {
            // If the mouse moves
            if (event.type == SDL_MOUSEMOTION)
            {
                Mx = event.motion.x;
                My = event.motion.y;
            }

            // If the mousebutton is pressed
            if (event.type == SDL_MOUSEMOTION)
            {
                // If left mousebutton is pressed
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    Mx = event.button.x;
                    My = event.button.y;

                    // If the mouse pointer is hovered over the button you click on
                    if ((Mx > start_Rect.x) && (Mx < start_Rect.x + start_Rect.w) && (My > start_Rect.y) && (My < start_Rect.y + start_Rect.h))
                    {
                        SDL_RenderFillRect(gRenderer, &start_Rect);
                    }
                }
            }

            // If mousebutton no longer is pressed
            if (event.type == SDL_MOUSEBUTTONUP)
            {
                // If left mousebutton no longer is pressed
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    Mx = event.button.x;
                    My = event.button.y;

                    // If mousepointer is hovered over the button whilst you release it
                    if ((Mx > start_Rect.x) && (Mx < start_Rect.x + start_Rect.w) && (My > start_Rect.y) && (My < start_Rect.y + start_Rect.h))
                    {
                        SDL_DestroyWindow(gWindow);
                        mainMenu(argc, args);
                        SDL_FreeSurface(backgroundMenu);
                        SDL_Quit();
                        return 0;
                    }
                    else if ((Mx > instructions_Rect.x) && (Mx < instructions_Rect.x + instructions_Rect.w) && (My > instructions_Rect.y) && (My < instructions_Rect.y + instructions_Rect.h))
                    {
                        SDL_RenderCopyEx(gRenderer, instructionPicture, NULL, NULL, 0, NULL, SDL_FLIP_NONE);
                        SDL_RenderCopyEx(gRenderer, closeInst, NULL, &closeInstructions_Rect, 0, NULL, SDL_FLIP_NONE);
                        SDL_RenderPresent(gRenderer);
                    }
                    else if ((Mx > quit_Rect.x) && (Mx < quit_Rect.x + quit_Rect.w) && (My > quit_Rect.y) && (My < quit_Rect.y + quit_Rect.h))
                    {
                        return 0;
                    }
                    if ((Mx > closeInstructions_Rect.x) && (Mx < closeInstructions_Rect.x + closeInstructions_Rect.w) && (My > closeInstructions_Rect.y) && (My < closeInstructions_Rect.y + closeInstructions_Rect.h))
                    {
                        SDL_RenderCopyEx(gRenderer, gBackground, NULL, NULL, 0, NULL, SDL_FLIP_NONE);
                        SDL_RenderCopyEx(gRenderer, start, NULL, &start_Rect, 0, NULL, SDL_FLIP_NONE);
                        SDL_RenderCopyEx(gRenderer, instructions, NULL, &instructions_Rect, 0, NULL, SDL_FLIP_NONE);
                        SDL_RenderCopyEx(gRenderer, quit, NULL, &quit_Rect, 0, NULL, SDL_FLIP_NONE);
                        SDL_RenderPresent(gRenderer);
                    }
                }
            }
            if (event.type == SDL_QUIT)
            {
                continuer = 0;
                break;
            }
        }
    }

    SDL_FreeSurface(backgroundMenu);
    SDL_Quit();

    return EXIT_SUCCESS;
}