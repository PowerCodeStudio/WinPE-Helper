#include <cstdio>
#include <iostream>
#include <io.h>
#include <cstring>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <windows.h>
using namespace std;

void color(int x) { //����������ɫ
	/*
	0 = ��ɫ       8  = ��ɫ
	1 = ��ɫ       9  = ����ɫ
	2 = ��ɫ       10 = ����ɫ
	3 = ǳ��ɫ     11 = ��ǳ��ɫ
	4 = ��ɫ       12 = ����ɫ
	5 = ��ɫ       13 = ����ɫ
	6 = ��ɫ       14 = ����ɫ
	7 = ��ɫ       15 = ����ɫ
	*/
	if (x >= 0 && x <= 15)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
	else
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

inline void printEndl(int x) { //��ӡ���� 
	if (x <= 1)
		printf("\n");
	else
		for (int i = 1; i <= x; i++)
			printf("\n");
}

inline void cls(bool debug) { //����
	system("cls");
}

inline void pause(bool inv) { //��ͣ 
	system(inv ? "pause > nul" : "pause");
}

inline void csi() { //������������� 
	fflush(stdin);
}

inline void cso() { //������������ 
	fflush(stdout);
}

inline void ding() {
	const char sound_ding = 7;
	putchar(sound_ding);
}
