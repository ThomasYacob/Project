#include "menuSystem.h"
#include "enemyCars.h"

struct enemies
{
    float x, y;
    float dy;
    float ang;
};

void mainMenu(int argc, char *args[])
{
    int width = 640;
    int height = 480;
    int velocity = 300;

    SDL_Texture *gBackground = NULL;
    SDL_Window *gWindow = NULL;
    SDL_Texture *car = NULL;
    SDL_Texture *car1 = NULL;
    SDL_Texture *lifeP1 = NULL;
    SDL_Texture *lifeP2 = NULL;
    SDL_Texture *light = NULL;
    SDL_Renderer *gRenderer = NULL;
    SDL_Surface *gScreenSurface = NULL;

    SDL_Texture *p1Notification = NULL;
    SDL_Texture *p2Notification = NULL;

    int korCountdown = 0;
    int game = 0;
    int player = 0;

    //Car 1
    SDL_Texture *playerOne = NULL;
    SDL_Rect dest;
    SDL_QueryTexture(playerOne, NULL, NULL, &dest.w, &dest.h);
    int carLives = 3;
    int carOldLives = 3;

    //Car 2
    SDL_Texture *playerTwo = NULL;
    SDL_Rect secondDest;
    SDL_QueryTexture(playerTwo, NULL, NULL, &secondDest.w, &secondDest.h);
    int car2Lives = 3;
    int car2OldLives = 3;

    //Liv 1
    SDL_Rect lifeP1Rec;
    lifeP1Rec.x = 0;
    lifeP1Rec.y = 170;
    lifeP1Rec.h = 90;
    lifeP1Rec.w = 40;

    //Liv 2
    SDL_Rect lifeP2Rec;
    lifeP2Rec.x = 600;
    lifeP2Rec.y = 170;
    lifeP2Rec.h = 90;
    lifeP2Rec.w = 40;

    // Light
    SDL_Rect lightR;
    lightR.x = 300;
    lightR.y = 120;
    lightR.h = 90;
    lightR.w = 40;

    //P1not
    SDL_Rect p1NotR;
    p1NotR.x = 120;
    p1NotR.y = 200;
    p1NotR.h = 100;
    p1NotR.w = 150;

    //P2not
    SDL_Rect p2NotR;
    p2NotR.x = 390;
    p2NotR.y = 200;
    p2NotR.h = 100;
    p2NotR.w = 150;

    UDPsocket sd;
    IPaddress srvadd;
    UDPpacket *p;
    UDPpacket *p2;

    char ipAddress[maxIP];
    printf("Enter IP-Adress: ");
    scanf("%s", ipAddress);

    if (SDLNet_Init() < 0)
    {
        fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
        exit(EXIT_FAILURE);
    }

    if (!(sd = SDLNet_UDP_Open(0)))
    {
        fprintf(stderr, "SDLNet_UDP_Open: %s\n", SDLNet_GetError());
        exit(EXIT_FAILURE);
    }

    if (SDLNet_ResolveHost(&srvadd, ipAddress, 2000) == -1)
    {
        fprintf(stderr, "SDLNet_ResolveHost(%s): %s\n", ipAddress, SDLNet_GetError());
        exit(EXIT_FAILURE);
    }

    if (!((p = SDLNet_AllocPacket(512)) && (p2 = SDLNet_AllocPacket(512))))
    {
        fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
        exit(EXIT_FAILURE);
    }

    // Get scale and dimensions of the texture
    SDL_Rect playerCollider;
    SDL_Rect player2Collider;

    dest.w = width / 10;
    dest.h = height / 10;

    playerCollider.w = dest.w;
    playerCollider.h = dest.h;

    secondDest.w = width / 10;
    secondDest.h = height / 10;

    player2Collider.w = secondDest.w;
    player2Collider.h = secondDest.h;

    float x_pos = starting1pos_x;
    float y_pos = starting1pos_y;
    float x_posOld = x_pos;
    float y_posOld = y_pos;
    float x_vel = 0;
    float y_vel = 0;

    float x_pos2 = starting2pos_x;
    float y_pos2 = starting2pos_y;
    float x_pos2Old = x_pos2;
    float y_pos2Old = y_pos2;
    float x_vel2 = 0;
    float y_vel2 = 0;

    int up = 0;
    int down = 0;
    int left = 0;
    int right = 0;

    if (init(&gRenderer) == 0)
    {
        printf("Failed to initialize!\n");
    }

    // Enemy cars starting positions
    Enemies enemie1, enemie2, enemie3, enemie4, enemie5, enemie6;

    enemie1.x = 110;
    enemie1.y = 0;
    enemie1.dy = 0;
    enemie1.ang = 0;

    enemie2.x = 175;
    enemie2.y = 0;
    enemie2.dy = 0;
    enemie2.ang = 0;

    enemie3.x = 240;
    enemie3.y = 0;
    enemie3.dy = 0;
    enemie3.ang = 0;

    enemie4.x = 370;
    enemie4.y = 0;
    enemie4.dy = 0;
    enemie4.ang = 0;

    enemie5.x = 435;
    enemie5.y = 0;
    enemie5.dy = 0;
    enemie5.ang = 0;

    enemie6.x = 500;
    enemie6.y = 0;
    enemie6.dy = 0;
    enemie6.ang = 0;

    loadMedia(&p1Notification, &p2Notification, p1NotR, p2NotR, gRenderer, gWindow, &playerOne, &playerTwo, &gBackground, &car, &car1, &enemyCar1, &enemyCar2, &enemyCar3);
    sprintf((char *)p->data, "%d\n", 1);
    p->address.host = srvadd.host; /* Set the destination host */
    p->address.port = srvadd.port; /* And destination port */
    p->len = strlen((char *)p->data) + 1;
    SDLNet_UDP_Send(sd, -1, p);
    while (player == 0)
    {
        if (SDLNet_UDP_Recv(sd, p2))
        {
            int a;
            sscanf((char *)p2->data, "%d\n", &a);
            player = a;
            printf("You are player %d\n", player);
        }
    }
    int countDownWait = 1;
    while (countDownWait)
    {
        if (SDLNet_UDP_Recv(sd, p2))
        {
            int a;
            sscanf((char *)p2->data, "%d\n", &a);
            if (a == 50)
            {
                countDownWait = 0;
                printf("Countdown is starting\n");
                break;
            }
        }
    }

    // Event for gameplay
    while (1)
    {
        if (game == 0)
        {
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode)
                    {
                    case SDL_SCANCODE_UP:
                    case SDL_SCANCODE_W:
                        up = 1;
                        break;
                    case SDL_SCANCODE_LEFT:
                    case SDL_SCANCODE_A:
                        left = 1;
                        break;

                    case SDL_SCANCODE_DOWN:
                    case SDL_SCANCODE_S:
                        down = 1;
                        break;

                    case SDL_SCANCODE_RIGHT:
                    case SDL_SCANCODE_D:
                        right = 1;
                        break;
                    }
                    break;
                case SDL_KEYUP:
                    switch (event.key.keysym.scancode)
                    {
                    case SDL_SCANCODE_UP:
                    case SDL_SCANCODE_W:
                        up = 0;
                        break;
                    case SDL_SCANCODE_LEFT:
                    case SDL_SCANCODE_A:
                        left = 0;
                        break;
                    case SDL_SCANCODE_DOWN:
                    case SDL_SCANCODE_S:
                        down = 0;
                        break;
                    case SDL_SCANCODE_RIGHT:
                    case SDL_SCANCODE_D:
                        right = 0;
                        break;
                    }
                    break;
                }
            }

            if (event.type == SDL_QUIT)
            {
                break;
            }
        }
        if (player == 1)
        {
            x_vel = y_vel = 0;
            if (up && !down)
                y_vel = -velocity;
            if (down && !up)
                y_vel = velocity;
            if (left && !right)
                x_vel = -velocity;
            if (right && !left)
                x_vel = velocity;

            x_pos += x_vel / 60;
            y_pos += y_vel / 60;
            playerCollider.y = y_pos;

            // Sends and recieves positions
            // if (x_posOld != x_pos || y_posOld != y_pos || carLives != carOldLives)
            // {
            printf("Packet sends to player 2: %d %d %d\n", (int)x_pos, (int)y_pos, (int)carLives);
            sprintf((char *)p->data, "%d %d %d\n", (int)x_pos, (int)y_pos, (int)carLives);
            p->len = strlen((char *)p->data) + 1;
            SDLNet_UDP_Send(sd, -1, p);
            x_posOld = x_pos;
            y_posOld = y_pos;
            carOldLives = carLives;
            // }
            if (SDLNet_UDP_Recv(sd, p2))
            {
                int a, b, c;
                sscanf((char *)p2->data, "%d %d %d\n", &a, &b, &c);
                x_pos2 = a;
                y_pos2 = b;
                car2Lives = c;
                printf("Packet incoming from player 2: %d %d %d\n", secondDest.x, secondDest.y, car2Lives);
            }
        }

        else if (player == 2)
        {
            x_vel2 = y_vel2 = 0;
            if (up && !down)
                y_vel2 = -velocity;
            if (down && !up)
                y_vel2 = velocity;
            if (left && !right)
                x_vel2 = -velocity;
            if (right && !left)
                x_vel2 = velocity;

            x_pos2 += x_vel2 / 60;
            y_pos2 += y_vel2 / 60;
            player2Collider.y = y_pos2;

            // if (x_pos2Old != x_pos2 || y_pos2Old != y_pos2 || car2Lives != car2OldLives)
            // {
            printf("Packet sends to player 1: %d %d %d\n", (int)x_pos2, (int)y_pos2, (int)car2Lives);
            sprintf((char *)p->data, "%d %d %d\n", (int)x_pos2, (int)y_pos2, (int)car2Lives);
            p->len = strlen((char *)p->data) + 1;
            SDLNet_UDP_Send(sd, -1, p);
            x_pos2Old = x_pos2;
            y_pos2Old = y_pos2;
            car2OldLives = car2Lives;
            // }
            if (SDLNet_UDP_Recv(sd, p2))
            {
                int a, b, c;
                sscanf((char *)p2->data, "%d %d %d\n", &a, &b, &c);
                x_pos = a;
                y_pos = b;
                carLives = c;
                printf("Packet incoming from player 1: %d %d %d\n", dest.x, dest.y, carLives);
            }
        }

        // player one out of reach bounds and lane bounds
        if (x_pos <= 0)
            x_pos = 0;
        playerCollider.x = x_pos;
        if (y_pos <= 0)
            y_pos = 0;
        playerCollider.y = y_pos;
        if (x_pos >= width - dest.w)
            x_pos = width - dest.w;
        playerCollider.x = x_pos;
        if (y_pos >= height - dest.h)
            y_pos = height - dest.h;
        playerCollider.y = y_pos;
        if (x_pos <= 86)
            x_pos = 87;
        if (x_pos >= 233)
            x_pos = 232;

        // player two out of reach bounds and lane bounds
        if (x_pos2 <= 0)
            x_pos2 = 0;
        player2Collider.x = x_pos2;
        if (y_pos2 <= 0)
            y_pos2 = 0;
        player2Collider.y = y_pos2;
        if (x_pos2 >= width - dest.w)
            x_pos2 = width - dest.w;
        player2Collider.x = x_pos2;
        if (y_pos2 >= height - dest.h)
            y_pos2 = height - dest.h;
        player2Collider.y = y_pos2;
        if (x_pos2 <= 346)
            x_pos2 = 347;
        if (x_pos2 >= 493)
            x_pos2 = 492;

        // Enemie cars positioning and size of cars
        SDL_Rect rect1 = {enemie1.x, enemie1.y, 17 * 2, 22 * 2};
        SDL_Rect rect2 = {enemie2.x, enemie2.y, 17 * 2, 22 * 2};
        SDL_Rect rect3 = {enemie3.x, enemie3.y, 17 * 2, 22 * 2};
        SDL_Rect rect4 = {enemie4.x, enemie4.y, 17 * 2, 22 * 2};
        SDL_Rect rect5 = {enemie5.x, enemie5.y, 17 * 2, 22 * 2};
        SDL_Rect rect6 = {enemie6.x, enemie6.y, 17 * 2, 22 * 2};

        // Collision deetection for player 1 & 2
        if (collision(dest, rect1) || collision(dest, rect2) || collision(dest, rect3))
        {
            // Sets the player cars to starting positions
            x_pos = starting1pos_x;
            y_pos = starting1pos_y;
            x_pos2 = starting2pos_x;
            y_pos2 = starting2pos_y;
            playerCollider.x = 163;
            playerCollider.y = 429;
            carLives--;
            // Sets the enemy cars to starting positions
            enemie1.y = 0;
            enemie2.y = 0;
            enemie3.y = 0;
            enemie4.y = 0;
            enemie5.y = 0;
            enemie6.y = 0;
        }
        if (collision(secondDest, rect4) || collision(secondDest, rect5) || collision(secondDest, rect6))
        {
            // Sets the player cars to starting positions
            x_pos = starting1pos_x;
            y_pos = starting1pos_y;
            x_pos2 = starting2pos_x;
            y_pos2 = starting2pos_y;
            player2Collider.x = 424;
            player2Collider.y = 429;
            car2Lives--;
            // Sets the enemy cars to starting positions
            enemie1.y = 0;
            enemie2.y = 0;
            enemie3.y = 0;
            enemie4.y = 0;
            enemie5.y = 0;
            enemie6.y = 0;
        }

        lifesCars(gRenderer, gWindow, &lifeP1, &lifeP2, carLives, car2Lives);

        // Positioning in struct
        dest.x = (int)x_pos;
        dest.y = (int)y_pos;

        secondDest.x = (int)x_pos2;
        secondDest.y = (int)y_pos2;

        if (korCountdown == 0)
        {
            korCountdown = countdown(gRenderer, gBackground, &light, lightR);
        }

        renderBackground(carLives, car2Lives, &p1Notification, &p2Notification, p1NotR, p2NotR, &enemie1, &enemie2, &enemie3, &enemie4, &enemie5, &enemie6, gRenderer, gBackground, &playerOne, &playerTwo, &lifeP1, &lifeP2, dest, secondDest, lifeP1Rec, lifeP2Rec);

        enemiesMove(&enemie1, &enemie2, &enemie3, &enemie4, &enemie5, &enemie6);

        game = checkIfGameOver(carLives, car2Lives);

        if (carLives == 0 || car2Lives == 0)
        {
            if (player == 1)
            {
                printf("%d %d %d\n", (int)x_pos, (int)y_pos, (int)carLives);
                sprintf((char *)p->data, "%d %d %d\n", (int)x_pos, (int)y_pos, (int)carLives);
                p->len = strlen((char *)p->data) + 1;
                SDLNet_UDP_Send(sd, -1, p);
                x_posOld = x_pos;
                y_posOld = y_pos;
                carOldLives = carLives;
            }
            else if (player == 2)
            {
                printf("%d %d %d\n", (int)x_pos2, (int)y_pos2, (int)car2Lives);
                sprintf((char *)p->data, "%d %d %d\n", (int)x_pos2, (int)y_pos2, (int)car2Lives);
                p->len = strlen((char *)p->data) + 1;
                SDLNet_UDP_Send(sd, -1, p);
                x_pos2Old = x_pos2;
                y_pos2Old = y_pos2;
                car2OldLives = car2Lives;
            }
            SDL_Delay(5000);
            close(gRenderer, gBackground, gWindow, gScreenSurface, &playerOne, &playerTwo);
            exit(NULL);
        }

        SDL_Delay(1000 / 60);
    }
}

