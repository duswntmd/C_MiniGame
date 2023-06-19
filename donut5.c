#include<stdio.h>
#include<Windows.h>
#include<conio.h>
#include <stdbool.h>
#include "teamplus.h"
#define pgbut 0  //고정함수
#define pgrbut 79 
#define meetbut 0


void GotoXY(int x, int y)  //좌표값정의
{
    COORD Pos;
    Pos.X = x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int GetKeyDown();  //키갑정의


void pinger(int pgX)  //손가락 콘솔표시
{
    GotoXY(pgX, 12);
    printf("  ㅁㅁㅁㅁㅇㅁㅁ      ");
    GotoXY(pgX, 13);
    printf("  ㅁㅁㅁㅁㅇㅁㅁㅁㅁ  ");
    GotoXY(pgX, 14);
    printf("  ㅁㅁㅁㅁㅇ          ");
    GotoXY(pgX, 15);
    printf("  ㅁㅁㅁㅇ            ");

}

void pingerRight(int pgrX)  //손가락 콘솔표시
{
    GotoXY(pgrX, 12);
    printf("     ㅁㅁㅇㅁㅁㅁㅁ   ");
    GotoXY(pgrX, 13);
    printf(" ㅁㅁㅁㅁㅇㅁㅁㅁㅁ   ");
    GotoXY(pgrX, 14);
    printf("         ㅇㅁㅁㅁㅁ   ");
    GotoXY(pgrX, 15);
    printf("           ㅇㅁㅁㅁ ");

}
void meeting(int meety)  //도넛콘솔표시
{
    GotoXY(20, meety);
    printf("ㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁ");
    GotoXY(20, meety + 1);
    printf("[            '                                             ]");
    GotoXY(20, meety + 2);
    printf(" )                              '                         ( ");
    GotoXY(20, meety + 3);
    printf("[                                                '         ]");
    GotoXY(20, meety + 4);
    printf("ㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁㅁ");

}

bool isCollision(const int pgX, const int meety)  //충돌값함수
{
    if (meety <= 14 && meety >= 12 && pgX > 3) //이조건 만족시
    {
        return true;
    }
    return false;
}
void firstwindow(void);
void gameover(void);
void gameclear(void);

void  stage5(void) //메인함수
{

    bool uppg = false;  //정답상태
    bool isBottom = true;  //오답상태
    const int gravity = 4;  //손가락 움직임 고정값
    int score = 0;
    int i = 100;


    int pgX = pgbut;  //고정함수 대입
    int pgrX = pgrbut;
    int meety = meetbut;

    int endTime = (unsigned)time(NULL);
    endTime += 10;
    while (true)  //반복문
    {
        int startTime = (unsigned)time(NULL);
        GotoXY(80, 0);
        printf("%d초 \n", endTime - startTime);
        Sleep(1);
        if (endTime - startTime == 0) {
            gameover();

            firstwindow();
        }
        int key = GetKeyDown();
        switch (key)
        {
        case 5:
            if (isBottom)
            {
                uppg = true;  //활성화
                isBottom = false;  //비활성화
            }
            break;
        }
        if (uppg)  
        {
            pgX += gravity;    //정답이면 증가
            pgrX -= gravity;
        }
        else
        {
            pgX -= gravity;  //오답이면 감소
            pgrX += gravity;
        }
        if (pgX <= pgbut)  // 손가락이x창을 벗어나면
        {
            pgX = pgbut;  //손가락 위치고정
            isBottom = true;  //정답처리
        }
        if (pgrX >= pgrbut)  // 손가락이x창을 벗어나면
        {
            pgrX = pgrbut;  //손가락 위치고정
        }
        if (pgX >= 4)  //손가락이 일정 이상 넘어갈려면
        {
            uppg = false;  //오답처리
        }
        meety += 2;  //도넛 2씩증가
        if (meety >= 24)  //아래벽에 떨어지면
        {
            system("cls");
            gameover();
            system("cls");
            firstwindow();
        }
        if (meety <= 11 && pgX > 3)  //도넛이 손가락에 닿기전에 먼저 눌리면 
        {
            system("cls");
            gameover();
            system("cls");
            firstwindow();
        }
        if (isCollision(pgX, meety))  //도넛이 손가락과 출돌시
        {
            meety = meetbut;  //도넛리셋
            score++; //점수증가
        }
        if (score > 4)  //5번성공시
        {         
            gameclear();
            system("pause");
            system("cls");
            firstwindow();
            
        }
        if (score == 1)  //속도 증가
        {
            i = 350;
        }
        if (score == 2)
        {
            i = 50;
        }
        if (score == 3)
        {
            i = 250;
        }
        if (score == 4)
        {
            i = 100;
        }

        pinger(pgX); //손가락을 찍어라
        meeting(meety);  //도넛을 찍어라
        pingerRight(pgrX);
        Sleep(i);  //딜레이
        system("cls");  //콘솔 클리어
        GotoXY(40, 0);
        printf("Score : %d ", score); //점수 출력
    }

    return;
}

