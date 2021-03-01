/* internal process communication*/
// pipe
// WaitNamedPipe���ȴ���ʱ����Server����׼�������ӣ�ConnectNamedPipe��
// CreateFile���������ܵ�

#include <Windows.h>
#include <stdio.h>

#define BUF_SIZE 4096
#define EXAMP_PIPE L"\\\\.\\pipe\\ReadPipe"

int main(int argc, char* argv[])
{
	// ��������
	char pszBuffer[BUF_SIZE] = { 0 };
	do
	{
		// �ȴ�
		BOOL bRet = WaitNamedPipe(EXAMP_PIPE, NMPWAIT_USE_DEFAULT_WAIT);
		if (!bRet)
		{
			printf("Wait named pipe error.\n");
			break;
		}

		// ��
		HANDLE hPipe = CreateFile(EXAMP_PIPE, GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
		if (hPipe == INVALID_HANDLE_VALUE)
		{
			printf("Create file error.\n");
			break;
		}

		// ��������
		DWORD dwNum = 0;
		bRet = ReadFile(hPipe, pszBuffer, BUF_SIZE, &dwNum, NULL);
		if (bRet)
		{
			pszBuffer[dwNum] = '\0';
			printf("%s\n", pszBuffer);
		}
		else
		{
			printf("Read file error.\n");
		}

		// ��������
		memset(pszBuffer, 0, BUF_SIZE);
		scanf("%s", pszBuffer);
		bRet = WriteFile(hPipe, pszBuffer, strlen(pszBuffer), &dwNum, NULL);
		if (!bRet)
		{
			printf("Write file error.\n");
		}

		CloseHandle(hPipe);
	} while (false);

	return 0;
}
