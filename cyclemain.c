#include<stdio.h>
#include<windows.h>

#include <mmsystem.h> //playsound를 사용하기 위해서
#pragma comment(lib,"winmm.lib") //별도의 라이브러리 필요함
#include "Digitalv.h"

void GotoXY(int x, int y);
void stage1(void);
void stage2(void);
void stage3(void);
void stage4(void);
void stage5(void);
void stage1draw(void)
{
    int x = 25;
    system("cls");
    GotoXY(x, 8);
    printf("  ###   #####     #       #####    #####     #####");
    GotoXY(x, 9);
    printf(" #        #      # #     #         #           #   ");
    GotoXY(x, 10);
    printf("  ###     #     # # #    #   ###   #####       #   ");
    GotoXY(x, 11);
    printf("     #    #    #     #   #     #   #           #   ");
    GotoXY(x, 12);
    printf("  ###     #    #     #    #### #   #####     ##### ");
    GotoXY(x, 14);
    printf("     허들넘기 : 장애물을 피해 목적지에 도착하시오." );
    Sleep(3000);
    stage1();
}
void stage2draw(void)
{
    int x = 25;
    system("cls");
    GotoXY(x, 8);
    printf("  ###   #####     #       #####    #####     #####");
    GotoXY(x, 9);
    printf(" #        #      # #     #         #          # # ");
    GotoXY(x, 10);
    printf("  ###     #     # # #    #   ###   #####      # # ");
    GotoXY(x, 11);
    printf("     #    #    #     #   #     #   #          # # ");
    GotoXY(x, 12);
    printf("  ###     #    #     #    #### #   #####     #####");
    GotoXY(x, 14);
    printf("    별 피하기 : 목표점수 200점까지 살아 남으시오"  );
    Sleep(1000);
    stage2();
}
void stage3draw(void)
{
    int x = 25;
    system("cls");
    GotoXY(x, 8);
    printf("  ###   #####     #       #####    #####     #######");
    GotoXY(x, 9);
    printf(" #        #      # #     #         #          # # #");
    GotoXY(x, 10);
    printf("  ###     #     # # #    #   ###   #####      # # #");
    GotoXY(x, 11);
    printf("     #    #    #     #   #     #   #          # # #");
    GotoXY(x, 12);
    printf("  ###     #    #     #    #### #   #####     #######");
    GotoXY(x, 14);
    printf(" 지렁이게임 : 아이템(4점)을 획득하여 클리어 하시오"  );
    Sleep(1000);
    stage3();
}
void stage4draw(void)
{
    int x = 15;
    system("cls");
    GotoXY(x, 8);
    printf("  ###   #####     #       #####    #####     #####   #        #");
    GotoXY(x, 9);
    printf(" #        #      # #     #         #           #      #      #");
    GotoXY(x, 10);
    printf("  ###     #     # # #    #   ###   #####       #       #    #");
    GotoXY(x, 11);
    printf("     #    #    #     #   #     #   #           #        #  #");
    GotoXY(x, 12);
    printf("  ###     #    #     #    #### #   #####     #####       ##");
    GotoXY(x, 14);
    printf("     테트리스 : 다섯줄 완성시 클리어하시오                   ");
    Sleep(1000);
    stage4();
}
void stage5draw(void)
{
    int x = 25;
    system("cls");
    GotoXY(x, 8);
    printf("  ###   #####     #       #####    #####    #        #");
    GotoXY(x, 9);
    printf(" #        #      # #     #         #         #      #");
    GotoXY(x, 10);
    printf("  ###     #     # # #    #   ###   #####      #    #");
    GotoXY(x, 11);
    printf("     #    #    #     #   #     #   #           #  #");
    GotoXY(x, 12);
    printf("  ###     #    #     #    #### #   #####        ##");
    GotoXY(x, 14);
    printf("     도넛게임 : 타이밍(5번) 맞추어 클리어            ");
    Sleep(1000);
    stage5();
}

void gameclear(void) {

    int x = 15;
    system("cls");
    GotoXY(x, 8);
    printf("  #####      #      #     #   #####    #####   #        #####      #      #####    ");
    GotoXY(x, 9);
    printf(" #          # #     ##   ##   #       #        #        #         # #     #    #   ");
    GotoXY(x, 10);
    printf(" #   ###   # # #    # # # #   #####   #        #        #####    # # #    #####    ");
    GotoXY(x, 11);
    printf(" #     #  #     #   #  #  #   #       #        #        #       #     #   #    #   ");
    GotoXY(x, 12);
    printf("  #### #  #     #   #     #   #####    #####   ######   #####   #     #   #     #  ");
    GotoXY(x, 14);
    mciSendString(TEXT("close gaming"), NULL, 0, NULL); //배경 음악 닫기
    mciSendString(TEXT("open \"gameclear.wav\" type mpegvideo alias gameclear"), NULL, 0, NULL); //배경 음악 열기
    mciSendString(TEXT("play gameclear repeat"), NULL, 0, NULL); //배경음악 반복 재생

    Sleep(3000);
    mciSendString(TEXT("close gameclear"), NULL, 0, NULL); //배경 음악 닫기
    mciSendString(TEXT("open \"gamemain.wav\" type mpegvideo alias gamemain"), NULL, 0, NULL); //배경 음악 열기
    mciSendString(TEXT("play gamemain repeat"), NULL, 0, NULL); //배경음악 반복 재생
    
}

void gameover(void) {

    int x = 25;
    system("cls");
    GotoXY(x, 8);
    printf(" #####       #      #     #   #####    #####    #     #   #####   #####   ");
    GotoXY(x, 9);
    printf("#           # #     ##   ##   #       #     #   #     #   #       #    #  ");
    GotoXY(x, 10);
    printf("#   ###    # # #    # # # #   #####   #     #    #   #    #####   #####   ");
    GotoXY(x, 11);
    printf("#     #   #     #   #  #  #   #       #     #     # #     #       #    #  ");
    GotoXY(x, 12);
    printf(" #### #   #     #   #     #   #####    #####       #      #####   #     # ");
    GotoXY(x, 14);


    mciSendString(TEXT("close gaming"), NULL, 0, NULL); //배경 음악 닫기
    mciSendString(TEXT("open \"byebyeSound.wav\" type mpegvideo alias byebyeSound"), NULL, 0, NULL); //배경 음악 열기
    mciSendString(TEXT("play byebyeSound"), NULL, 0, NULL); //배경음악 반복 재생
    Sleep(2000);
    mciSendString(TEXT("close byebyeSound"), NULL, 0, NULL); //배경 음악 닫기

}
