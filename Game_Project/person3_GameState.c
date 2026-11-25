#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#include "Constant_Variable.h"
#include "Person2_Enemy.h"
#include "Person3_Fruit.h"
#include "Person3_GameState.h"

#define START_X (PLAY_LEFT + 60)
#define START_Y (PLAY_TOP + 60)
#define MAX_DIFFICULTY 5

/* Game variables */
int score = 0;
int GameOverFlag = 0;
int GameElapsedSeconds = 0;
int DifficultyLevel = 1;
int EnemySpawnDelay = 30;

/* Stores the time when the current game starts. */
static time_t GameStartTime;

/* Set up the game for the first time. */
void Game_Init(void)
{
    /* Seed rand() once so fruit positions change between runs. */
    srand((unsigned int)time(NULL));

    score = 0;
    GameOverFlag = 0;
    GameElapsedSeconds = 0;
    DifficultyLevel = 1;
    EnemySpawnDelay = 30;

    Reset_Player_Path(START_X, START_Y, DIR_RIGHT);
    Enemy_Init();
    Fruit_Init();

    GameStartTime = time(NULL);
}

/* Update the number of seconds since this game started. */
void Game_UpdateTimer(void)
{
    GameElapsedSeconds = (int)difftime(time(NULL), GameStartTime);

    if (GameElapsedSeconds < 0)
    {
        GameElapsedSeconds = 0;
    }
}

/* Make the game harder as the player survives for more time. */
void Update_Difficulty(void)
{
    int NewLevel;

    /* Difficulty increases after every 20 seconds. */
    NewLevel = 1 + (GameElapsedSeconds / 20);

    if (NewLevel > MAX_DIFFICULTY)
    {
        NewLevel = MAX_DIFFICULTY;
    }

    DifficultyLevel = NewLevel;

    /* A smaller delay makes enemies appear more often. */
    EnemySpawnDelay = 30 - ((DifficultyLevel - 1) * 5);

    if (EnemySpawnDelay < 10)
    {
        EnemySpawnDelay = 10;
    }
}

/* Call this function once in every round of the main game loop. */
void Game_Update(void)
{
    if (GameOverFlag == 1)
    {
        return;
    }

    Game_UpdateTimer();
    Update_Difficulty();
    Update_Fruit();
}

/* Clear the old game values and prepare a new round. */
void Game_Reset(void)
{
    score = 0;
    GameOverFlag = 0;
    GameElapsedSeconds = 0;
    DifficultyLevel = 1;
    EnemySpawnDelay = 30;

    /* Use the player and enemy reset functions already provided. */
    Reset_Player_Path(START_X, START_Y, DIR_RIGHT);
    Reset_Enemies();
    Spawn_Fruit();

    GameStartTime = time(NULL);
}

/* Show the result after the enemy catches the player, then restart. */
void GameOver(void)
{
    if (GameOverFlag == 0)
    {
        return;
    }

    printf("\n====================\n");
    printf("      GAME OVER     \n");
    printf("Final Score: %d\n", score);
    printf("Time Played: %d seconds\n", GameElapsedSeconds);
    printf("Press any key to restart...\n");
    printf("====================\n");

    /* Wait for a key before resetting the game. */
    getch();

    Game_Reset();
}
