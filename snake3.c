#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<time.h>
#include "teamplus.h"

#include <mmsystem.h> //playsound를 사용하기 위해서
#pragma comment(lib,"winmm.lib") //별도의 라이브러리 필요함
#include "Digitalv.h"

typedef struct
{
    int x, y;

}POS;
void firstwindow(void);
void stage2draw(void);
void gameover(void);
void gotoxy(int x, int y, char* s)//물체의 이동

{
    COORD Pos = { x * 2,y };

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);

    printf("%s", s);// s를 맵에 나오게 프린트함.

}

void draw_screen()  ///처음 맵 테두리 그리기

{
    int i;

    system("cls");//화면 지움

    gotoxy(0, 0, "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");// 위 테두리

    for (i = 1; i < 20; i++)// 왼쪽 오른쪽 테두리

    {

        gotoxy(0, i, "■");

        gotoxy(30, i, "■");

    }

    gotoxy(0, 20, "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");// 아래쪽 테두리

}
int GetKeyDown();// 키 함수 키보드 입력해서 움직이게하기위한

void move_snake(POS* snake, int len)///뱀이 움직이는 부분

{
    static int dir = -1;

    if (_kbhit())///입력부분

    {
        int key = GetKeyDown();// 키 함수 부르기

        switch (key)//키함수의 입력 키에따라 dir변수 값을 변경

        {
        case 1: dir = 0; break;//위

        case 2: dir = 1; break;//아래

        case 3: dir = 2; break;//왼쪽

        case 4: dir = 3; break;//오른쪽

        }

    }

    if (dir != -1)//키함수로 키를 입력했을때 꼬리부분에 대한 코드

    {

        int i;

        gotoxy(snake[len - 1].x, snake[len - 1].y, "  ");// 꼬리 마지막부분 늘어지지않게하기위한 코드

        for (i = len - 1; i > 0; i--)
            snake[i] = snake[i - 1]; //마지막 꼬리부분부터 처음꼬리까지 한칸식 이동시킴 다만 여기서 ○로 나타낸건 아님

        gotoxy(snake[1].x, snake[1].y, "○");//꼬리부분을 생성하기 위한코드

    }


    switch (dir) //누른 키에따른 변수를 스위치문으로 변환해 스네이크 머리부분 위치 변환

    {

    case 0: snake[0].y--;; break;//위 

    case 1: snake[0].y++; break;//아레

    case 2: snake[0].x--; break;//왼쪽

    case 3: snake[0].x++; break;//오른쪽

    }

    gotoxy(snake[0].x, snake[0].y, "●");//스네이크 머리부분

}

int check_snake(POS* snake, int len)///뱀이 충돌했는지 확인하는 부분

{

    int i;

    if (snake[0].x == 0 || snake[0].y == 0 || snake[0].x == 30 || snake[0].y == 20)return 0;//스네이크가 맵의 부딪혔을때 0반환

    for (i = 1; i < len; i++)

    {

        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)return 0;//스네이크 머리가 꼬리에 부딪히면 0반환

    }

    return 1;

}

void stage3(void)

