#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

//키보드값 정의
#define up 0
#define down 1
#define left 2
#define right 3
#define submit 4
#define fast 5
#define slow 6

void init();//초기화함수(콘솔 크기 설정, 창제목 설정, 커서제거 등)
int keycontrol();
void gotoxy(int, int);
void title();
int menu();
int maplist();
void info();//게임정보창 함수
void drawmap(int*, int*, int*, int*);
void gloop(int);
void pacman_move(int*, int*, int, int, int*, int*);
char ghost_move(int*, int*, int, int, int);
void setcolor(int, int);
void drawnow(int*,int*);

//컬러 정의
enum {
	black,
	blue,
	green,
	red,
	purple,
	brown,
	yellow,
	white
};

char tempmap[20][36];// 맵을 임시 저장하는 배열

char map1[20][36] = {

	 "111111111111111111111111111111111111",
	 "125555555555555555555555555555555551",
	 "155551111115555111111555511111155551",
	 "155551111115555111111555511111155551",
	 "155151111115555111111555511111155551",
	 "155555555555555555555551555555555551",
	 "155551111115555111111555511111155551",
	 "155551111115555111111555511111155551",
	 "155551111115515111111555511111155551",
	 "155555555555555555555555155555555551",
	 "155551111115555111111555511111155551",
	 "155551111115555111111555511111155551",
	 "155551111115555111111555511111155551",
	 "155555555555155555555555555555555551",
	 "155551111115555111111515511111155551",
	 "155551111115555111111555511111155551",
	 "155551111115555111111555511111155551",
	 "151555555555555555555555555555555551",
	 "155555555555555555555555555555555431",
	 "111111111111111111111111111111111111"
};
char map2[20][36] = {

 "1111111111111111111111111111111111",
 "1255555555555555555555555555555551",
 "1555555155555555555555551555555551",
 "1551115555555155555555555555555151",
 "1551115511115551115555115151115551",
 "1551115511115555555555115151115551",
 "1555551555555555555555555555555551",
 "1555555555555555555555555111115511",
 "1551111111115555555551115555555551",
 "1555551551115111111111115555555151",
 "1555555555555555555555555555555511",
 "1555115115515111551111155111115551",
 "1555555555555555555555555555555511",
 "1551115511115555551111155111111511",
 "1551115511115555551111155111111511",
 "1551115511115555551111155111111511",
 "1555551555555555555555555555555551",
 "1555555555551555555555555555555551",
 "1555555555555555555555415555555531",
 "1111111111111111111111111111111111"
};

int main() {
	init();
	while (1) {
		title();
		int menucode = menu();
		if (menucode == 0) {
			int n = maplist();

			if (n == 0) {
				gloop(0);
			}
			else if (n == 1) {
				gloop(1);
			}
		}
		else if (menucode == 1) {
			info();
		}
		else if (menucode == 2) {
			return 0;
		}
		system("cls");
		setcolor(white, black);
	}

	return 0;
}

//초기화 함수
void init() {
	system("mode con cols=83 lines=21| title Pac-Man");
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}

//키 입력받는 함수
int keycontrol() {
	char temp = getch();

	if (temp == 'w' || temp == 'W') {
		return up;
	}
	else if (temp == 'a' || temp == 'A') {
		return left;
	}
	else if (temp == 's' || temp == 'S') {
		return down;
	}
	else if (temp == 'd' || temp == 'D') {
		return right;
	}
	else if (temp == ' ') {//스페이스바(공백)이 선택 버튼
		return submit;
	}
	else if (temp == 'u' || temp == 'U') {
		return fast;
	}
	else if (temp == 'i' || temp == 'I') {
		return slow;
	}
}

//goto함수
void gotoxy(int x, int y) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}

void title() {
	setcolor(blue, black);
	printf("\n\n\n\n");
	printf("      #####     #    #####   #     #     #    #   # \n");
	printf("      #    #   # #   #       ##   ##    # #   ##  # \n");
	printf("      #####   #####  #       #  #  #   #####  # # # \n");
	printf("      #	      #   #  #       #     #   #   #  #  ## \n");
	printf("      #	      #   #  #####   #     #   #   #  #   # \n");
	setcolor(white, black);
}

int menu() {
	int x = 24;
	int y = 12;
	gotoxy(x - 2, y);
	printf("> 게임 시작");
	gotoxy(x, y + 1);
	printf("게임 방법");
	gotoxy(x, y + 2);
	printf("게임 종료");
	while (1) {//무한반복
		int n = keycontrol();//키값으로 받아오기
		switch (n) {
		case up: {//입력한 키의 값이 up인 경우}
			if (y > 12) {//y는 12~14까지만 이동
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, --y);
				printf(">");
			}
			break;
		}

		case down: {//입력한 키의 값이 down인 경우}
			if (y < 14) {//y는 12~14까지만 이동
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, ++y);
				printf(">");
			}
			break;
		}

		case submit: {
			return y - 12; // y시작 위치가 12였으므로 y-12fmf 하면
						   // 0,1,2 세 숫자를 받을 수 있다.
		}
		}
	}
}

