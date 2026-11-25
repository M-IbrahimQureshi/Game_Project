#ifndef PERSON3_GAMESTATE_H
#define PERSON3_GAMESTATE_H

/* These variables are used by the game loop and the other modules. */
extern int score;
extern int GameOverFlag;
extern int GameElapsedSeconds;
extern int DifficultyLevel;
extern int EnemySpawnDelay;

/* Game-state functions */
void Game_Init(void);
void Game_Update(void);
void Game_UpdateTimer(void);
void Update_Difficulty(void);
void Game_Reset(void);
void GameOver(void);

#endif
