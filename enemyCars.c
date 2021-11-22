#include "enemyCars.h"

struct enemies
{
    float x, y;
    float dy;
    float ang;
};

void enemiesMove(Enemies *enemie1, Enemies *enemie2, Enemies *enemie3, Enemies *enemie4, Enemies *enemie5, Enemies *enemie6)
{
    // Velocity of the cars
    float cdy1 = 0.16;
    float cdy2 = 0.18;
    float cdy3 = 0.2;

    /*enemie1->dy += cdy1;
    enemie2->dy += cdy2;
    enemie3->dy += cdy3;
    enemie4->dy += cdy1;
    enemie5->dy += cdy2;
    enemie6->dy += cdy3;*/

    // When the cars reach the end, set cars to startingpositions and increase velocity
    if (enemie1->y > 615 && enemie4->y > 615)
    {
        enemie1->y = 0;
        enemie1->dy *= 2;
        enemie4->y = 0;
        enemie4->dy *= 2;
    }

    if (enemie2->y > 615 && enemie5->y > 615)
    {
        enemie2->y = 0;
        enemie2->dy *= 2;
        enemie5->y = 0;
        enemie5->dy *= 2;
    }

    if (enemie3->y > 615 && enemie6->y > 615)
    {
        enemie3->y = 0;
        enemie3->dy *= 2;
        enemie6->y = 0;
        enemie6->dy *= 2;
    }

    enemie1->y += enemie1->dy;
    enemie1->dy *= 0.7;
    enemie2->y += enemie2->dy;
    enemie2->dy *= 0.8;
    enemie3->y += enemie3->dy;
    enemie3->dy *= 0.9;

    enemie4->y += enemie4->dy;
    enemie4->dy *= 0.7;
    enemie5->y += enemie5->dy;
    enemie5->dy *= 0.8;
    enemie6->y += enemie6->dy;
    enemie6->dy *= 0.9;
}