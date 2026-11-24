
#ifndef PERSON2_ENEMY_H
#define PERSON2_ENEMY_H

#include "Constant_Variable.h"

/* Enemy data */
extern int enemy[100][3];
extern int eGen;
extern int EnemyCount;

/* Initialization and reset */
void Enemy_Init(void);
void Reset_Enemies(void);

/* Enemy spawning and movement */
void Spawn_Enemy(void);
void Update_Enemies(void);

/* Collision detection */
int EnemyHitPlayer(void);

/* Rendering */
void Render_Enemies(void);

#endif

