
#include <stdio.h>
//#include <graphics.h>

#include "Constant_Variable.h"
#include "Person2_Enemy.h"

/* ==========================================
   GLOBAL ENEMY VARIABLES
   ========================================== */

/*
   enemy[i][0] = Enemy X coordinate
   enemy[i][1] = Enemy Y coordinate
   enemy[i][2] = Enemy Path Index

   If enemy[i][2] == -1,
   that enemy slot is inactive.
*/

int enemy[100][3];

int eGen = 0;
int EnemyCount = 0;

/*
   Person 3 must define this variable
   in the game-state module.
*/

extern int GameOverFlag;


/* ==========================================
   1. ENEMY INITIALIZATION
   ========================================== */

void Enemy_Init(void)
{
    int i;

    eGen = 0;
    EnemyCount = 0;

    for(i = 0; i < 100; i++)
    {
        enemy[i][0] = 0;
        enemy[i][1] = 0;

        /* -1 means inactive enemy */
        enemy[i][2] = -1;
    }
}


/* ==========================================
   2. RESET ENEMIES
   ========================================== */

void Reset_Enemies(void)
{
    int i;

    eGen = 0;
    EnemyCount = 0;

    for(i = 0; i < 100; i++)
    {
        enemy[i][0] = 0;
        enemy[i][1] = 0;
        enemy[i][2] = -1;
    }
}


/* ==========================================
   3. SPAWN ENEMY
   ========================================== */

void Spawn_Enemy(void)
{
    int i;
    int SpawnIndex;

    /*
       Wait until enough footsteps
       have been recorded.

       This prevents an enemy from
       spawning directly on the player.
    */

    if(PathIndex <= 8)
        return;

    /*
       Find an available enemy slot.
    */

    for(i = 0; i < 100; i++)
    {
        if(enemy[i][2] == -1)
        {
            /*
               Enemy starts 8 recorded
               footsteps behind the player.
            */

            SpawnIndex = PathIndex - 1 - 8;

            if(SpawnIndex < 0)
                SpawnIndex = 0;

            /*
               Store the starting coordinates
               from the player's path array.
            */

            enemy[i][0] = Path[SpawnIndex][0];
            enemy[i][1] = Path[SpawnIndex][1];

            /*
               Store the path index in
               the third column.
            */

            enemy[i][2] = SpawnIndex;

            EnemyCount++;

            return;
        }
    }
}


/* ==========================================
   4. UPDATE ENEMIES
   ========================================== */

void Update_Enemies(void)
{
    int i;
    int TargetIndex;

    if(GameOverFlag)
        return;

    /*
       Increase enemy generation timer.
    */

    eGen++;

    /*
       Generate a new enemy after
       30 game updates.
    */

    if(eGen >= 30)
    {
        Spawn_Enemy();

        eGen = 0;
    }

    /*
       Calculate the delayed path index.

       Enemies follow the player's path
       with an 8-step delay.
    */

    TargetIndex = PathIndex - 1 - 8;

    if(TargetIndex < 0)
        TargetIndex = 0;

    /*
       Update every active enemy.
    */

    for(i = 0; i < 100; i++)
    {
        /*
           Check whether this enemy
           is active.
        */

        if(enemy[i][2] != -1)
        {
            /*
               Move enemy forward through
               the recorded path.
            */

            if(enemy[i][2] < TargetIndex)
            {
                enemy[i][2]++;
            }

            /*
               Read the next coordinates
               from the player's path.
            */

            enemy[i][0] = Path[enemy[i][2]][0];
            enemy[i][1] = Path[enemy[i][2]][1];
        }
    }

    /*
       Check collision after updating
       all enemy positions.
    */

    EnemyHitPlayer();
}


/* ==========================================
   5. ENEMY-PLAYER COLLISION DETECTION
   ========================================== */

int EnemyHitPlayer(void)
{
    int i;

    /*
       Check every active enemy
       against the player.
    */

    for(i = 0; i < 100; i++)
    {
        if(enemy[i][2] != -1)
        {
            /*
               Bounding-box collision:

               Player rectangle:
               Px, Py, PSize

               Enemy rectangle:
               enemy[i][0],
               enemy[i][1],
               PSize
            */

            if(
                Px < enemy[i][0] + PSize &&

                Px + PSize > enemy[i][0] &&

                Py < enemy[i][1] + PSize &&

                Py + PSize > enemy[i][1]
              )
            {
                /*
                   Collision detected.
                   Trigger Game Over.
                */

                GameOverFlag = 1;

                return 1;
            }
        }
    }

    return 0;
}


/* ==========================================
   6. RENDER ENEMIES
   ========================================== */

void Render_Enemies(void)
{
    int i;

    /*
       Draw every active enemy.
    */

    for(i = 0; i < 100; i++)
    {
        if(enemy[i][2] != -1)
        {
            /*
               Enemy color: RED
            */

            setcolor(RED);

            setfillstyle(SOLID_FILL, RED);

            /*
               Draw enemy as a filled rectangle.
            */

            bar(
                enemy[i][0],
                enemy[i][1],

                enemy[i][0] + PSize,
                enemy[i][1] + PSize
            );
        }
    }
}

