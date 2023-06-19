#include <stdio.h>
#include <windows.h>
#include "teamplus.h"

void titleDraw();
void GotoXY(int, int);
int menuDraw();
void infoDraw();
void stage1draw(void);
void firstwindow(void) {

	mciSendString(TEXT("open \"gamemain.wav\" type mpegvideo alias gamemain"), NULL, 0, NULL); //배경 음악 열기
	mciSendString(TEXT("play gamemain repeat"), NULL, 0, NULL); //배경음악 반복 재생

	while (1) {
		titleDraw();
		int menuCode = menuDraw();
		if (menuCode == 0) {
			mciSendString(TEXT("close gamemain"), NULL, 0, NULL); //배경 음악 닫기
			stage1draw();
			break;
		}
		else if (menuCode == 1) {
			infoDraw();
		}
		else if (menuCode == 2) {
			break;
		}
		system("cls");
	}


}
void infoDraw() {
	system("cls");
	int x = 24;
	int y = 12;
	GotoXY(x - 2, y);
	printf("                [ 조작법 ] \n\n");
	GotoXY(x, y + 1);
	printf("              이 동: 방향키 \n");
	GotoXY(x, y + 2);
	printf("              선택 : z \n");
	GotoXY(x, y + 5);
	printf("              z를 누르면 메인화면으로 이동합니다. ");

	while (1) {
		int key = GetKeyDown();
		if (key == 5) {
			break;
		}
	}
}

void titleDraw() {
	printf("\n\n\n\n");
	printf("         #####    #####   #         #    #     #    \n");
	printf("         #    #   #       #        # #    #   #     \n");
	printf("         #####    #####   #       #####    ###      \n");
	printf("         #   #    #       #       #   #     #       \n");
	printf("         #    #   #####   ######  #   #     #       \n");

}
void GotoXY(int x, int y);
int menuDraw() {
	int x = 24;
	int y = 12;
	GotoXY(x - 2, y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3); //파란색
	printf("> 게 임 시 작");
	GotoXY(x, y + 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13); //파란색
	printf("키  정   보");
	GotoXY(x, y + 2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //파란색
	printf("종       료 ");
	while (1) {
		int key = GetKeyDown();
		switch (key) {
		case 1: {
			if (y > 12) {
				GotoXY(x - 2, y); //y는 12~14까지만 이동
				printf(" "); //원래 위치지우기
				GotoXY(x - 2, --y); //새로 이동한 위치로 이동하여
				printf(">");
			}
			break;
		}
		case 2: {
			if (y < 14) {
				GotoXY(x - 2, y);
				printf(" ");
				GotoXY(x - 2, ++y);
				printf(">");
			}
			break;
		}
		case 5: {
			return y - 12;

		}
		}

	}
	return 0;
}