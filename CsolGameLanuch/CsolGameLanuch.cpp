// CsolGameLanuch.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>


char szMapData[100] = { 0, 0, 0, 0, 5, 0, 0, 0, 8, 0, 0, 0, 108, 97, 117, 110, 99, 104, \
101, 100, 1, 0, 0, 0, 49, 4, 0, 0, 0, 109, 111, 100, 101, 0, 0, 0, 0, 8, 0, 0, 0, 112, 97, \
115, 115, 112, 111, 114, 116, 0, 0, 0, 0, 6, 0, 0, 0, 114, 101, 103, 105, 111, 110, 1, 0, 0, 0, 54, 4, 0, 0, 0, 116, 121, 112, 101, 1, 0, 0, 0, 48, 0 };


char szRelData[15] = { 49, 54, 4, 0, 0, 0, 116, 121, 112, 101, 1, 0, 0, 0, 48 };

void CsolGameLaunch(int GameService, char* szGamePath)
{
	if (GameService > 5 || GameService <= 0 || szGamePath == NULL)
		return;

	if (GameService <= 3)
	{
		szMapData[67] = 52 + GameService;
	}
	else
	{
		szMapData[63] = 2;
		memcpy(szMapData + 67, szRelData, 15);
		szMapData[68] = 49 + GameService;
	}

	HANDLE hMapFile = CreateFileMappingA((HANDLE)-1, 0, 4, 0, 32768, "CSO.SharedDict");

	if (hMapFile == 0)
	{
		printf("CreateFileMappingA faild!\n");
		return;
	}
		

	char* lpMap = (char*)MapViewOfFile(hMapFile, 98307, 0, 0, 0);

	if (lpMap == 0)
	{
		printf("MapViewOfFile faild!\n");
		return;
	}


	for (size_t i = 0; i < 83; i++)
	{
		lpMap[i] = szMapData[i];
	}

	char szPath[MAX_PATH];

	GetCurrentDirectoryA(MAX_PATH, szPath);

	SetCurrentDirectoryA(szPath);
	
	strcat(szPath, "\\cstrike-online.exe");

	STARTUPINFOA si = {0};
	PROCESS_INFORMATION pi = {0};

	si.cb = sizeof(si);

	CreateProcessA(NULL, szPath, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);

	Sleep(5000);

	UnmapViewOfFile(lpMap);
	CloseHandle(hMapFile);
}


int main(int argc, char ** argv)
{
	int service = 0;
	SetConsoleTitleA("CsolGameLaunchTools\n");

	/*if (argc < 2)
	{
		printf("Game Service：1~5\n");
		printf("1.电信一区 2.电信二区.....\n");
		return 0;
	}

	service = atoi(argv[1]);*/

	printf("%d\n",service);
	CsolGameLaunch(4, "lala");

    return 0;
}

