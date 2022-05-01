#include <cstdio>
#include <iostream>
#include <io.h>
#include <cstring>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <windows.h>
#include "power_command.hpp"
#define normal_version "10.4"
#define inside_version "22.04131"
#define compile_version "87ndz9"
#define channel "R (Release)"
using namespace std;
string __STR_WIM_PATH = "\\sources\\install.wim";
string __STR_ESD_PATH = "\\sources\\install.esd";
string wepath;

void FindWimEsd() {
	for(char i = 'C'; i <= 'Z'; i++) {
		char diskpath[3];
		diskpath[0] = i;
		diskpath[1] = ':';
		diskpath[2] = '\0';
		string qpath;
		qpath = diskpath + __STR_WIM_PATH;
//		cout << "Ѱ���ļ� �� " << qpath << endl;
		if(_access(qpath.c_str(), 0) != -1) {
			wepath = qpath;
			cout << "��Ѱ�ҵ� WIM �ļ� �� " << wepath << endl;
			return;
		}
		qpath = diskpath + __STR_ESD_PATH;
//		cout << "Ѱ���ļ� �� " << qpath << endl;
		if(_access(qpath.c_str(), 0) != -1) {
			wepath = qpath;
			cout << "��Ѱ�ҵ� ESD �ļ� �� " << wepath << endl;
			return;
		}
	}
	color(12);
	ding();
	printf("���棺û��Ѱ�ҵ� WIM/ESD �ļ��������������\n");
	printf("�����ͨ������ \"wepath\" ���ֶ�ָ��·��\n");
	wepath = "WIM/ESD_FILE_NOT_FOUND";
} 

inline void version() {
	printf("PowerCode Studio WinPE Helper\n");
	printf("�汾����: %s\n", normal_version);
	printf("�ڲ��汾: %s\n", inside_version);
	printf("�����汾: %s\n", compile_version);
	printf("ͨ������: %s\n", channel);
	printf("(c) PowerCode Studio & CodeZhangBorui, All right reserved.\n");
}

inline void about() {
	printf("PowerCode Studio WinPE Helper\n");
	printf("���� C++11 ������");
	printf("���ߣ�CodeZhangBorui\n");
	printf("��ϵ��ʽ��[Bվ]PowerCodeStudio [Github]CodeZhangBorui\n");
	color(13);
	printf("Enjoy Coding Life!\n");
	color(7);
}

