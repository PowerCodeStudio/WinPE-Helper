#include <iostream>
#include <cstdio>
#include <cstring>
#include <io.h>
#include <string>
#include <windows.h>
#include <shlobj.h>
#include <CommDlg.h>
#include <tchar.h>
#pragma once

inline bool fileExits(const char* name) {
    int acsResult = _access(name, 00);
    if (acsResult == 0) return true;
    else return false;
}

inline bool fileRead(const char* name) {
    int acsResult = _access(name, 04);
    if (acsResult == 0) return true;
    else return false;
}

inline bool fileWrite(const char* name) {
    int acsResult = _access(name, 06);
    if (acsResult == 0) return true;
    else return false;
}

std::string SelectFolder()
{
	BROWSEINFO  bi;
	bi.hwndOwner = GetConsoleWindow();
	bi.pidlRoot = CSIDL_DESKTOP;
	bi.pszDisplayName = NULL;
	bi.lpszTitle = NULL;
	bi.ulFlags = BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
	bi.lpfn = NULL;
	bi.iImage = 0;
	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
	if (pidl == NULL)
	{
		return "CANCEL";
	}
	TCHAR strFolder[MAX_PATH];
	SHGetPathFromIDList(pidl, strFolder);
	std::wstring wStr = strFolder;
	return std::string(wStr.begin(), wStr.end());
}

std::string SelectWimEsd() {
	TCHAR szBuffer[MAX_PATH] = { 0 };
	OPENFILENAME ofn = { 0 };
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = GetConsoleWindow();
	ofn.lpstrFilter = _T("WIM文件(*.wim)\0*.wim\0已解密的ESD文件(*.esd)\0*.esd\0所有文件(*.*)\0*.*\0");//要选择的文件后缀   
	ofn.lpstrInitialDir = _T("D:\\");
	ofn.lpstrFile = szBuffer; 
	ofn.nMaxFile = sizeof(szBuffer) / sizeof(*szBuffer);
	ofn.nFilterIndex = 0;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER;//标志如果是多选要加上OFN_ALLOWMULTISELECT  
	BOOL bSel = GetOpenFileName(&ofn);
	if (!bSel) return "CANCEL";
	std::wstring wStr = szBuffer;
	return std::string(wStr.begin(), wStr.end());
}

void LittleExplorer() {
	TCHAR szBuffer[MAX_PATH] = { 0 };
	OPENFILENAME ofn = { 0 };
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = GetConsoleWindow();
	ofn.lpstrFilter = _T("所有文件(*.*)\0*.*\0");//要选择的文件后缀   
	ofn.lpstrInitialDir = _T("C:\\");
	ofn.lpstrFile = szBuffer;
	ofn.nMaxFile = sizeof(szBuffer) / sizeof(*szBuffer);
	ofn.nFilterIndex = 0;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER | OFN_ALLOWMULTISELECT;
	BOOL bSel = GetOpenFileName(&ofn);
}