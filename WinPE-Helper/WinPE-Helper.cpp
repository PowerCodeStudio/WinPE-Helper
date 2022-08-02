// WinPE-Helper.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include "power_command.hpp"
#define normal_version "11.0"
#define inside_version "22.08027"
#define compile_version "9ejcozm"
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
			if (!fileRead(wepath.c_str())) {
				color(12);
				ding(); //发出声音 
				printf("警告：当前文件无法读取，请检查文件！\n");
			}
			return;
		}
		qpath = diskpath + __STR_ESD_PATH;
		if (_access(qpath.c_str(), 0) != -1) {
			wepath = qpath;
			cout << "已寻找到 ESD 文件 在 " << wepath << endl;
			if (!fileRead(wepath.c_str())) {
				color(12);
				ding(); //发出声音 
				printf("警告：当前文件无法读取，请检查文件！\n");
			}
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
	printf("联系方式：[BiliBili]PowerCodeStudio [Github]CodeZhangBorui\n");
	color(13);
	printf("Enjoy Coding Life!\n");
	color(7);
}

inline void help() {
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
	printf("EXPLORER   打开内置小型文件资源管理器\n");
	printEndl(0);
	printf("提示：可在任意功能提示输入时输入 C 来取消\n");
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
		printf("PEHelper > "); //命令提示符
		color(14);
		csi(); //清空输入缓存
		cso(); //清空输出缓存
		getline(cin, inp); //等待用户输入指令，不用cin的原因是cin输入空指令无法判断 
		color(7);
		transform(inp.begin(), inp.end(), inp.begin(), ::tolower); //将指令转为小写 
		if (inp == "") goto cancel; //如果是空指令，直接忽略，重新一次开始 
		else if (inp == "exit") return 0;
		else if (inp == "help") {
			help();

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
				int mbret = MessageBox(GetConsoleWindow(), _T("请选择：手动指定新路径[是] 自动重新扫描[否] 取消？"), _T("选择"), MB_YESNOCANCEL);
				if (mbret == IDYES) {
					string inPath = SelectWimEsd();
					if (inPath == "CANCEL") {
						printf("用户取消操作\n\n");
						goto cancel;
					}
					else if (!fileExits(inPath.c_str())) {
						color(12);
						ding(); //发出声音
						printf("错误：此文件不存在，无法指定此文件。\n");
						printf("你可以通过命令 \"wepath\" 来手动指定路径\n");
						//wepath = "WIM/ESD_FILE_NOT_FOUND";
						//goto cancel;
					}
					else if (!fileRead(inPath.c_str())) {
						color(12);
						ding(); //发出声音 
						printf("警告：当前文件无法读取，请检查文件！\n");
						wepath = inPath;
						//goto cancel;
					}
					else {
						wepath = inPath;
						cout << "已选定文件：" << wepath << endl;
					}
					break;
				}
				else if (mbret == IDNO) {
					FindWimEsd();
					break;
				}
				else if (IDCANCEL) {
					printf("用户取消操作\n\n");
					goto cancel;
				}
				else {
					throw "Error: MessageBox return wrong, on module 'wepath'.";
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
			printf("请选择目标应用目录");
			applydir = SelectFolder();
			if (applydir == "CANCEL") {
				clearLine();
				printf("用户取消操作\n\n");
				goto cancel;
			}
			clearLine();
			cout << "目标应用目录: " << applydir << endl;
			string qcmd = "dism /Apply-Image /ImageFile:" + wepath + " /Index:" + index + " /ApplyDir:" + applydir;
			cout << "> " << qcmd << endl;
			int mbret = MessageBox(GetConsoleWindow(), _T("请查看控制台内的指令。\n确定？"), _T("警告"), MB_OKCANCEL | MB_ICONWARNING);
			if (mbret == IDCANCEL) {
				clearLine();
				printf("用户取消操作\n\n");
				goto cancel;
			}
			system(qcmd.c_str());

		}
		else if (inp == "bcdboot") {
			while (1) {
				csi();
				int mbret = MessageBox(GetConsoleWindow(), _T("请选择：使用UEFI启动[是] 使用传统启动[否] 取消？"), _T("选择"), MB_YESNOCANCEL);
				if (mbret == IDYES) {
					printf("请选择 Windows 系统目录路径：");
					string winpath, uefiDisk, qcmd;
					winpath = SelectFolder();
					if (winpath == "CANCEL") {
						clearLine();
						printf("用户取消操作\n\n");
						goto cancel;
					}
					cout << winpath << endl;
					printf("请输入 EFI 系统分区（ESP）盘符（格式为 X:）：");
					cin >> uefiDisk;
					qcmd = "bcdboot " + winpath + " /s " + uefiDisk + " /f UEFI";
					cout << "> " << qcmd << endl;
					int mbret = MessageBox(GetConsoleWindow(), _T("请查看控制台内的指令。\n确定？"), _T("警告"), MB_OKCANCEL | MB_ICONWARNING);
					if (mbret == IDCANCEL) {
						clearLine();
						printf("用户取消操作\n\n");
						goto cancel;
					}
					system(qcmd.c_str());
					break;
				}
				else if (mbret == IDNO) {
					printf("请选择 Windows 系统目录路径：");
					string winpath, sysDisk, qcmd;
					winpath = SelectFolder();
					if (winpath == "CANCEL") {
						clearLine();
						printf("用户取消操作\n\n");
						goto cancel;
					}
					cout << winpath << endl;
					sysDisk = winpath.substr(0, 2);
					if (sysDisk.c_str()[1] != ':') {
						printf("请输入 Windows 系统所在分区盘符（格式为 X:）：");
						cin >> sysDisk;
					}
					qcmd = "bcdboot " + winpath + " /s " + sysDisk + " /f BIOS";
					cout << "> " << qcmd << endl;
					int mbret = MessageBox(GetConsoleWindow(), _T("请查看控制台内的指令。\n确定？"), _T("警告"), MB_OKCANCEL | MB_ICONWARNING);
					if (mbret == IDCANCEL) {
						clearLine();
						printf("用户取消操作\n\n");
						goto cancel;
					}
					system(qcmd.c_str());
					break;
				}
				else if (mbret == IDCANCEL) {
					printf("用户取消操作\n");
					goto cancel;
				}
				else {
					throw "Error: MessageBox return wrong, on module 'bcdboot'.";
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
			string from, to, qcmd;
			cout << "从：";
			from = SelectFolder();
			cout << from << endl;
			if (from == "CANCEL") { printf("用户取消操作\n\n"); goto cancel; }
			cout << "到：";
			to = SelectFolder();
			cout << to << endl;
			if (to == "CANCEL") { printf("用户取消操作\n\n"); goto cancel; }
			while (1) {
				csi();
				int mbret = MessageBox(GetConsoleWindow(), _T("请选择：复制所有[是] 只复制目录结构[否] 取消？"), _T("选择"), MB_YESNOCANCEL);
				if (mbret == IDYES) {
					cout << "复制所有。" << endl;
					string qcmd = "xcopy \"" + from + "\" \"" + to + "\" /E /C /F /H";
					//cout << "> " << qcmd << endl;
					int mbret = MessageBox(GetConsoleWindow(), _T("请查看控制台内的信息。\n确定？"), _T("警告"), MB_OKCANCEL | MB_ICONWARNING);
					if (mbret == IDCANCEL) {
						clearLine();
						printf("用户取消操作\n\n");
						goto cancel;
					}
					system(qcmd.c_str());
					break;
				}
				else if (mbret == IDNO) {
					cout << "仅复制目录结构。" << endl;
					string qcmd = "xcopy \"" + from + "\" \"" + to + "\" /E /C /F /H /T";
					//cout << "> " << qcmd << endl;
					int mbret = MessageBox(GetConsoleWindow(), _T("请查看控制台内的信息。\n确定？"), _T("警告"), MB_OKCANCEL | MB_ICONWARNING);
					if (mbret == IDCANCEL) {
						clearLine();
						printf("用户取消操作\n\n");
						goto cancel;
					}
					system(qcmd.c_str());
					break;
				}
				else if (mbret == IDCANCEL) {
					printf("用户取消操作\n");
					goto cancel;
				}
				else {
					throw "Error: MessageBox return wrong, on module 'copys'.";
				}
			}
		}
		else if (inp == "explorer") {
			puts("即将打开内置小型文件资源管理器。\n如果想打开一个文件，请右键文件选择打开。");
			LittleExplorer();
		}
		else {
			//printf("命令无效\n请键入 \"help\" 或参考用户手册来获取更多信息\n"); 用户手册未更新
			printf("命令无效\n请键入 \"help\" 来获取更多信息\n");
		}
		printEndl(0);
		//cin.ignore(); //让 cin 忽略多余换行
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