void renderEnemies(SDL_Renderer *gRenderer, Enemies *enemie1, Enemies *enemie2, Enemies *enemie3, Enemies *enemie4, Enemies *enemie5, Enemies *enemie6)
{
    int frame = 0;
    // Set the drawing color to blue
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 255, 255);

    SDL_RenderCopy(gRenderer, gBackground, NULL, NULL);

    // Set the drawing color to white
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);

    SDL_Rect rect1 = {enemie1->x, enemie1->y, 17 * 2, 22 * 2};
    SDL_Rect rect2 = {enemie2->x, enemie2->y, 17 * 2, 22 * 2};
    SDL_Rect rect3 = {enemie3->x, enemie3->y, 17 * 2, 22 * 2};
    SDL_Rect rect4 = {enemie4->x, enemie4->y, 17 * 2, 22 * 2};
    SDL_Rect rect5 = {enemie5->x, enemie5->y, 17 * 2, 22 * 2};
    SDL_Rect rect6 = {enemie6->x, enemie6->y, 17 * 2, 22 * 2};
    SDL_RenderCopyEx(gRenderer, enemyCar1, &gCarsclips[frame], &rect1, enemie1->ang, NULL, 0);
    SDL_RenderCopyEx(gRenderer, enemyCar1, &gCarsclips[frame], &rect2, enemie2->ang, NULL, 0);
    SDL_RenderCopyEx(gRenderer, enemyCar1, &gCarsclips[frame], &rect3, enemie3->ang, NULL, 0);
    SDL_RenderCopyEx(gRenderer, enemyCar1, &gCarsclips1[frame + 1], &rect4, enemie4->ang, NULL, 0);
    SDL_RenderCopyEx(gRenderer, enemyCar1, &gCarsclips1[frame + 1], &rect5, enemie5->ang, NULL, 0);
    SDL_RenderCopyEx(gRenderer, enemyCar1, &gCarsclips1[frame + 1], &rect6, enemie6->ang, NULL, 0);
    // Done, now present what has been drawn
    SDL_RenderPresent(gRenderer);
}