int main() {
	system("title WinPE Helper");
	color(15);
	printf("PowerCode Studio WinPE Helper [�汾 %s]\n", normal_version);
	printf("(c) PowerCode Studio & CodeZhangBorui, All right reserved.\n");
	printEndl(0);
	FindWimEsd();
	printEndl(0);
	
	string inp;
	while(1) {
		cancel:; 
		color(9);
		csi();
		printf("PEHelper > ");
		color(14);
		getline(cin, inp);
		color(7);
		transform(inp.begin(), inp.end(), inp.begin(), ::tolower);
		       if(inp == "") goto cancel;
		  else if(inp == "exit") return 0;
		  else if(inp == "help") {
			printf("===== WinPE Helper ���� =====\n");
			printf("\n  ϵͳ��\n");
			printf("HELP       ��ȡ WinPE Helper ����\n");
			printf("VER        ��ʾ WinPE Helper �汾\n");
			printf("ABOUT      ���� WinPE Helper\n");
			printf("EXIT       �˳� WinPE Helper\n");
			printf("\n  ϵͳ��װ��\n");
			printf("WEPATH     ���²��һ��ֶ�ָ�� WIM/ESD �ļ�λ��\n");
			printf("WEINFO     ��ȡ WIM/ESD ������Ϣ\n");
			printf("SYSINSTALL ʹ�� Dism ��װϵͳ\n");
			printf("BCDBOOT    ����������\n");
			printf("\n  �����\n");
			printf("NOTEPAD    �򿪼��±�\n");
			printf("REGEDIT    ��ע���༭��\n");
			printf("CMD        ���µ� CMD ����\n");
			printf("SETUP      �� WindowsPE �Դ� GUI ϵͳ��װ\n");
			printf("\n  ��ɫ���ܣ�\n");
			printf("COPYS      ����һ���ļ��м������ļ����ڵ������ļ�\n");
			printEndl(0);
			printf("��ʾ���������⹦����ʾ����ʱ���� C ��ȡ��\n");
			
		} else if(inp == "ver") {
			version();
		
		} else if(inp == "about") {
			about();
		
		} else if(inp == "wepath") {
			cout << "��ǰ WIM/ESD �ļ� �� " << wepath << endl;
			while(1) {
				csi(); 
				printf("��ѡ���ֶ�ָ����·��[w] �Զ�����ɨ��[s] ȡ��[c]��");
				char mode = getchar();
				if(mode == 'w' || mode == 'W') {
					printf("��������·����");
					cin >> wepath;
					break;
				} else if(mode == 's' || mode == 'S') {
					FindWimEsd();
					break;
				} else if(mode == 'c' || mode == 'C') {
					printf("�û�ȡ������\n");
					goto cancel;
				} else {
					printf("'%c' ����һ����Ч��ѡ�", mode);
				}
			}
			
		} else if(inp == "weinfo") {
			string qcmd = "dism /Get-WimInfo /WimFile:" + wepath;
			system(qcmd.c_str());
			
		} else if(inp == "sysinstall") {
			string index, applydir;
			cout << "ӳ���ļ�λ��: " << wepath << endl;
			printf("����: ");
			cin >> index;
			if(index == "c" || index == "C") {printf("�û�ȡ������\n\n");goto cancel;}
			printf("Ŀ��Ӧ��Ŀ¼: ");
			cin >> applydir;
			if(applydir == "c" || applydir == "C") {printf("�û�ȡ������\n\n");goto cancel;}
			string qcmd = "dism /Apply-Image /ImageFile:" + wepath + " /Index:" + index + " /ApplyDir:" + applydir;
			cout << "> " << qcmd << endl;
			printf("ȷ����(Y/N) "); csi(); char yn = getchar(); if(yn == 'n' || yn == 'N') {printf("�û�ȡ������\n\n");goto cancel;} printEndl(0);
			system(qcmd.c_str());
		
		} else if(inp == "bcdboot") {
			while(1) {
				csi();
				printf("��ѡ��ʹ��UEFI����[u] ʹ�ô�ͳ����[l] ȡ��[c]��");
				char mode = getchar();
				if(mode == 'u' || mode == 'U') {
					printf("������ Windows ϵͳĿ¼·����");
					string winpath, uefiDisk, qcmd;
					cin >> winpath;
					printf("������ EFI ϵͳ������ESP���̷�����ʽΪ X:����");
					cin >> uefiDisk;
					qcmd = "bcdboot " + winpath + " /s " + uefiDisk + " /f UEFI";
					cout << "> " << qcmd << endl;
					printf("ȷ����(Y/N) "); csi(); char yn = getchar(); if(yn == 'n' || yn == 'N') {printf("�û�ȡ������\n\n");goto cancel;} printEndl(0);
					system(qcmd.c_str());
					break;
				} else if(mode == 'l' || mode == 'L') {
					printf("������ Windows ϵͳĿ¼·����");
					string winpath, sysDisk, qcmd;
					cin >> winpath;
					printf("������ Windows ϵͳ���ڷ����̷�����ʽΪ X:����");
					cin >> sysDisk;
					qcmd = "bcdboot " + winpath + " /s " + sysDisk + " /f BIOS";
					cout << "> " << qcmd << endl;
					printf("ȷ����(Y/N) "); csi(); char yn = getchar(); if(yn == 'n' || yn == 'N') {printf("�û�ȡ������\n\n");goto cancel;} printEndl(0);
					system(qcmd.c_str());
					break;
				} else if(mode == 'c' || mode == 'C') {
					printf("�û�ȡ������\n");
					goto cancel;
				} else {
					printf("'%c' ����һ����Ч��ѡ�", mode);
				}
			}
			
			
			

		} else if(inp == "notepad") {
			system("start notepad");
		
		} else if(inp == "regedit") {
			system("start regedit");
		
		} else if(inp == "cmd") {
			system("start cmd");
			
		} else if(inp == "setup") {
			system("start setup");
		
		} else if(inp == "copys") {
			printf("COPYS ʵ�ù��� [�汾 1.0.22.04032]\n");
//			printf("��ע�⣺���·���к��пո��뽫����·��ʹ��Ӣ������������\n");
			string from, to, qcmd;
			cout << "�ӣ�";
			getline(cin, from);
			if(from == "c" || from == "C") {printf("�û�ȡ������\n\n");goto cancel;}
			cout << "����";
			getline(cin, to);
			if(to == "c" || to == "C") {printf("�û�ȡ������\n\n");goto cancel;}
			while(1) {
				csi(); 
				printf("��ѡ�񣺸�������[a] ֻ����Ŀ¼�ṹ[t] ȡ��[c]��");
				char mode = getchar();
				if(mode == 'a' || mode == 'A') {
					string qcmd = "xcopy \"" + from + "\" \""  + to + "\" /E /C /F /H";
//					cout << "> " << qcmd << endl;
					cout << "ȷ����"; csi(); char yn = getchar(); if(yn == 'n' || yn == 'N') {printf("�û�ȡ������\n\n");goto cancel;} printEndl(0);
					system(qcmd.c_str());
					break;
				} else if(mode == 't' || mode == 'T') {
					string qcmd = "xcopy \"" + from + "\" \"" + to + "\" /E /C /F /H /T";
//					cout << "> " << qcmd << endl;
					cout << "ȷ����"; csi(); char yn = getchar(); if(yn == 'n' || yn == 'N') {printf("�û�ȡ������\n\n");goto cancel;} printEndl(0);
					system(qcmd.c_str());
					break;
				} else if(mode == 'c' || mode == 'C') {
					printf("�û�ȡ������\n");
					goto cancel;
				} else {
					printf("'%c' ����һ����Ч��ѡ�", mode);
				}
			}
		} else {
			printf("������Ч\n����� \"help\" ��ο��û��ֲ�����ȡ������Ϣ\n");
		}
		printEndl(0);
	}
}
