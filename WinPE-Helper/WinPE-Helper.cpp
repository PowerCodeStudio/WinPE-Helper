﻿// WinPE-Helper.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include <cstdio>
#include <iostream>
#include <io.h>
#include <cstring>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <windows.h>
#include "power_command.hpp"
#define normal_version "10.6"
#define inside_version "22.06051"
#define compile_version "9end28"
#define channel "R (Release)"
using namespace std;
string __STR_WIM_PATH = "\\sources\\install.wim";
string __STR_ESD_PATH = "\\sources\\install.esd";
string wepath;

void FindWimEsd() {
	for (char i = 'C'; i <= 'Z'; i++) { //从C盘到Z盘挨个判断 
		char diskpath[3];
		diskpath[0] = i;
		diskpath[1] = ':';
		diskpath[2] = '\0';
		string qpath; //要寻找的路径 = 盘符 + "\sources\install.wim或esd" 
		qpath = diskpath + __STR_WIM_PATH;
		if (_access(qpath.c_str(), 0) != -1) {
			wepath = qpath;
			cout << "已寻找到 WIM 文件 在 " << wepath << endl;
			return;
		}
		qpath = diskpath + __STR_ESD_PATH;
		if (_access(qpath.c_str(), 0) != -1) {
			wepath = qpath;
			cout << "已寻找到 ESD 文件 在 " << wepath << endl;
			return;
		}
	}
	color(12);
	ding(); //发出声音 
	printf("警告：没有寻找到 WIM/ESD 文件，部分命令将出错\n");
	printf("你可以通过命令 \"wepath\" 来手动指定路径\n");
	wepath = "WIM/ESD_FILE_NOT_FOUND";
}

inline void version() {
	printf("PowerCode Studio WinPE Helper\n");
	// "　" 是全角空格，用于对齐内容 
	printf("版本　　: %s\n", normal_version);
	printf("内部版本: %s\n", inside_version);
	printf("构建版本: %s\n", compile_version);
	printf("通道　　: %s\n", channel);
	printf("(c) PowerCode Studio & CodeZhangBorui, All right reserved.\n");
}

inline void about() {
	printf("PowerCode Studio WinPE Helper\n");
	printf("采用 Visual Studio with C++14 构建，");
	printf("作者：CodeZhangBorui\n");
	printf("联系方式：[B站]PowerCodeStudio [Github]CodeZhangBorui\n");
	color(13);
	printf("Enjoy Coding Life!\n");
	color(7);
}

