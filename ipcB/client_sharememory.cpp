/* internal process communication*/
// share memeory

#include <windows.h>
#include <stdio.h>

#define BUF_SIZE 4096

int main(int argc, char* argv[])
{	
	// ���干������
	char pszBuffer[BUF_SIZE] = { 0 };

	do 
	{	
		// ��
		HANDLE hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, NULL, L"ShareMemory");
		if (hMapFile == NULL)
		{
			// ʧ�ܣ�������
			printf("Open file mapping error.\n");
			break;
		}

		// ӳ��
		LPVOID lpBase = MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);
		if (lpBase == NULL)
		{
			// ʧ��
			printf("Map view of file error.\n");
			CloseHandle(hMapFile);
			hMapFile = NULL;
			break;
		}

		// ����
		strcpy(pszBuffer, (char*)lpBase);
		printf("Get share memory: %s\n", pszBuffer);

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
