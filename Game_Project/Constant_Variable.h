#ifndef CONSTANT_VARIABLE_H
#define CONSTANT_VARIABLE_H

#define MAX_PATH 2000

#define WIN_W 900
#define WIN_H 600
#define SIDEBAR_W 220
#define PLAY_LEFT 20
#define PLAY_TOP 20
#define PLAY_RIGHT (WIN_W - SIDEBAR_W - 20)
#define PLAY_BOTTOM (WIN_H - 20)

enum Direction {
	DIR_UP = 0,
	DIR_RIGHT = 1,
	DIR_DOWN = 2,
	DIR_LEFT = 3,
};

extern int Px;
extern int Py;
extern int PSize;
extern int StepSize;
extern int dir;

extern int Path[MAX_PATH][2];
extern int PathIndex;

int Restrict(int val, int Min_Val, int Max_Val);
void Record_FootStep();
void Reset_Player_Path(int StartX, int StartY, int initialDir);
void Player_Input();
void Update_Player_Path();
void Render_Bound_Player();

#endif
