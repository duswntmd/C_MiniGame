#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include <time.h>
#include <stdbool.h>
#include "teamplus.h"

#include <mmsystem.h> //playsound를 사용하기 위해서
#pragma comment(lib,"winmm.lib") //별도의 라이브러리 필요함
#include "Digitalv.h"

void GotoXY(int x, int y);
void GotoXy(int x, int y);
void gotoxyt(int x, int y);
void gotoxy(int x, int y, char* s);

int GetKeyDown();

void firstwindow(void);
void stage1draw(void);
void stage2draw(void);
void stage3draw(void);
void stage4draw(void);
void stage5draw(void);
void stage1(void);
void stage2(void);
void stage3(void);
void stage4(void);
void stage5(void);
void gameclear(void);

int main(void)
{
  
   
        firstwindow();
        stage1draw();
        stage1();
        stage2draw();
        stage2();
        stage3draw();
        stage3();
        stage4draw();
        stage4();
        stage5draw();
        stage5();
        return 0;
}