{
    POS fall1[4], fall2[4], fall3[4], fall4[4];//장애물
    POS snake[100], item, item2;//지렁이의 몸과, 아이템 선언
    int j, i, dir = -1, len = 5, score = 0;// len은 꼬리 마지막까지의 수 선언및, 점수 선언
    int speed = 150; //스피드 선언
    double timec = 0;//시간의 차를 저장할 변수 선언**********************************
    clock_t start, end;//clock_t선언*************************************8
    srand(time(NULL));//함수를 랜덤으로 선언할때마다 랜덤으로 만들려고

    mciSendString(TEXT("close gamemain"), NULL, 0, NULL); //배경 음악 닫기
    mciSendString(TEXT("open \"gaming.wav\" type mpegvideo alias gaming"), NULL, 0, NULL); //배경 음악 열기
    mciSendString(TEXT("play gaming repeat"), NULL, 0, NULL); //배경음악 반복 재생

    draw_screen();// 맵생성

    for (i = 0; i < len; i++)// 처음시작할떄의 위치 

    {

        snake[i].x = 15 + i; //지렁의 몸 위치

        snake[i].y = 10;

        gotoxy(snake[i].x, snake[i].y, "○");//처음시작할때의 위치를 꼬리로 표현 머리는 key함수로 나타나짐

    }
    fall1[0].x = 3;// 처음 랜덤장애물의 위치
    fall1[0].y = 2;
    fall1[1].x = 4;
    fall1[1].y = 2;
    fall1[2].x = 3;
    fall1[2].y = 3;
    fall1[3].x = 4;
    fall1[3].y = 3;
    fall2[0].x = 3;
    fall2[0].y = 17;
    fall2[1].x = 4;
    fall2[1].y = 17;
    fall2[2].x = 3;
    fall2[2].y = 18;
    fall2[3].x = 4;
    fall2[3].y = 18;
    fall3[0].x = 26;
    fall3[0].y = 2;
    fall3[1].x = 27;
    fall3[1].y = 2;
    fall3[2].x = 26;
    fall3[2].y = 3;
    fall3[3].x = 27;
    fall3[3].y = 3;
    fall4[0].x = 26;
    fall4[0].y = 17;
    fall4[1].x = 27;
    fall4[1].y = 17;
    fall4[2].x = 26;
    fall4[2].y = 18;
    fall4[3].x = 27;
    fall4[3].y = 18;
respone:
    item.x = rand() % 28 + 1;// 아이템1의 위치를 랜덤으로 선언

    item.y = rand() % 18 + 1;
respone1:
    item2.x = rand() % 28 + 1;//아이템2의 위치를 랜덤으로 선언

    item2.y = rand() % 18 + 1;
    for (i = 0; i < 4; i++) {
        if (fall1[i].x == item.x && fall1[i].y == item.y)// 아이템1과 아이템2가 랜덤장애물에 생성되면 다시 goto문으로 다시 돌아가서 생성
            goto respone;
        if (fall2[i].x == item.x && fall2[i].y == item.y)
            goto respone;
        if (fall3[i].x == item.x && fall3[i].y == item.y)
            goto respone;
        if (fall4[i].x == item.x && fall4[i].y == item.y)
            goto respone;
        if (fall1[i].x == item2.x && fall1[i].y == item2.y)
            goto respone1;
        if (fall2[i].x == item2.x && fall2[i].y == item2.y)
            goto respone1;
        if (fall3[i].x == item2.x && fall3[i].y == item2.y)
            goto respone1;
        if (fall4[i].x == item2.x && fall4[i].y == item2.y)
            goto respone1;
    }
    if (item.x == item2.x && item.y == item2.y)//아이템1과 아이템2가 겹치면 다시 돌아가서 생성
        goto respone1;
    gotoxy(1, 21, "Score : 0");// 처음 스코어 위치 조정






    while (1) {
        if (timec >= 30)//일정시간 지나면 반복문 탈출*******************************
            break;
        if (check_snake(snake, len) == 0)//스네이크가 몸이나 맵에 부딪히면 반복문 탈출

            break;

        if (snake[0].x == item.x && snake[0].y == item.y || snake[0].x == item2.x && snake[0].y == item2.y)///아이템 먹었을 경우

        {
            mciSendString(TEXT("open \"effect.wav\" type mpegvideo alias effect"), NULL, 0, NULL); //효과음 열기
            mciSendString(TEXT("play effect from 0 to 1000"), NULL, 0, NULL); //배경음악 반복 재생
            score += 10;//점수가 올라감
            if (score == 40)//일정점수 모으면 반복문 탈출
                stage4draw();
            if (snake[0].x == item.x && snake[0].y == item.y)// 아이템1을 먹었을때 스피드가 시작스피드에 비해 느려짐
                speed = 200;
            if (snake[0].x == item2.x && snake[0].y == item2.y)// 아이템2를 먹었을때 스피드가 시작스피드에 비해 빨라짐
                speed = 90;
            gotoxy(item.x, item.y, "  ");//아이템을 먹었을때 아이템의 모양이남으면 치우는 코드
            gotoxy(item2.x, item2.y, "  ");
            for (i = 0; i < 4; i++) {// 아이템을 먹었을때 랜덤장애물의 모양이남아있으면 치우는 코드
                gotoxy(fall1[i].x, fall1[i].y, "  ");
                gotoxy(fall2[i].x, fall2[i].y, "  ");
                gotoxy(fall3[i].x, fall3[i].y, "  ");
                gotoxy(fall4[i].x, fall4[i].y, "  ");
            }

        fall1:
            fall1[0].x = rand() % 28 + 1;// 첫번째 랜덤장애물을 랜덤함수로 위치선정

            fall1[0].y = rand() % 18 + 1;
            fall1[1].x = fall1[0].x + 1;// 첫번째 랜덤장애물이 위치가 정해지면 사각형으로만들기 위해 위치선정
            fall1[1].y = fall1[0].y;
            fall1[2].x = fall1[0].x;
            fall1[2].y = fall1[0].y + 1;
            fall1[3].x = fall1[0].x + 1;
            fall1[3].y = fall1[0].y + 1;
        fall2:
            fall2[0].x = rand() % 28 + 1;//위와 마찬갖지

            fall2[0].y = rand() % 18 + 1;
            fall2[1].x = fall2[0].x + 1;
            fall2[1].y = fall2[0].y;
            fall2[2].x = fall2[0].x;
            fall2[2].y = fall2[0].y + 1;
            fall2[3].x = fall2[0].x + 1;
            fall2[3].y = fall2[0].y + 1;
        fall3:
            fall3[0].x = rand() % 28 + 1;// 위와 마찬가지

            fall3[0].y = rand() % 18 + 1;
            fall3[1].x = fall3[0].x + 1;
            fall3[1].y = fall3[0].y;
            fall3[2].x = fall3[0].x;
            fall3[2].y = fall3[0].y + 1;
            fall3[3].x = fall3[0].x + 1;
            fall3[3].y = fall3[0].y + 1;
        fall4:
            fall4[0].x = rand() % 28 + 1;//위와 마찬가지

            fall4[0].y = rand() % 18 + 1;
            fall4[1].x = fall4[0].x + 1;
            fall4[1].y = fall4[0].y;
            fall4[2].x = fall4[0].x;
            fall4[2].y = fall4[0].y + 1;
            fall4[3].x = fall4[0].x + 1;
            fall4[3].y = fall4[0].y + 1;

            item.x = rand() % 28 + 1;// 아이템의 위치를 랜덤으로 선정

            item.y = rand() % 18 + 1;
        ask:
            item2.x = rand() % 28 + 1;

            item2.y = rand() % 18 + 1;
            if (item.x == item2.x && item.y == item2.y)// 아이템1,2가 위치가 같을때 다시 돌아가서 위치 재설정
                goto ask;
            for (i = 0; i < 4; i++) {// 아이템 위치가 랜덤장애물 위치랑 같을때 돌아가서 재설정
                if (fall1[i].x == item.x && fall1[i].y == item.y)
                    goto fall1;
                if (fall1[i].x == item2.x && fall1[i].y == item2.y)
                    goto fall1;
            }
            for (i = 0; i < 4; i++) {// 위와 마찬가지
                if (fall2[i].x == item.x && fall2[i].y == item.y)
                    goto fall2;
                if (fall2[i].x == item2.x && fall2[i].y == item2.y)
                    goto fall2;
                if (fall3[i].x == item.x && fall3[i].y == item.y)
                    goto fall3;
                if (fall3[i].x == item2.x && fall3[i].y == item2.y)
                    goto fall3;
                if (fall4[i].x == item.x && fall4[i].y == item.y)
                    goto fall4;
                if (fall4[i].x == item2.x && fall4[i].y == item2.y)
                    goto fall4;
                if (snake[0].x == fall1[i].x && snake[0].y == fall1[i].y)// 랜덤장애물이 아이템먹고 램덤으로 위치할때 머리부분에 생성안되게 하는 코드
                    goto fall1;
                if (snake[0].x == fall2[i].x && snake[0].y == fall2[i].y)
                    goto fall2;
                if (snake[0].x == fall3[i].x && snake[0].y == fall3[i].y)
                    goto fall3;
                if (snake[0].x == fall4[i].x && snake[0].y == fall4[i].y)
                    goto fall4;
                if (snake[0].x + 1 == fall1[i].x && snake[0].y == fall1[i].y)// 랜덤장애물이 아이템먹고 램덤으로 위치할때 머리근처에 생성안되게 하는 코드
                    goto fall1;
                if (snake[0].x + 1 == fall2[i].x && snake[0].y == fall2[i].y)
                    goto fall2;
                if (snake[0].x + 1 == fall3[i].x && snake[0].y == fall3[i].y)
                    goto fall3;
                if (snake[0].x + 1 == fall4[i].x && snake[0].y == fall4[i].y)
                    goto fall4;
                if (snake[0].x - 1 == fall1[i].x && snake[0].y == fall1[i].y)
                    goto fall1;
                if (snake[0].x - 1 == fall2[i].x && snake[0].y == fall2[i].y)
                    goto fall2;
                if (snake[0].x - 1 == fall3[i].x && snake[0].y == fall3[i].y)
                    goto fall3;
                if (snake[0].x - 1 == fall4[i].x && snake[0].y == fall4[i].y)
                    goto fall4;
                if (snake[0].x == fall1[i].x && snake[0].y + 1 == fall1[i].y)
                    goto fall1;
                if (snake[0].x == fall2[i].x && snake[0].y + 1 == fall2[i].y)
                    goto fall2;
                if (snake[0].x == fall3[i].x && snake[0].y + 1 == fall3[i].y)
                    goto fall3;
                if (snake[0].x == fall4[i].x && snake[0].y + 1 == fall4[i].y)
                    goto fall4;
                if (snake[0].x == fall1[i].x && snake[0].y - 1 == fall1[i].y)
                    goto fall1;
                if (snake[0].x == fall2[i].x && snake[0].y - 1 == fall2[i].y)
                    goto fall2;
                if (snake[0].x == fall3[i].x && snake[0].y - 1 == fall3[i].y)
                    goto fall3;
                if (snake[0].x == fall4[i].x && snake[0].y - 1 == fall4[i].y)
                    goto fall4;
            }

            gotoxy(1, 21, "Score : ");// 스코어 위치 설정


            printf("%d", score);// 점수 설정



            if (len < 100)// 꼬리가 일정정도 이상 안넘을시 꼬리끝이 한칸다음으로 넘어가고 len함수 증가

            {

                snake[len] = snake[len - 1];

                len++;

            }




        }

        if (snake[0].x == fall1[0].x && snake[0].y == fall1[0].y)// 스네이크머리가 랜덤장애물에 부딪히면 반복문 탈출
            break;
        if (snake[0].x == fall1[1].x && snake[0].y == fall1[1].y)
            break;
        if (snake[0].x == fall1[2].x && snake[0].y == fall1[2].y)
            break;
        if (snake[0].x == fall1[3].x && snake[0].y == fall1[3].y)
            break;

        if (snake[0].x == fall2[0].x && snake[0].y == fall2[0].y)
            break;
        if (snake[0].x == fall2[1].x && snake[0].y == fall2[1].y)
            break;
        if (snake[0].x == fall2[2].x && snake[0].y == fall2[2].y)
            break;
        if (snake[0].x == fall2[3].x && snake[0].y == fall2[3].y)
            break;

        if (snake[0].x == fall3[0].x && snake[0].y == fall3[0].y)
            break;
        if (snake[0].x == fall3[1].x && snake[0].y == fall3[1].y)
            break;
        if (snake[0].x == fall3[2].x && snake[0].y == fall3[2].y)
            break;
        if (snake[0].x == fall3[3].x && snake[0].y == fall3[3].y)
            break;
        if (snake[0].x == fall4[0].x && snake[0].y == fall4[0].y)
            break;
        if (snake[0].x == fall4[1].x && snake[0].y == fall4[1].y)
            break;
        if (snake[0].x == fall4[2].x && snake[0].y == fall4[2].y)
            break;
        if (snake[0].x == fall4[3].x && snake[0].y == fall4[3].y)
            break;
        start = clock();// 시간 재는것을 시작*************************************
        for (i = 0; i < 4; i++) {//랜덤장애물의 위치에따른 모양설정
            gotoxy(fall1[i].x, fall1[i].y, "■");
        }
        for (i = 0; i < 4; i++) {
            gotoxy(fall2[i].x, fall2[i].y, "■");
        }
        for (i = 0; i < 4; i++) {
            gotoxy(fall3[i].x, fall3[i].y, "■");
        }
        for (i = 0; i < 4; i++) {
            gotoxy(fall4[i].x, fall4[i].y, "■");
        }
        gotoxy(item.x, item.y, "º");//아이템 위치에따른 모양살정
        gotoxy(item2.x, item2.y, "º");

        move_snake(snake, len);// 위에 정의한 함수 불러오기

        Sleep(speed);// 스피드에 따른 지연 설정 낮으면 낮을수록 빨라짐
        end = clock();// 시간 재는것이 끝나는 것을 선언*************************
        timec += (double)(end - start) / CLK_TCK; //시간차를 원래 변수의 값에 더하여 저장*************************************************************
        gotoxy(7, 21, "시간: ");//************************************************
        printf("%d ", 30 - (int)timec);// 시간줄어드는걸 프린트**********************
    }

    for (i = 0; i < 4; i++) {//랜덤 장애물로 반복문 탈출시 게임오버
        if (snake[0].x == fall1[i].x && snake[0].y == fall1[i].y)
            system("cls");
            gameover();
            system("cls");
        firstwindow();
    }
    for (i = 0; i < 4; i++) {
        if (snake[0].x == fall2[i].x && snake[0].y == fall2[i].y)
            system("cls");
            gameover();
            system("cls");
        firstwindow();
    }
    for (i = 0; i < 4; i++) {
        if (snake[0].x == fall3[i].x && snake[0].y == fall3[i].y)
            system("cls");
            gameover();
            system("cls");
        firstwindow();
    }
    for (i = 0; i < 4; i++) {
        if (snake[0].x == fall4[i].x && snake[0].y == fall4[i].y)
            system("cls");
            gameover();
            system("cls");
        firstwindow();
    };
    if (score == 40) {//스코어 모아서 반복문 탈출시 다음스테이지 전환

        stage4draw();
    }
    if (check_snake(snake, len) == 0) {//맵이나 몸에 부딪혀 반복문 탈출시 게임오버
        system("cls");
        gameover();
        system("cls");
        firstwindow();

    }
    if (timec >= 30) {
        system("cls");
        gameover();
        system("cls");
        firstwindow();
    }//일정 시간 넘어가면 게임오버******************************



}