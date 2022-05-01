#include <cstdio>
#include <iostream>
#include <io.h>
#include <cstring>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <windows.h>
using namespace std;

void color(int x) { //设置字体颜色
	/*
	0 = 黑色       8  = 灰色
	1 = 蓝色       9  = 淡蓝色
	2 = 绿色       10 = 淡绿色
	3 = 浅绿色     11 = 淡浅绿色
	4 = 红色       12 = 淡红色
	5 = 紫色       13 = 淡紫色
	6 = 黄色       14 = 淡黄色
	7 = 白色       15 = 亮白色
	*/
	if (x >= 0 && x <= 15)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
	else
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

inline void printEndl(int x) { //打印换行 
	if (x <= 1)
		printf("\n");
	else
		for (int i = 1; i <= x; i++)
			printf("\n");
}

inline void cls(bool debug) { //清屏
	system("cls");
}

inline void pause(bool inv) { //暂停 
	system(inv ? "pause > nul" : "pause");
}

inline void csi() { //清除输入区缓存 
	fflush(stdin);
}

inline void cso() { //清除输出区缓存 
	fflush(stdout);
}

inline void ding() {
	const char sound_ding = 7;
	putchar(sound_ding);
}
