/* internal process communication*/
// pipe
// CreateNamedPipe，创建命名管道实例
// ConnectNamedPipe，Server进程等待Client进程连接命名管道实例
// ReadFile，读取客户端数据
// WriteFile，发送客户端数据
// DisconnectNamedPipe，断开Server进程与Client进程的命名管道实例的连接

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
		// 创建
		HANDLE hPipe = CreateNamedPipe(EXAMP_PIPE, PIPE_ACCESS_DUPLEX, 
			PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
			PIPE_UNLIMITED_INSTANCES, BUF_SIZE, BUF_SIZE, 0, NULL);
		if (hPipe == INVALID_HANDLE_VALUE)
		{
			printf("Create name pipe error.\n");
			break;
		}

		// 等待连接
		BOOL bRet = ConnectNamedPipe(hPipe, NULL);
		if (!bRet)
		{
			printf("Connect named pipe error.\n");
			CloseHandle(hPipe);
			break;
		}

		// 发送数据
		DWORD dwNum = 0;
		scanf("%s", pszBuffer);
		bRet = WriteFile(hPipe, pszBuffer, strlen(pszBuffer), &dwNum, NULL);
		if (!bRet)
		{
			printf("Write file error.\n");
		}

		// 接收数据
		memset(pszBuffer, 0, BUF_SIZE);
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

		// 断开连接
		bRet = DisconnectNamedPipe(hPipe);
		if (!bRet)
		{
			printf("Disconnect named pipe error.\n");
		}

		CloseHandle(hPipe);
	} while (false);

	return 0;
}
