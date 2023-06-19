#include<stdio.h>
#include<windows.h>
#include<stdbool.h>
#include<conio.h>
#include<time.h>
#include "teamplus.h"
//#include <mmsystem.h>

//#pragma comment(lib,"winmm.lib")
#define HUMAN_BOTTOM_X 7
#define HUMAN_BOTTOM_Y 12
#define TREE_BOTTOM_Y 14
#define TREE_BOTTOM_X 57

#define wallbut_Y 12
#define wallbut_X 0

#define exitdoor_X 45


//콘솔 창의 크기와 제목을 지정하는 함수
void SetConsoleView()
{
    system("mode con:cols=100 lines=25");
    system("title Google Dinosaurs. By LHS.");
}

//커서의 위치를 x, y로 이동하는 함수
void GotoXy(int x, int y)
{
    COORD Pos;
    Pos.X = 2 * x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void firstwindow(void);
void stage4draw(void);
void gameover(void);

void DrawHuman(int humanX, int humanY, bool isJumping)
{
    GotoXy(humanX, humanY);
    printf("  @  \n");
    GotoXy(humanX, humanY + 1);
    printf("@ @ @\n");
    if (isJumping) {
        GotoXy(humanX, humanY + 2);
        printf("  @  \n");
        GotoXy(humanX, humanY + 3);
        printf("@   @\n");
    }
    else if (humanX % 2 == 0) {
        GotoXy(humanX, humanY + 2);
        printf("  @ @\n");
        GotoXy(humanX, humanY + 3);
        printf("@    \n");
    }
    else if (humanX % 2 == 1) {
        GotoXy(humanX, humanY + 2);
        printf("@ @  \n");
        GotoXy(humanX, humanY + 3);
        printf("    @\n");
    }


}


//나무를 그리는 함수
void DrawTree(int treeX)
{
    GotoXy(treeX, TREE_BOTTOM_Y);
    printf("$$$");
    GotoXy(treeX, TREE_BOTTOM_Y + 1);
    printf(" $ ");
}

void wall(int wallX, int wally)  //콘솔에 벽표시
{
    GotoXy(wallX, wally);
    printf("ㅁ");
    GotoXy(wallX, wally + 1);
    printf("ㅁ ㅁ");
    GotoXy(wallX, wally + 2);
    printf("ㅁ ㅁ ㅁ");
    GotoXy(wallX, wally + 3);
    printf("ㅁ ㅁ");
    GotoXy(wallX, wally + 4);
    printf("ㅁ");

}

//(v2.0) 충돌 했을때 게임오버 그려줌
void DrawClear() {
    system("cls");
    int x = 18;
    int y = 8;
    GotoXy(x, y);
    printf("===========================");
    GotoXy(x, y + 1);
    printf("======G A M E C L E A R======");
    GotoXy(x, y + 2);
    printf("===========================");
}

void DrawGameOver()
{
    system("cls");
    int x = 18;
    int y = 8;
    GotoXy(x, y);
    printf("===========================");
    GotoXy(x, y + 1);
    printf("======G A M E O V E R======");
    GotoXy(x, y + 2);
    printf("===========================");

    //PlaySound(TEXT("fall.wav"), 0, SND_ASYNC | SND_LOOP);

    printf("\n\n\n\n\n\n\n\n\n");
    system("pause");
}
void Draw_exit(int exitX) {
    GotoXy(exitX, 10);
    printf(" @@");
    GotoXy(exitX, 11);
    printf("@  @");
    GotoXy(exitX, 12);
    printf("@  @");
    GotoXy(exitX, 13);
    printf("@  @");
    GotoXy(exitX, 14);
    printf("@  @");
    GotoXy(exitX, 15);
    printf(" @@");
}

//(v2.0) 충돌했으면 true, 아니면 false
bool isCollisionn(const int treeX, const int humanX, const int humanY)
{
    //트리의 X가 human의 몸체쪽에 있을때,
    //human의 높이가 충분하지 않다면 충돌로 처리
    
    if (treeX <= humanX + 3 && treeX >= humanX + 1 &&
        humanY > 9)
    {
        return true;
    }
    return false;
}
//void stage5(void);
void stage1(void)
{
    SetConsoleView();

    bool isMove = false;
    //const int gravity = 1;     //벽 속도 고정함수
    int wally = wallbut_Y;
    double wallX = wallbut_X;
    int exitX = exitdoor_X;

    while (true)        //(v2.0) 게임 루프
    {
        mciSendString(TEXT("open \"gaming.wav\" type mpegvideo alias gaming"), NULL, 0, NULL); //배경 음악 열기
        mciSendString(TEXT("play gaming repeat"), NULL, 0, NULL); //배경음악 반복 재생
        //게임 시작시 초기화
        bool isJumping = false;
        bool isBottom = true;
        const int gravity = 3;

        int humanX = HUMAN_BOTTOM_X;
        int humanY = HUMAN_BOTTOM_Y;
        int treeX = TREE_BOTTOM_X;

        int endTime = (unsigned)time(NULL);
        endTime += 10;
        //PlaySound(TEXT("test.wav"), 0, SND_ASYNC | SND_LOOP);
        while (true)    //한 판에 대한 루프
        {
            int startTime = (unsigned)time(NULL);
            GotoXy(80, 0);
            printf("%d초 \n", endTime - startTime);
            Sleep(1);
            if (endTime - startTime == 0) {
                gameover();
                
                firstwindow();
            }
            
            // 충돌체크 트리의 x값과 human의 y값으로 판단
            if (isCollisionn(treeX, humanX, humanY)) {
                system("cls");
                gameover();
                system("cls");
                firstwindow();
            }

            int key = GetKeyDown();

            switch (key)
            {
            case 4: //앞으로 ==오른쪽
                humanX += 1;
                break;
            case 3: //왼쪽
                humanX -= 1;
                break;
            case 1: //위쪽 =점프
                if (isBottom) {
                    isJumping = true;
                    isBottom = false;
                    mciSendString(TEXT("open \"Jumping.wav\" type mpegvideo alias Jumping"), NULL, 0, NULL); //효과음 열기
                    mciSendString(TEXT("play jumping from 0 to 1000"), NULL, 0, NULL); //배경음악 반복 재생
                }
                break;
            }
            //점프중이라면 Y를 감소, 점프가 끝났으면 Y를 증가.
            if (isJumping)
            {
                humanY -= gravity;
            }
            else
            {
                humanY += gravity;
            }

            //Y가 계속해서 증가하는걸 막기위해 바닥을 지정.
            if (humanY >= HUMAN_BOTTOM_Y)
            {
                humanY = HUMAN_BOTTOM_Y;
                isBottom = true;
            }

            //나무가 왼쪽으로 (x음수) 가도록하고
            //나무의 위치가 왼쪽 끝으로가면 다시 오른쪽 끝으로 소환.
            treeX -= 2;
            if (treeX <= 0)
            {
                treeX = TREE_BOTTOM_X;
            }

            //점프의 맨위를 찍으면 점프가 끝난 상황.
            if (humanY <= 7)
            {
                isJumping = false;
            }

            wallX += 0.4;//벽이동속도
            if (wallX + 3 >= humanX) {

                wallX = wallbut_X;
                system("cls");
                gameover();
                system("cls");
                firstwindow();

            }
            if (exitX == humanX) {

                stage2draw();
            }

            DrawHuman(humanX, humanY, isJumping);    //draw human
            DrawTree(treeX);        //draw Tree
            wall(wallX, wally);
            Draw_exit(exitX);


            Sleep(60);
            system("cls");    //clear
        }
        DrawGameOver();
    }

    return;
}