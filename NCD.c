#include <windows.h>
#include <winsock2.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <stdlib.h>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "iphlpapi.lib")

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

void showActiveTCPConnections()
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

int main()
{
    showActiveTCPConnections();
    return 0;
}