int main() {
	system("title WinPE Helper");
	color(15);
	printf("PowerCode Studio WinPE Helper [版本 %s]\n", normal_version);
	printf("(c) PowerCode Studio & CodeZhangBorui, All right reserved.\n");
	printEndl(0);
	FindWimEsd();
	printEndl(0);

	string inp;
	while (1) {
	cancel:; //标记 如果用户取消操作直接 goto 
		color(9);
		csi(); //清空输入缓存 
		printf("PEHelper > ");
		color(14);
		getline(cin, inp); //等待用户输入指令，不用cin的原因是cin输入空指令无法判断 
		color(7);
		transform(inp.begin(), inp.end(), inp.begin(), ::tolower); //将指令转为小写 
		if (inp == "") goto cancel; //如果是空指令，直接忽略，重新一次开始 
		else if (inp == "exit") return 0;
		else if (inp == "help") {
			printf("===== WinPE Helper 帮助 =====\n");
			printf("\n  通用：\n");
			printf("HELP       获取 WinPE Helper 帮助\n");
			printf("CLS        清空屏幕\n");
			printf("VER        显示 WinPE Helper 版本\n");
			printf("ABOUT      关于 WinPE Helper\n");
			printf("EXIT       退出 WinPE Helper\n");
			printf("\n  系统安装：\n");
			printf("WEPATH     重新查找或手动指定 WIM/ESD 文件位置\n");
			printf("WEINFO     获取 WIM/ESD 镜像信息\n");
			printf("SYSINSTALL 使用 Dism 安装系统\n");
			printf("BCDBOOT    设置启动项\n");
			printf("\n  软件：\n");
			printf("NOTEPAD    打开记事本\n");
			printf("REGEDIT    打开注册表编辑器\n");
			printf("CMD        打开新的 CMD 窗口\n");
			printf("SETUP      打开 WindowsPE 自带 GUI 系统安装\n");
			printf("\n  特色功能：\n");
			printf("COPYS      复制一个文件夹及其子文件夹内的所有文件\n");
			printEndl(0);
			printf("提示：可在任意功能提示输入时输入 C 来取消\n");

		}
		else if (inp == "ver") {
			version();

		}
		else if (inp == "cls") {
			system("cls");
			cso();

		}
		else if (inp == "about") {
			about();

		}
		else if (inp == "wepath") {
			cout << "当前 WIM/ESD 文件 在 " << wepath << endl;
			while (1) {
				csi();
				printf("请选择：手动指定新路径[w] 自动重新扫描[s] 取消[c]？");
				char mode = getchar();
				if (mode == 'w' || mode == 'W') {
					printf("请输入新路径：");
					cin >> wepath;
					break;
				}
				else if (mode == 's' || mode == 'S') {
					FindWimEsd();
					break;
				}
				else if (mode == 'c' || mode == 'C') {
					printf("用户取消操作\n");
					goto cancel;
				}
				else {
					printf("'%c' 不是一个有效的选项。", mode);
				}
			}

		}
		else if (inp == "weinfo") {
			string qcmd = "dism /Get-WimInfo /WimFile:" + wepath;
			system(qcmd.c_str());

		}
		else if (inp == "sysinstall") {
			string index, applydir;
			cout << "映像文件位置: " << wepath << endl;
			printf("索引: ");
			cin >> index;
			if (index == "c" || index == "C") { printf("用户取消操作\n\n"); goto cancel; }
			printf("目标应用目录: ");
			cin >> applydir;
			if (applydir == "c" || applydir == "C") { printf("用户取消操作\n\n"); goto cancel; }
			string qcmd = "dism /Apply-Image /ImageFile:" + wepath + " /Index:" + index + " /ApplyDir:" + applydir;
			cout << "> " << qcmd << endl;
			printf("确定？(Y/N) "); csi(); char yn = getchar(); if (yn == 'n' || yn == 'N') { printf("用户取消操作\n\n"); goto cancel; } printEndl(0);
			system(qcmd.c_str());

		}
		else if (inp == "bcdboot") {
			while (1) {
				csi();
				printf("请选择：使用UEFI启动[u] 使用传统启动[l] 取消[c]？");
				char mode = getchar();
				if (mode == 'u' || mode == 'U') {
					printf("请输入 Windows 系统目录路径：");
					string winpath, uefiDisk, qcmd;
					cin >> winpath;
					printf("请输入 EFI 系统分区（ESP）盘符（格式为 X:）：");
					cin >> uefiDisk;
					qcmd = "bcdboot " + winpath + " /s " + uefiDisk + " /f UEFI";
					cout << "> " << qcmd << endl;
					printf("确定？(Y/N) "); csi(); char yn = getchar(); if (yn == 'n' || yn == 'N') { printf("用户取消操作\n\n"); goto cancel; } printEndl(0);
					system(qcmd.c_str());
					break;
				}
				else if (mode == 'l' || mode == 'L') {
					printf("请输入 Windows 系统目录路径：");
					string winpath, sysDisk, qcmd;
					cin >> winpath;
					sysDisk = winpath.substr(0, 2);
					if (sysDisk.c_str()[1] != ':') {
						printf("请输入 Windows 系统所在分区盘符（格式为 X:）：");
						cin >> sysDisk;
					}
					qcmd = "bcdboot " + winpath + " /s " + sysDisk + " /f BIOS";
					cout << "> " << qcmd << endl;
					printf("确定？(Y/N) "); csi(); char yn = getchar(); if (yn == 'n' || yn == 'N') { printf("用户取消操作\n\n"); goto cancel; } printEndl(0);
					system(qcmd.c_str());
					break;
				}
				else if (mode == 'c' || mode == 'C') {
					printf("用户取消操作\n");
					goto cancel;
				}
				else {
					printf("'%c' 不是一个有效的选项。", mode);
				}
			}




		}
		else if (inp == "notepad") {
			system("start notepad");

		}
		else if (inp == "regedit") {
			system("start regedit");

		}
		else if (inp == "cmd") {
			system("start cmd");

		}
		else if (inp == "setup") {
			system("start setup");

		}
		else if (inp == "copys") {
			printf("COPYS 实用工具 [版本 1.0.22.04032]\n");
			//			printf("请注意：如果路径中含有空格，请将整段路径使用英文引号括起来\n");
			string from, to, qcmd;
			cout << "从：";
			getline(cin, from);
			if (from == "c" || from == "C") { printf("用户取消操作\n\n"); goto cancel; }
			cout << "到：";
			getline(cin, to);
			if (to == "c" || to == "C") { printf("用户取消操作\n\n"); goto cancel; }
			while (1) {
				csi();
				printf("请选择：复制所有[a] 只复制目录结构[t] 取消[c]？");
				char mode = getchar();
				if (mode == 'a' || mode == 'A') {
					string qcmd = "xcopy \"" + from + "\" \"" + to + "\" /E /C /F /H";
					//					cout << "> " << qcmd << endl;
					cout << "确定？"; csi(); char yn = getchar(); if (yn == 'n' || yn == 'N') { printf("用户取消操作\n\n"); goto cancel; } printEndl(0);
					system(qcmd.c_str());
					break;
				}
				else if (mode == 't' || mode == 'T') {
					string qcmd = "xcopy \"" + from + "\" \"" + to + "\" /E /C /F /H /T";
					//					cout << "> " << qcmd << endl;
					cout << "确定？"; csi(); char yn = getchar(); if (yn == 'n' || yn == 'N') { printf("用户取消操作\n\n"); goto cancel; } printEndl(0);
					system(qcmd.c_str());
					break;
				}
				else if (mode == 'c' || mode == 'C') {
					printf("用户取消操作\n");
					goto cancel;
				}
				else {
					printf("'%c' 不是一个有效的选项。", mode);
				}
			}
		}
		else {
			printf("命令无效\n请键入 \"help\" 或参考用户手册来获取更多信息\n");
		}
		printEndl(0);
	}
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
