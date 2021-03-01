/* internal process communication*/
// pipe
// CreateNamedPipe�����������ܵ�ʵ��
// ConnectNamedPipe��Server���̵ȴ�Client�������������ܵ�ʵ��
// ReadFile����ȡ�ͻ�������
// WriteFile�����Ϳͻ�������
// DisconnectNamedPipe���Ͽ�Server������Client���̵������ܵ�ʵ��������

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
		// ����
		HANDLE hPipe = CreateNamedPipe(EXAMP_PIPE, PIPE_ACCESS_DUPLEX, 
			PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
			PIPE_UNLIMITED_INSTANCES, BUF_SIZE, BUF_SIZE, 0, NULL);
		if (hPipe == INVALID_HANDLE_VALUE)
		{
			printf("Create name pipe error.\n");
			break;
		}

		// �ȴ�����
		BOOL bRet = ConnectNamedPipe(hPipe, NULL);
		if (!bRet)
		{
			printf("Connect named pipe error.\n");
			CloseHandle(hPipe);
			break;
		}

		// ��������
		DWORD dwNum = 0;
		scanf("%s", pszBuffer);
		bRet = WriteFile(hPipe, pszBuffer, strlen(pszBuffer), &dwNum, NULL);
		if (!bRet)
		{
			printf("Write file error.\n");
		}

		// ��������
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

		// �Ͽ�����
		bRet = DisconnectNamedPipe(hPipe);
		if (!bRet)
		{
			printf("Disconnect named pipe error.\n");
		}

		CloseHandle(hPipe);
	} while (false);

	return 0;
}
