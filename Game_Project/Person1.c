//#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include "Constant_Variable.h" 

int Px = 120;
int Py = 120;
int PSize = 20;
int StepSize = 20;
int dir = DIR_RIGHT;

int Path[MAX_PATH][2];
int PathIndex = 0;

int Restrict(int val, int Min_Val, int Max_Val){
	if(val < Min_Val)
		return Min_Val;
	if(val > Max_Val)
		return Max_Val;
	return val;
}

void Record_FootStep(){
	int LastX;
	int LastY;
	if(PathIndex == 0){
		Path[0][0] = Px;
		Path[0][1] = Py;
		PathIndex = 1;
		return;
	}
	
	LastX = Path[PathIndex-1][0];
	LastY = Path[PathIndex-1][1];
	
	if(Px == LastX && Py == LastY)
		return;
		
	if(PathIndex < MAX_PATH){
		Path[PathIndex][0] = Px;
		Path[PathIndex][1] = Py;
		PathIndex++;
	}
}

void Reset_Player_Path(int StartX, int StartY, int initialDir){
	int MinX = PLAY_LEFT + 2;
	int MaxX = PLAY_RIGHT - PSize - 2;
	int MinY = PLAY_TOP + 2;
	int MaxY = PLAY_BOTTOM - PSize - 2;
	
	Px = Restrict(StartX, MinX, MaxX);
	Py = Restrict(StartY, MinY, MaxY);
	dir = initialDir;
	PathIndex = 0;
	
	Record_FootStep();
}

void Player_Input(){
	while(kbhit()){
		int ch = getch();
		
		if(ch==0 || ch==224){
			
				int Scan = getch();
				if(Scan == 72 && dir != DIR_DOWN)
					dir = DIR_UP;
				else if(Scan == 77 && dir != DIR_LEFT)
					dir = DIR_RIGHT;
				else if(Scan == 80 && dir != DIR_UP)
					dir = DIR_DOWN;
				else if(Scan == 75 && dir != DIR_RIGHT)
					dir = DIR_LEFT;
			
		
		}
	}
}

void Update_Player_Path(){
	int MinX;
	int MaxX;
	int MinY;
	int MaxY;
	
	if(dir == DIR_UP)
		Py -= StepSize;
	else if(dir == DIR_RIGHT)
		Px += StepSize;
	else if(dir == DIR_DOWN)
		Py += StepSize;
	else if(dir == DIR_LEFT)
		Px -= StepSize;
		
	MinX = PLAY_LEFT + 2;
	MaxX = PLAY_RIGHT - PSize - 2;
	MinY = PLAY_TOP + 2;
	MaxY = PLAY_BOTTOM - PSize - 2;
	
	Px = Restrict(Px, MinX, MaxX);
	Py = Restrict(Py, MinY, MaxY);
	
	Record_FootStep();
}

void Render_Bound_Player(){
//	int i;
//	int PanelLeft = PLAY_RIGHT + 15;
//	int PanelRight = WIN_W - 20;
	printf("Pos: (%d, %d) | Dir: %d | PathIndex: %d\n", Px, Py, dir, PathIndex);
    fflush(stdout);
	
//	setcolor(WHITE);
//	rectangle(PLAY_LEFT, PLAY_TOP, PLAY_RIGHT, PLAY_BOTTOM);
//	rectangle(PanelLeft, PLAY_TOP, PanelRight, PLAY_BOTTOM);
	
//	for(i=0; i<PathIndex; i++)
////		putpixel(Path[i][0] + PSize/2, Path[i][1] + PSize/2, DARKGRAY);
//		
////		setcolor(CYAN);
////		setfillstyle(SOLID_FILL, CYAN);
//		bar(Px,Py,Px+PSize,Py+PSize);		
}

int main(){
	//initwindow(WIN_W, WIN_H, "Foot Steps Player & Path Engine");
	Reset_Player_Path(PLAY_LEFT+60, PLAY_TOP+60, DIR_RIGHT);
	printf("Use Arrow keys to move, ESC to quit.\n");
    fflush(stdout);
    
	while(1){
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
        	break;
		
		Player_Input();
		Update_Player_Path();
		
		//cleardevice();
		Render_Bound_Player();
		Sleep(100);
		//delay(60);
	}
	//closegraph();
	return 0;
	
	}