int maplist() {
	int x = 24;
	int y = 6;
	system("cls");
	printf("\n\n");
	printf("                  [ 맵  선 택]\n\n");

	gotoxy(x - 2, y);
	printf("> Easy");
	gotoxy(x, y + 1);
	printf("Hard");
	gotoxy(x, y + 2);
	printf("Back");

	while (1) {//무한반복
		int n = keycontrol();//키값으로 받아오기
		switch (n) {
		case up: {//입력한 키의 값이 up인 경우}
			if (y > 6) {//y는 6~9까지만 이동
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, --y);
				printf(">");
			}
			break;
		}

		case down: {//입력한 키의 값이 down인 경우}
			if (y < 9) {//y는 6~9까지만 이동
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, ++y);
				printf(">");
			}
			break;
		}

		case submit: {
			return y - 6; // y시작 위치가 6였으므로 y-12fmf 하면
						   // 0,1,2 세 숫자를 받을 수 있다.
		}
		}
	}

}
void info() {
	system("cls");
	printf("\n");
	printf("     [게임 목적]\n");
	printf("     팩맨을 조종하여 유령을 피해 포인트를 쌓아 최고점수로 목적지에 도달한다.\n\n");
	printf("     [게임 방법]\n");
	printf("     게임시작시 난이도를 설정가능하다.(Easy,Hard)\n");
	printf("     최소 점수(100 point)를 획득해야 목적지에 들어갈 수 있다.\n");
	printf("     유령의 속도 조절이 가능하다(기본60 최소0 최대100)\n");
	printf("     U 입력 --> Speed UP \n");
	printf("     I 입력 --> Speed DOWn \n\n");
	printf("     [조작법]\n");
	printf("     이동 : W, A, S, D\n");
	printf("     선택 : 스 페 이 스 바 \n\n");
	printf("     [게임 개발자]\n");
	printf("     8조 PacMen\n");
	printf("     김경민 김정호 김진우\n\n");
	printf("     ----스페이스바를 누르면 메인화면으로 이동합니다.----");


	while (1) {
		if (keycontrol() == submit) {
			break;
		}
	}
}

void drawmap(int* x, int* y, int* mx, int* my) {
	system("cls");
	int h, w;


	for (h = 0; h < 20; h++) {
		for (w = 0; w < 36; w++) {
			char temp = tempmap[h][w];
			if (temp == '0') {
				setcolor(black, black);
				printf(" ");//빈공간
			}
			else if (temp == '1') {
				setcolor(blue, blue);
				printf("#");//벽
			}
			else if (temp == '2') {
				setcolor(yellow, black);
				*x = w;//플레이어 좌표값 저장
				*y = h;
				printf("P");//시작
			}
			else if (temp == '3') {
				setcolor(white, white);
				printf("o");//목적지 
			}
			else if (temp == '4') {
				setcolor(brown, black);
				*mx = w;//유령 좌표값 저장
				*my = h;
				printf("G");//유령
			}
			else if (temp == '5') {
				setcolor(white, black);
				printf("*");//포인트
			}
		}
		printf("\n");
	}
	setcolor(white, black);
}

