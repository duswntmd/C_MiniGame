#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h> 
#include<Windows.h> 
#include<conio.h> 
#include<stdlib.h> 
#include<time.h> 
#include"teamplus.h"


#define GAMESTART 1 
#define LEVEL 2 
#define EXIT 3 
#define WIDTH 10 
#define HEIGHT 20 
#define Y 0 
#define X 1 
#define NULL 0 
#define WALL 1 
#define PLAYER 2     
#define STAR 3 
#define false 0 
#define true 1 

int player[2];
int level = 3;
int run = 1;
int score = 0;
void firstwindow(void);
void stage3draw(void);
void gameclear(void);
void Init(int map[][WIDTH])
{
    player[X] = WIDTH - 5;
    player[Y] = HEIGHT - 1;
}
void StarCreate(int map[HEIGHT][WIDTH])
{
    int lv, i, x;
    int starCount = 0; // 생성된 별의 개수를 저장하는 변수
    while (starCount < 5) // 별이 5개 미만일 경우 계속 생성
    {
        x = rand() % 8 + 1;
        if (map[0][x] != STAR) // 이미 별이 있는 위치에는 생성하지 않음
        {
            map[0][x] = STAR;
            starCount++; // 별 개수 증가
        }
    }
}

void map_reset(int map[][WIDTH])
{
    int y, x;
    for (y = 0; y < HEIGHT; y++)
    {
        for (x = 0; x < WIDTH; x++)
        {
            map[y][0] = WALL;
            map[y][WIDTH - 1] = WALL;
        }
    }
    StarCreate(map);
}


void MapDraw(int map[][WIDTH])
{
    COORD pos = { 0, 0 };
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            if (player[Y] == y && player[X] == x)
                printf("옷");
            else if (map[y][x] == WALL)
                printf("│");
            else if (map[y][x] == STAR)
                printf("☆");
            else
                printf("  ");
        }
        printf("\n");
    }
    printf("\n Score : %d\n", score);
}

void Star_Update(int map[HEIGHT][WIDTH])
{
    for (int y = HEIGHT - 1; y >= 0; y--)
    {
        for (int x = 1; x < WIDTH - 1; x++)
        {
            if (map[y][x] == STAR)
            {
                map[y][x] = 0;
                if (y + 1 >= HEIGHT)
                {
                    map[HEIGHT - 1][1] = 0;
                    map[HEIGHT - 1][2] = 0;
                    map[HEIGHT - 1][3] = 0;
                    map[HEIGHT - 1][4] = 0;
                    map[HEIGHT - 1][5] = 0;
                    map[HEIGHT - 1][6] = 0;
                    map[HEIGHT - 1][7] = 0;
                    map[HEIGHT - 1][8] = 0;
                    StarCreate(map);
                    return;
                }
                else
                {
                    map[y + 1][x] = STAR;
                }
            }
        }
    }
}

int check_hit(int map[][WIDTH])
{
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            if (map[y][x] == STAR)
            {
                if (player[Y] == y && player[X] == x)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

void PlayerMove(int map[][WIDTH])
{
    int run = 1;
    int gameover1 = 0;

    system("cls"); // 게임 시작 시 한 번만 화면을 지움
    MapDraw(map);

    while (run)
    {
        int key = GetKeyDown();

        switch (key)
        {
        case 3: // 왼쪽으로 움직이는 키
            if (map[player[Y]][player[X] - 1] != WALL)
            {
                map[player[Y]][player[X]] = 0;
                player[X]--;
            }
            break;

        case 4: // 오른쪽으로 움직이는 키
            if (map[player[Y]][player[X] + 1] != WALL)
            {
                map[player[Y]][player[X]] = 0;
                player[X]++;
            }
            break;

        default:
            break;
        }

        if (map[player[Y]][player[X]] == STAR)
        {
            run = 0;
            gameover1 = 1;
            system("cls");
            gameover();
            system("cls");
            firstwindow();

        }
        else
        {
            map[player[Y]][player[X]] = PLAYER;
            score++;
        }

        Star_Update(map); // 별의 위치 업데이트

        if (score > 200)
        {
            run = 0;
            stage3draw();
            Sleep(2000); // 2초 대기
        }

        if (!gameover1)
        {
            COORD pos = { 0, 0 };
            HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleCursorPosition(output, pos);
            MapDraw(map); // 맵을 다시 그림
        }
        Sleep(50); // 별의 이동 속도 조절
    }

    score = 0; // 게임 오버 후 점수 초기화
}

void stage2(void)
{
    int map[HEIGHT][WIDTH] = { 0 };


    srand((unsigned)time(NULL));

    map_reset(map);
    Init(map);

    while (run)
    {
        Star_Update(map);
        MapDraw(map);
        PlayerMove(map);

        if (score > 200)
        {
            
            stage3draw();
        }
        Sleep(50);
    }
}
