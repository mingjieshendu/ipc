/* internal process communication*/
// pipe
// WaitNamedPipe，等待超时或者Server进程准备好连接（ConnectNamedPipe）
// CreateFile，打开命名管道

#include <Windows.h>
#include <stdio.h>

#define BUF_SIZE 4096
#define EXAMP_PIPE L"\\\\.\\pipe\\ReadPipe"

int main(int argc, char* argv[])
{
	// 缓冲数据
	char pszBuffer[BUF_SIZE] = { 0 };
	do
	{
		// 等待
		BOOL bRet = WaitNamedPipe(EXAMP_PIPE, NMPWAIT_USE_DEFAULT_WAIT);
		if (!bRet)
		{
			printf("Wait named pipe error.\n");
			break;
		}

		// 打开
		HANDLE hPipe = CreateFile(EXAMP_PIPE, GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
		if (hPipe == INVALID_HANDLE_VALUE)
		{
			printf("Create file error.\n");
			break;
		}

		// 接收数据
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

		// 发送数据
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
