/* internal process communication*/
// share memeory

#include <windows.h>
#include <stdio.h>

#define BUF_SIZE 4096

int main(int argc, char* argv[])
{	
	// 定义共享数据
	char pszBuffer[BUF_SIZE] = { 0 };

	do 
	{	
		// 打开
		HANDLE hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, NULL, L"ShareMemory");
		if (hMapFile == NULL)
		{
			// 失败，不存在
			printf("Open file mapping error.\n");
			break;
		}

		// 映射
		LPVOID lpBase = MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);
		if (lpBase == NULL)
		{
			// 失败
			printf("Map view of file error.\n");
			CloseHandle(hMapFile);
			hMapFile = NULL;
			break;
		}

		// 拷贝
		strcpy(pszBuffer, (char*)lpBase);
		printf("Get share memory: %s\n", pszBuffer);

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
