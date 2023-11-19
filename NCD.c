#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#include <winsock2.h>
#include <iphlpapi.h>
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "iphlpapi.lib")
#else
#include <string.h>
#endif

#ifdef _WIN32
void printError(char *functionName)
{
    // Retrieve the system error message for the last-error code
    LPVOID lpMsgBuf;
    DWORD dw = GetLastError();

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&lpMsgBuf,
        0, NULL);

    printf("%s failed with error %d: %s", functionName, dw, lpMsgBuf);
    LocalFree(lpMsgBuf);
}

void showActiveTCPConnectionsWindows()
{
    // Declare and initialize variables
    PMIB_TCPTABLE pTcpTable;
    DWORD dwSize = 0;
    DWORD dwRetVal = 0;

    pTcpTable = (MIB_TCPTABLE *)malloc(sizeof(MIB_TCPTABLE));
    if (pTcpTable == NULL)
    {
        printf("Error allocating memory\n");
        return;
    }

    dwSize = sizeof(MIB_TCPTABLE);
    // Make an initial call to GetTcpTable to get the necessary size into dwSize
    if ((dwRetVal = GetTcpTable(pTcpTable, &dwSize, TRUE)) == ERROR_INSUFFICIENT_BUFFER)
    {
        free(pTcpTable);
        pTcpTable = (MIB_TCPTABLE *)malloc(dwSize);
        if (pTcpTable == NULL)
        {
            printf("Error allocating memory\n");
            return;
        }
    }

    // Make a second call to GetTcpTable to get the actual data
    if ((dwRetVal = GetTcpTable(pTcpTable, &dwSize, TRUE)) == NO_ERROR)
    {
        printf("Number of entries: %d\n", (int)pTcpTable->dwNumEntries);
        for (int i = 0; i < (int)pTcpTable->dwNumEntries; i++)
        {
            printf("\nTCP[%d] State: %ld - ", i, pTcpTable->table[i].dwState);
            printf("Local Addr: %s:%d - ",
                   inet_ntoa(*(struct in_addr *)&(pTcpTable->table[i].dwLocalAddr)),
                   ntohs((u_short)pTcpTable->table[i].dwLocalPort));
            printf("Remote Addr: %s:%d",
                   inet_ntoa(*(struct in_addr *)&(pTcpTable->table[i].dwRemoteAddr)),
                   ntohs((u_short)pTcpTable->table[i].dwRemotePort));
        }
    }
    else
    {
        printError("GetTcpTable");
    }

    if (pTcpTable != NULL)
    {
        free(pTcpTable);
        pTcpTable = NULL;
    }
}
#else
void showActiveTCPConnectionsLinux()
{
    // Declare and initialize variables
    FILE *tcpFile;
    char line[256];
    char localAddress[128], remAddress[128];
    int localPort, remPort, state;

    tcpFile = fopen("/proc/net/tcp", "r");
    if (tcpFile == NULL)
    {
        perror("Error opening file");
        return;
    }

    fgets(line, sizeof(line), tcpFile); // Skip first line

    printf("Local Address\t\tRemote Address\t\tState\n");
    while (fgets(line, sizeof(line), tcpFile) != NULL)
    {
        sscanf(line, "%*d: %64[0-9A-Fa-f]:%X %64[0-9A-Fa-f]:%X %X",
               localAddress, &localPort, remAddress, &remPort, &state);
        printf("%s:%d\t\t%s:%d\t\t%d\n", localAddress, localPort, remAddress, remPort, state);
    }

    fclose(tcpFile);
}
#endif

int main()
{
#ifdef _WIN32
    showActiveTCPConnectionsWindows();
#else
    showActiveTCPConnectionsLinux();
#endif
    return 0;
}