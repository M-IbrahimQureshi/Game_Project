#include <stdlib.h>
#include "Constant_Variable.h"
#include "Person3_Fruit.h"
#include "Person3_GameState.h"

/* Fruit variables */
int fx = 0;
int fy = 0;
int fSize = 10;

/* Place the first fruit on the board. */
void Fruit_Init(void)
{
    Spawn_Fruit();
}

/* Generate a random fruit position inside the playing area. */
void Spawn_Fruit(void)
{
    int MinX;
    int MaxX;
    int MinY;
    int MaxY;

    /* Keep the complete fruit inside the board. */
    MinX = PLAY_LEFT + fSize;
    MaxX = PLAY_RIGHT - fSize;
    MinY = PLAY_TOP + fSize;
    MaxY = PLAY_BOTTOM - fSize;

    /* Choose random coordinates until the fruit is not on the player. */
    do
    {
        fx = MinX + rand() % (MaxX - MinX + 1);
        fy = MinY + rand() % (MaxY - MinY + 1);

    } while (PlayerHitFruit());
}

/* Return 1 when the player touches the fruit, otherwise return 0. */
int PlayerHitFruit(void)
{
    /* The fruit is treated as a small square around its centre.
       This simple overlap check is suitable for our beginner-level game. */
    if (Px < fx + fSize &&
        Px + PSize > fx - fSize &&
        Py < fy + fSize &&
        Py + PSize > fy - fSize)
    {
        return 1;
    }

    return 0;
}

/* Check collection once during each game update. */
void Update_Fruit(void)
{
    if (PlayerHitFruit())
    {
        score++;
        Spawn_Fruit();
    }
}
