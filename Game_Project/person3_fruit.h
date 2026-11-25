#ifndef PERSON3_FRUIT_H
#define PERSON3_FRUIT_H

#include "Constant_Variable.h"

/* Fruit position is the centre of the fruit. */
extern int fx;
extern int fy;
extern int fSize;

/* Fruit functions */
void Fruit_Init(void);
void Spawn_Fruit(void);
int PlayerHitFruit(void);
void Update_Fruit(void);

#endif
