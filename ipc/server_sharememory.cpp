/* internal process communication*/
// share memeory
// CreateFileMapping，创建命名的内存映射文件对象
// MapViewOfFile，将内存空间映射到地址空间
// OpenFileMapping，获取已命名的对象句柄

#include <windows.h>
#include <stdio.h>

#define BUF_SIZE 4096

int main(int argc, char* argv[])
{
	// 定义共享数据
	char pszBuffer[] = "Shared memory";
	
	// 创建
	do 
	{	
		HANDLE hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, BUF_SIZE, L"ShareMemory");
		if (hMapFile != NULL && GetLastError() == ERROR_ALREADY_EXISTS)
		{
			// 重复
			printf("Create file mapping error.\n");
			CloseHandle(hMapFile);
			hMapFile = NULL;
			break;
		}

		// 映射
		LPVOID lpBase = MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, BUF_SIZE);
		if (lpBase == NULL)
		{
			// 失败
			printf("Map view of file error.\n");
			CloseHandle(hMapFile);
			hMapFile = NULL;
			break;
		}

		// 拷贝
		strcpy((char*)lpBase, pszBuffer);

		// 线程挂起20s
		printf("Sleep 20s.\n");
		Sleep(20000);

		// 移除
		BOOL bRet = UnmapViewOfFile(lpBase);
		if (!bRet)
		{
			// 失败
			printf("Unmap view of file error.\n");
		}

		CloseHandle(hMapFile);
	} while (false);

	return 0;
}
