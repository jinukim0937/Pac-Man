#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

//Ű���尪 ����
#define up 0
#define down 1
#define left 2
#define right 3
#define submit 4
#define fast 5
#define slow 6

void init();//�ʱ�ȭ�Լ�(�ܼ� ũ�� ����, â���� ����, Ŀ������ ��)
int keycontrol();
void gotoxy(int, int);
void title();
int menu();
int maplist();
void info();//��������â �Լ�
void drawmap(int*, int*, int*, int*);
void gloop(int);
void pacman_move(int*, int*, int, int, int*, int*);
char ghost_move(int*, int*, int, int, int);
void setcolor(int, int);
void drawnow(int*,int*);

//�÷� ����
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

char tempmap[20][36];// ���� �ӽ� �����ϴ� �迭

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

//�ʱ�ȭ �Լ�
void init() {
	system("mode con cols=83 lines=21| title Pac-Man");
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}

//Ű �Է¹޴� �Լ�
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
	else if (temp == ' ') {//�����̽���(����)�� ���� ��ư
		return submit;
	}
	else if (temp == 'u' || temp == 'U') {
		return fast;
	}
	else if (temp == 'i' || temp == 'I') {
		return slow;
	}
}

//goto�Լ�
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
	printf("> ���� ����");
	gotoxy(x, y + 1);
	printf("���� ���");
	gotoxy(x, y + 2);
	printf("���� ����");
	while (1) {//���ѹݺ�
		int n = keycontrol();//Ű������ �޾ƿ���
		switch (n) {
		case up: {//�Է��� Ű�� ���� up�� ���}
			if (y > 12) {//y�� 12~14������ �̵�
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, --y);
				printf(">");
			}
			break;
		}

		case down: {//�Է��� Ű�� ���� down�� ���}
			if (y < 14) {//y�� 12~14������ �̵�
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, ++y);
				printf(">");
			}
			break;
		}

		case submit: {
			return y - 12; // y���� ��ġ�� 12�����Ƿ� y-12fmf �ϸ�
						   // 0,1,2 �� ���ڸ� ���� �� �ִ�.
		}
		}
	}
}

int maplist() {
	int x = 24;
	int y = 6;
	system("cls");
	printf("\n\n");
	printf("                  [ ��  �� ��]\n\n");

	gotoxy(x - 2, y);
	printf("> Easy");
	gotoxy(x, y + 1);
	printf("Hard");
	gotoxy(x, y + 2);
	printf("Back");

	while (1) {//���ѹݺ�
		int n = keycontrol();//Ű������ �޾ƿ���
		switch (n) {
		case up: {//�Է��� Ű�� ���� up�� ���}
			if (y > 6) {//y�� 6~9������ �̵�
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, --y);
				printf(">");
			}
			break;
		}

		case down: {//�Է��� Ű�� ���� down�� ���}
			if (y < 9) {//y�� 6~9������ �̵�
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, ++y);
				printf(">");
			}
			break;
		}

		case submit: {
			return y - 6; // y���� ��ġ�� 6�����Ƿ� y-12fmf �ϸ�
						   // 0,1,2 �� ���ڸ� ���� �� �ִ�.
		}
		}
	}

}
void info() {
	system("cls");
	printf("\n");
	printf("     [���� ����]\n");
	printf("     �Ѹ��� �����Ͽ� ������ ���� ����Ʈ�� �׾� �ְ������� �������� �����Ѵ�.\n\n");
	printf("     [���� ���]\n");
	printf("     ���ӽ��۽� ���̵��� ���������ϴ�.(Easy,Hard)\n");
	printf("     �ּ� ����(100 point)�� ȹ���ؾ� �������� �� �� �ִ�.\n");
	printf("     ������ �ӵ� ������ �����ϴ�(�⺻60 �ּ�0 �ִ�100)\n");
	printf("     U �Է� --> Speed UP \n");
	printf("     I �Է� --> Speed DOWn \n\n");
	printf("     [���۹�]\n");
	printf("     �̵� : W, A, S, D\n");
	printf("     ���� : �� �� �� �� �� \n\n");
	printf("     [���� ������]\n");
	printf("     8�� PacMen\n");
	printf("     ���� ����ȣ ������\n\n");
	printf("     ----�����̽��ٸ� ������ ����ȭ������ �̵��մϴ�.----");


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
				printf(" ");//�����
			}
			else if (temp == '1') {
				setcolor(blue, blue);
				printf("#");//��
			}
			else if (temp == '2') {
				setcolor(yellow, black);
				*x = w;//�÷��̾� ��ǥ�� ����
				*y = h;
				printf("P");//����
			}
			else if (temp == '3') {
				setcolor(white, white);
				printf("o");//������ 
			}
			else if (temp == '4') {
				setcolor(brown, black);
				*mx = w;//���� ��ǥ�� ����
				*my = h;
				printf("G");//����
			}
			else if (temp == '5') {
				setcolor(white, black);
				printf("*");//����Ʈ
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
			printf("\n                  ����� ������:%d�� �Դϴ�", *point);

		}
		else
		{
			gotoxy(40, 18);
			printf("100�� �̻��̾�� ������ ����˴ϴ�!!\n");
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
	printf("----���� ����:%d��---- \n", *point);
	gotoxy(45, 13);
	printf("���� ������ ���ǵ�:%d          \n", (100 - *ghost_speed));
	gotoxy(45, 2);
	printf(" [ ���� �ӵ����� ]   \n");
	gotoxy(45, 4);
	printf("  ������ : press U   \n");
	gotoxy(45, 5);
	printf("  ������ : press I   \n");
	gotoxy(45, 6);
	printf("  �ּ� 0  �ִ� 100\n");
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