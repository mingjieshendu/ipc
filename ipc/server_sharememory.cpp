/* internal process communication*/
// share memeory
// CreateFileMapping�������������ڴ�ӳ���ļ�����
// MapViewOfFile�����ڴ�ռ�ӳ�䵽��ַ�ռ�
// OpenFileMapping����ȡ�������Ķ�����

#include <windows.h>
#include <stdio.h>

#define BUF_SIZE 4096

int main(int argc, char* argv[])
{
	// ���干������
	char pszBuffer[] = "Shared memory";
	
	// ����
	do 
	{	
		HANDLE hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, BUF_SIZE, L"ShareMemory");
		if (hMapFile != NULL && GetLastError() == ERROR_ALREADY_EXISTS)
		{
			// �ظ�
			printf("Create file mapping error.\n");
			CloseHandle(hMapFile);
			hMapFile = NULL;
			break;
		}

		// ӳ��
		LPVOID lpBase = MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, BUF_SIZE);
		if (lpBase == NULL)
		{
			// ʧ��
			printf("Map view of file error.\n");
			CloseHandle(hMapFile);
			hMapFile = NULL;
			break;
		}

		// ����
		strcpy((char*)lpBase, pszBuffer);

		// �̹߳���20s
		printf("Sleep 20s.\n");
		Sleep(20000);

		// �Ƴ�
		BOOL bRet = UnmapViewOfFile(lpBase);
		if (!bRet)
		{
			// ʧ��
			printf("Unmap view of file error.\n");
		}

		CloseHandle(hMapFile);
	} while (false);

	return 0;
}