void gloop(int mapcode) {
	int pacman_x, pacman_y;
	int ghost_x, ghost_y;
	int point = 0;
	int playing = 1;
	int dir_x = -1;
	int dir_y = 0;
	int ghost_speed = 40;
	int ghost_position = 5;
	char ghpst_state;

	if (mapcode == 0) {
		memcpy(tempmap, map1, sizeof(tempmap));
	}
	else if (mapcode == 1) {
		memcpy(tempmap, map2, sizeof(tempmap));
	}
	drawmap(&pacman_x, &pacman_y, &ghost_x, &ghost_y);

	while (playing) {
		drawnow(&point, &ghost_speed);
		ghpst_state = ghost_move(&ghost_x, &ghost_y, dir_x, dir_y, ghost_position);
		Sleep(ghost_speed);

		switch(ghpst_state){
		case 's':
			if ((dir_x == -1) && (dir_y == 0)) {
				dir_x = 0;
				dir_y = -1;
			}
			else if ((dir_x == 0) && (dir_y == -1)) {
				dir_x = 1;
				dir_y = 0;
			}
			else if ((dir_x == 1) && (dir_y == 0)) {
				dir_x = 0;
				dir_y = 1;
			}
			else if ((dir_x == 0) && (dir_y == 1)) {
				dir_x = -1;
				dir_y = 0;
			}
			break;
		case 'g':
			setcolor(white, black);
			playing = 0;
			system("cls");
			printf("\n\n\n\n\n\n\n");
			printf("      #####     #     #     #   #####        ####  #       # #####  #####          \n");
			printf("      #        # #    ##   ##   #           #    #  #     #  #      #   #          \n");
			printf("      #  ##   #####   #  #  #   #####       #    #   #   #   #####  ####           \n");
			printf("      #	  #   #   #   #     #   #           #    #    # #    #      #   #          \n");
			printf("      #####   #   #   #     #   #####        ####      #     #####  #    #         \n");
			while (1) {
				if (keycontrol() == submit) {
					break;
				}
			}
			break;
		case 'b':
			ghost_position = 0;
			break;
		case 'p':
			ghost_position = 5;
			break;
		}

		if (kbhit()) {
			switch (keycontrol()) {
			case up:
				pacman_move(&pacman_x, &pacman_y, 0, -1, &point, &playing);
				break;

			case down:
				pacman_move(&pacman_x, &pacman_y, 0, 1, &point, &playing);
				break;

			case right:
				pacman_move(&pacman_x, &pacman_y, 1, 0, &point, &playing);
				break;

			case left:
				pacman_move(&pacman_x, &pacman_y, -1, 0, &point, &playing);
				break;

			case submit:
				playing = 0;

			case fast:
				if (ghost_speed > 0) {
					ghost_speed -= 5;
				}
				break;


			case slow:
				if (ghost_speed < 100) {
				ghost_speed += 5;
			}
				break;

			}
		}
	}
}
void pacman_move(int* x, int* y, int _x, int _y, int* point, int* playing) {

	char mapobject = tempmap[*y + _y][*x + _x];

	switch (mapobject) {
	case '0':
		setcolor(yellow, black);
		tempmap[*y][*x] = '0';
		gotoxy(*x, *y);
		printf(" ");
		tempmap[*y + _y][*x + _x] = '2';
		gotoxy(*x + _x, *y + _y);
		printf("P");
		*x += _x;
		*y += _y;
		break;

	case '1':
		break;

	case '3':
		if (*point >= 100)
		{
			setcolor(white, black);
			*playing = 0;
			system("cls");
			printf("\n\n\n\n");
			printf("     #       #  #####  #####  ########   ####    ####   #     #     \n");
			printf("      #     #     #    #         #      #    #   #   #   #   #      \n");
			printf("       #   #      #    #         #      #    #   ####      #        \n");
			printf("      	# #       #    #         #      #    #   #   #     #        \n");
			printf("         #      #####  #####     #       ####    #    #    #        \n\n");
			printf("\n                  당신의 점수는:%d점 입니다", *point);

		}
		else
		{
			gotoxy(40, 18);
			printf("100점 이상이어야 게임이 종료됩니다!!\n");
			break;
		}
		while (1) {
			if (keycontrol() == submit) {
				break;
			}
		}
	case '5':
		setcolor(yellow, black);
		*point += 1;
		tempmap[*y][*x] = '0';
		gotoxy(*x, *y);
		printf(" ");
		tempmap[*y + _y][*x + _x] = '2';
		gotoxy(*x + _x, *y + _y);
		printf("P");
		*x += _x;
		*y += _y;
		break;
	}
}

void drawnow(int* point,int* ghost_speed) {

	setcolor(white, black);
	gotoxy(45, 11);
	printf("----현재 점수:%d점---- \n", *point);
	gotoxy(45, 13);
	printf("현재 유령의 스피드:%d          \n", (100 - *ghost_speed));
	gotoxy(45, 2);
	printf(" [ 유령 속도조절 ]   \n");
	gotoxy(45, 4);
	printf("  빠르게 : press U   \n");
	gotoxy(45, 5);
	printf("  느리게 : press I   \n");
	gotoxy(45, 6);
	printf("  최소 0  최대 100\n");
}
char ghost_move(int* ghost_x, int* ghost_y, int _ghost_x, int _ghost_y, int ghost_position) {
	char mapobject = tempmap[*ghost_y + _ghost_y][*ghost_x + _ghost_x];

	switch (mapobject) {

	case '0':
		if (ghost_position == 0) {
			tempmap[*ghost_y][*ghost_x] = '0';
			gotoxy(*ghost_x, *ghost_y);
			printf(" ");
		} else if (ghost_position == 5) {
			setcolor(white, black);
			tempmap[*ghost_y][*ghost_x] = '5';
			gotoxy(*ghost_x, *ghost_y);
			printf("*");
		}
		setcolor(brown, black);
		tempmap[*ghost_y + _ghost_y][*ghost_x + _ghost_x] = '4';
		gotoxy(*ghost_x + _ghost_x, *ghost_y + _ghost_y);
		printf("G");
		*ghost_x += _ghost_x;
		*ghost_y += _ghost_y;
		return 'b';

	case '1':
		return 's';
	case '2':
		return 'g';
	case '3':
		return 's';
	case '4':
		return 's';
	case '5':
		setcolor(white, black);
		if (ghost_position == 5) {
			tempmap[*ghost_y][*ghost_x] = '5';
			gotoxy(*ghost_x, *ghost_y);
			printf("*");
		} else if(ghost_position == 0){
			tempmap[*ghost_y][*ghost_x] = '0';
			gotoxy(*ghost_x, *ghost_y);
			printf(" ");
		}
		
		tempmap[*ghost_y + _ghost_y][*ghost_x + _ghost_x] = '4';
		setcolor(brown, black);
		gotoxy(*ghost_x + _ghost_x, *ghost_y + _ghost_y);
		printf("G");
		*ghost_x += _ghost_x;
		*ghost_y += _ghost_y;
		return 'p';
	}

}


void setcolor(int forground, int background) {

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	int code = forground + background * 16;
	SetConsoleTextAttribute(consoleHandle, code);
}