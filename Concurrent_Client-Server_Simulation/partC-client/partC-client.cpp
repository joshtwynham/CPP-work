#undef UNICODE

// Turn off warnings for using sprintf - which is unsafe, as it states, but portable
#define _CRT_SECURE_NO_WARNINGS 1

// Only keep the main windows functions from windows.h:
#define WIN32_LEAN_AND_MEAN
// Use 4 byte IP addresses - old mode
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include "DoNotChangeThese.h"

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

// Pick a port
#define DEFAULT_PORT 27015

// And choose a size for the buffer for data - make it big enough for any input
#define DEFAULT_BUFLEN 512

struct DataForThread
{
	SOCKET ClientSocket;
	int iConnectionNumber;
};

struct DataClientToServer
{
	int procID;
	int resource7Count;
	int resource8Count;
	int resource9Count;
	int resource10Count;
	int resource11Count;
	int resource12Count;
};
union WrapperDataClientToServer
{
	DataClientToServer a;
	char b[sizeof(DataClientToServer)];
};
struct DataServerToClient
{
	int resource7Count;
	int resource8Count;
	int resource9Count;
	int resource10Count;
	int resource11Count;
	int resource12Count;
};
union WrapperDataServerToClient
{
	DataServerToClient a;
	char b[sizeof(DataServerToClient)];
};

HWND resourceAccess = FindWindow("resourceClass", NULL);
HWND threadProgress = FindWindow("threadClass", NULL);

struct MyDataStructure
{
	int numberOfProcesses;

	DWORD resource7Count;
	DWORD resource8Count;
	DWORD resource9Count;
	DWORD resource10Count;
	DWORD resource11Count;
	DWORD resource12Count;
};

HANDLE hMapFile = CreateFileMapping(
	INVALID_HANDLE_VALUE,    // use paging file
	NULL,                    // default security
	PAGE_READWRITE,          // read/write access
	0, sizeof(MyDataStructure), // max size high,low DWORDs
	"Local\\MyFileMappingObject"); // name of mapping object

volatile MyDataStructure * pMyData = (MyDataStructure *)MapViewOfFile(
	hMapFile,   // handle to map object
	FILE_MAP_ALL_ACCESS, // read/write permission
	0,
	0,
	sizeof(MyDataStructure));

HANDLE ClientMutex;
HANDLE ClientMutex2;

void TestCase1()
{
	StartingFunction(1); // Do not remove - for testing purposes

	InterlockedIncrement(&pMyData->resource7Count);

	switch (WaitForSingleObject(ClientMutex, INFINITE))
		// handle to mutex, timeout interval
	{
		// The thread got ownership of the mutex
	case WAIT_OBJECT_0:
		UseResource(7);	// Do not remove - for testing purposes

		if (!ReleaseMutex(ClientMutex))
		{ 
			printf("Could not release mutex");
		}

		break;
	}

	EndingFunction(1); // Do not remove - for testing purposes
}

void TestCase2()
{
	StartingFunction(2); // Do not remove - for testing purposes

	InterlockedIncrement(&pMyData->resource8Count);

	switch (WaitForSingleObject(ClientMutex, INFINITE))
		// handle to mutex, timeout interval
	{
		// The thread got ownership of the mutex
	case WAIT_OBJECT_0:
		UseResource(8);	// Do not remove - for testing purposes

		if (!ReleaseMutex(ClientMutex))
		{
			printf("Could not release mutex");
		}

		break;
	}

	EndingFunction(2); // Do not remove - for testing purposes
}

void TestCase3()
{
	StartingFunction(3); // Do not remove - for testing purposes

	InterlockedIncrement(&pMyData->resource9Count);

	switch (WaitForSingleObject(ClientMutex, INFINITE))
		// handle to mutex, timeout interval
	{
		// The thread got ownership of the mutex
	case WAIT_OBJECT_0:
		UseResource(9);	// Do not remove - for testing purposes

		if (!ReleaseMutex(ClientMutex))
		{
			printf("Could not release mutex");
		}

		break;
	}

	EndingFunction(3); // Do not remove - for testing purposes
}

void TestCase4()
{
	StartingFunction(4); // Do not remove - for testing purposes

	InterlockedIncrement(&pMyData->resource10Count);

	switch (WaitForSingleObject(ClientMutex, INFINITE))
		// handle to mutex, timeout interval
	{
		// The thread got ownership of the mutex
	case WAIT_OBJECT_0:
		UseResource(10);	// Do not remove - for testing purposes

		if (!ReleaseMutex(ClientMutex))
		{
			printf("Could not release mutex");
		}

		break;
	}

	EndingFunction(4); // Do not remove - for testing purposes
}

void TestCase5()
{
	StartingFunction(5); // Do not remove - for testing purposes

	InterlockedIncrement(&pMyData->resource11Count);

	switch (WaitForSingleObject(ClientMutex, INFINITE))
		// handle to mutex, timeout interval
	{
		// The thread got ownership of the mutex
	case WAIT_OBJECT_0:
		UseResource(11);	// Do not remove - for testing purposes

		if (!ReleaseMutex(ClientMutex))
		{
			printf("Could not release mutex");
		}

		break;
	}

	EndingFunction(5); // Do not remove - for testing purposes
}

void TestCase6()
{
	StartingFunction(6); // Do not remove - for testing purposes

	InterlockedIncrement(&pMyData->resource7Count);
	InterlockedIncrement(&pMyData->resource8Count);

	switch (WaitForSingleObject(ClientMutex, INFINITE))
		// handle to mutex, timeout interval
	{
		// The thread got ownership of the mutex
	case WAIT_OBJECT_0:
		UseTwoResources(7, 8);	// Do not remove - for testing purposes

		if (!ReleaseMutex(ClientMutex))
		{
			printf("Could not release mutex");
		}

		break;
	}

	EndingFunction(6); // Do not remove - for testing purposes
}

void TestCase7()
{
	StartingFunction(7); // Do not remove - for testing purposes

	InterlockedIncrement(&pMyData->resource8Count);
	InterlockedIncrement(&pMyData->resource9Count);

	switch (WaitForSingleObject(ClientMutex, INFINITE))
		// handle to mutex, timeout interval
	{
		// The thread got ownership of the mutex
	case WAIT_OBJECT_0:
		UseTwoResources(8, 9);	// Do not remove - for testing purposes

		if (!ReleaseMutex(ClientMutex))
		{
			printf("Could not release mutex");
		}

		break;
	}

	EndingFunction(7); // Do not remove - for testing purposes
}

void TestCase8()
{
	StartingFunction(8); // Do not remove - for testing purposes

	InterlockedIncrement(&pMyData->resource9Count);

	switch (WaitForSingleObject(ClientMutex, INFINITE))
		// handle to mutex, timeout interval
	{
		// The thread got ownership of the mutex
	case WAIT_OBJECT_0:
		int iTemp = StartToUseResource(9); // Do not remove - for testing purposes
		// TODO - add extra code to increment your value for resources 5 and 6
		pMyData->resource11Count++;
		pMyData->resource12Count++;
		UseTwoResources(11, 12);  // Do not remove - for testing purposes

		FinishUsingResource(9, iTemp); // Do not remove - for testing purposes

		if (!ReleaseMutex(ClientMutex))
		{
			printf("Could not release mutex");
		}

		break;
	}

	

	EndingFunction(8); // Do not remove - for testing purposes
}

void TestCase9()
{
	StartingFunction(9); // Do not remove - for testing purposes

	pMyData->resource10Count++;

	switch (WaitForSingleObject(ClientMutex, INFINITE))
		// handle to mutex, timeout interval
	{
		// The thread got ownership of the mutex
	case WAIT_OBJECT_0:
		int iTemp = StartToUseResource(10); // Do not remove - for testing purposes
		TestCase6(); // Do not remove - for testing purposes
		FinishUsingResource(10, iTemp); // Do not remove - for testing purposes

		if (!ReleaseMutex(ClientMutex))
		{
			printf("Could not release mutex");
		}

		break;
	}
	
	

	EndingFunction(9); // Do not remove - for testing purposes
}

void TestCase10()
{
	StartingFunction(10); // Do not remove - for testing purposes

	pMyData->resource7Count++;

	switch (WaitForSingleObject(ClientMutex, INFINITE))
		// handle to mutex, timeout interval
	{
		// The thread got ownership of the mutex
	case WAIT_OBJECT_0:
		int iTemp = StartToUseResource(7); // Do not remove - for testing purposes
		TestCase7(); // Do not remove - for testing purposes

		FinishUsingResource(7, iTemp); // Do not remove - for testing purposes

		if (!ReleaseMutex(ClientMutex))
		{
			printf("Could not release mutex");
		}

		break;
	}

	

	EndingFunction(10); // Do not remove - for testing purposes
}

void TestCase11()
{
	StartingFunction(11); // Do not remove - for testing purposes

	pMyData->resource9Count++;

	switch (WaitForSingleObject(ClientMutex, INFINITE))
		// handle to mutex, timeout interval
	{
		// The thread got ownership of the mutex
	case WAIT_OBJECT_0:
		int iTemp3 = StartToUseResource(9); // Do not remove - for testing purposes
		pMyData->resource10Count++;
		int iTemp4 = StartToUseResource(10); // Do not remove - for testing purposes
		pMyData->resource11Count++;
		pMyData->resource12Count++;
		UseTwoResources(11, 12);  // Do not remove - for testing purposes

		FinishUsingResource(9, iTemp3); // Do not remove - for testing purposes
		FinishUsingResource(10, iTemp4); // Do not remove - for testing purposes

		if (!ReleaseMutex(ClientMutex))
		{
			printf("Could not release mutex");
		}

		break;
	}

	

	EndingFunction(11); // Do not remove - for testing purposes
}

void TestCase12()
{
	StartingFunction(12); // Do not remove - for testing purposes

	pMyData->resource11Count++;

	switch (WaitForSingleObject(ClientMutex, INFINITE))
		// handle to mutex, timeout interval
	{
		// The thread got ownership of the mutex
	case WAIT_OBJECT_0:
		int iTemp = StartToUseResource(11); // Do not remove - for testing purposes
		TestCase3(); // Do not remove - for testing purposes

		FinishUsingResource(11, iTemp); // Do not remove - for testing purposes

		if (!ReleaseMutex(ClientMutex))
		{
			printf("Could not release mutex");
		}

		break;
	}

	

	EndingFunction(12); // Do not remove - for testing purposes
}

void TestCase13()
{
	StartingFunction(13); // Do not remove - for testing purposes

	TestCase1(); // Do not remove - for testing purposes
	TestCase7(); // Do not remove - for testing purposes
	TestCase8(); // Do not remove - for testing purposes

	EndingFunction(13); // Do not remove - for testing purposes
}

void TestCase14()
{
	StartingFunction(14); // Do not remove - for testing purposes

	pMyData->resource10Count++;

	switch (WaitForSingleObject(ClientMutex, INFINITE))
		// handle to mutex, timeout interval
	{
		// The thread got ownership of the mutex
	case WAIT_OBJECT_0:
		int iTemp4 = StartToUseResource(10); // Do not remove - for testing purposes
		pMyData->resource11Count++;
		int iTemp5 = StartToUseResource(11); // Do not remove - for testing purposes
		pMyData->resource12Count++;
		int iTemp6 = StartToUseResource(12); // Do not remove - for testing purposes

		FinishUsingResource(10, iTemp4); // Do not remove - for testing purposes
		FinishUsingResource(11, iTemp5); // Do not remove - for testing purposes
		FinishUsingResource(12, iTemp6); // Do not remove - for testing purposes

		if (!ReleaseMutex(ClientMutex))
		{
			printf("Could not release mutex");
		}

		break;
	}

	

	EndingFunction(14); // Do not remove - for testing purposes
}

void TestCase15()
{
	StartingFunction(15); // Do not remove - for testing purposes

	pMyData->resource10Count++;

	switch (WaitForSingleObject(ClientMutex, INFINITE))
		// handle to mutex, timeout interval
	{
		// The thread got ownership of the mutex
	case WAIT_OBJECT_0:
		int iTemp4 = StartToUseResource(10); // Do not remove - for testing purposes
		pMyData->resource11Count++;
		int iTemp5 = StartToUseResource(11); // Do not remove - for testing purposes
		pMyData->resource12Count++;
		int iTemp6 = StartToUseResource(12); // Do not remove - for testing purposes

		TestCase1(); // Do not remove - for testing purposes
		TestCase7(); // Do not remove - for testing purposes
		TestCase6(); // Do not remove - for testing purposes

		FinishUsingResource(4, iTemp4); // Do not remove - for testing purposes
		FinishUsingResource(5, iTemp5); // Do not remove - for testing purposes
		FinishUsingResource(6, iTemp6); // Do not remove - for testing purposes

		if (!ReleaseMutex(ClientMutex))
		{
			printf("Could not release mutex");
		}

		break;
	}

	

	EndingFunction(15); // Do not remove - for testing purposes
}

void InitialCode(int iDelay)
{
	StartingFunction(-1); // Do not remove - for testing purposes
	SimulateProcessingTime(iDelay);
	EndingFunction(-1); // Do not remove - for testing purposes
}

void RemainderCode(int iDelay)
{
	StartingFunction(-2); // Do not remove - for testing purposes
	SimulateProcessingTime(iDelay); // Do not remove - for testing purposes
	EndingFunction(-2); // Do not remove - for testing purposes
}

void SendDataToServer(int iProcessOrThreadID)
{
	StartingFunction(-3); // Do not remove - for testing purposes

	// Implement this to send the information to the server
	// You need to send a value to say which thread/process this is, along with the current values of all resource variables.
	SOCKET ConnectSocket = INVALID_SOCKET;

	int iResult;
	int recvbuflen = DEFAULT_BUFLEN;

	struct sockaddr_in serveraddress;
	serveraddress.sin_family = AF_INET;
	serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1"); // Local machine
	serveraddress.sin_port = htons(DEFAULT_PORT);

	// Create a SOCKET for connecting to server
	ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ConnectSocket == INVALID_SOCKET)
	{
		printf("ConnectSocket socket failed with error: %ld\n", WSAGetLastError());
		return;
	}

	// Connect to server.
	iResult = connect(ConnectSocket, (sockaddr*)&serveraddress, sizeof(serveraddress));
	if (iResult == SOCKET_ERROR)
	{
		printf("ConnectSocket connect failed with error: %ld\n", WSAGetLastError());
		closesocket(ConnectSocket);
		ConnectSocket = INVALID_SOCKET;
	}

	// New for handling a struct-based system.
	int iReceiveIndex = 0; // Index into struct that we are getting
	WrapperDataServerToClient dataReceived = { 0 }; // Used to hold the received message.Initialise the structure to 0s

	WrapperDataClientToServer message;
	message.a.procID = iProcessOrThreadID + 4;
	message.a.resource7Count = pMyData->resource7Count;
	message.a.resource8Count = pMyData->resource8Count;
	message.a.resource9Count = pMyData->resource9Count;
	message.a.resource10Count = pMyData->resource10Count;
	message.a.resource11Count = pMyData->resource11Count;
	message.a.resource12Count = pMyData->resource12Count;


	send(ConnectSocket, message.b, (int)sizeof(message), 0);

	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR)
	{
		printf("ConnectSocket shutdown failed with error: %d\n",
			WSAGetLastError());
		closesocket(ConnectSocket);
		return;
	}
	// cleanup
	closesocket(ConnectSocket);


	EndingFunction(-3); // Do not remove - for testing purposes
}


// Thread 1 should run this
DWORD WINAPI Procedure1(LPVOID lpParm)
{
	InitialCode(1000); // Do not remove - for testing purposes

	for (int i = 0; i < 100; i++) // Do not remove - for testing purposes
	{ // Do not remove - for testing purposes	
		TestCase1(); // Do not remove - for testing purposes
		RemainderCode(100); // Do not remove - for testing purposes
		TestCase6(); // Do not remove - for testing purposes
		RemainderCode(100); // Do not remove - for testing purposes
		TestCase11(); // Do not remove - for testing purposes
		RemainderCode(500); // Do not remove - for testing purposes
		SendDataToServer(1); // Do not remove - for testing purposes
	} // Do not remove - for testing purposes
	return 1;
}

// Thread 2 should run this
DWORD WINAPI Procedure2(LPVOID lpParm)
{
	InitialCode(1000); // Do not remove - for testing purposes

	for (int i = 0; i < 100; i++) // Do not remove - for testing purposes
	{ // Do not remove - for testing purposes
		TestCase2(); // Do not remove - for testing purposes
		RemainderCode(100); // Do not remove - for testing purposes
		TestCase7(); // Do not remove - for testing purposes
		RemainderCode(100); // Do not remove - for testing purposes
		TestCase12(); // Do not remove - for testing purposes
		RemainderCode(500); // Do not remove - for testing purposes
		SendDataToServer(2); // Do not remove - for testing purposes
	}
	return 1;
}

// Thread 3 should run this
DWORD WINAPI Procedure3(LPVOID lpParm)
{
	InitialCode(1000); // Do not remove - for testing purposes

	for (int i = 0; i < 100; i++) // Do not remove - for testing purposes
	{ // Do not remove - for testing purposes
		TestCase3(); // Do not remove - for testing purposes
		RemainderCode(100); // Do not remove - for testing purposes
		TestCase8(); // Do not remove - for testing purposes
		RemainderCode(100); // Do not remove - for testing purposes
		TestCase13(); // Do not remove - for testing purposes
		RemainderCode(500); // Do not remove - for testing purposes
		SendDataToServer(3); // Do not remove - for testing purposes
	} // Do not remove - for testing purposes
	return 1;
}

// Thread 4 should run this
DWORD WINAPI Procedure4(LPVOID lpParm)
{
	InitialCode(1000); // Do not remove - for testing purposes

	for (int i = 0; i < 100; i++) // Do not remove - for testing purposes
	{ // Do not remove - for testing purposes
		TestCase4(); // Do not remove - for testing purposes
		RemainderCode(100); // Do not remove - for testing purposes
		TestCase9(); // Do not remove - for testing purposes
		RemainderCode(100); // Do not remove - for testing purposes
		TestCase14(); // Do not remove - for testing purposes
		RemainderCode(500); // Do not remove - for testing purposes
		SendDataToServer(4); // Do not remove - for testing purposes
	} // Do not remove - for testing purposes
	return 1;
}

// Thread 5 should run this
DWORD WINAPI Procedure5(LPVOID lpParm)
{
	InitialCode(1000); // Do not remove - for testing purposes

	for (int i = 0; i < 100; i++) // Do not remove - for testing purposes
	{ // Do not remove - for testing purposes
		TestCase5(); // Do not remove - for testing purposes
		RemainderCode(100); // Do not remove - for testing purposes
		TestCase10(); // Do not remove - for testing purposes
		RemainderCode(100); // Do not remove - for testing purposes
		TestCase15(); // Do not remove - for testing purposes
		RemainderCode(500); // Do not remove - for testing purposes
		RemainderCode(500); // Do not remove - for testing purposes
		SendDataToServer(5); // Do not remove - for testing purposes
	} // Do not remove - for testing purposes
	return 1;
}

int main()
{

	

	WSADATA wsaData;
	// Initialize Winsock
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (hMapFile == NULL)
	{
		printf("Could not create file mapping object (%d).\n",
			GetLastError());
		return 1;
	}

	if (pMyData == NULL)
	{
		printf(TEXT("Could not map view of file (%d).\n"),
			GetLastError());
		CloseHandle(hMapFile);
		return 1;
	}


	// So that different processes run different procedures
	int processID = ++pMyData->numberOfProcesses;

	if (pMyData->numberOfProcesses < 5) 
	{

		ClientMutex = CreateMutex(
			NULL, // default security attributes
			FALSE, // initially not owned
			"ClientMutex");

		ClientMutex2 = CreateMutex(
			NULL,
			FALSE,
			"ClientMutex2");
		// Work out the filename of the exe for process
		char szMyFileName[1024];
		GetModuleFileName(NULL, szMyFileName, 1024);
		// We saw the create process before…
		STARTUPINFO info = { sizeof(info) }; // Input
		PROCESS_INFORMATION processInfo; // Output
		if (CreateProcess(szMyFileName, // Program
			"", // Command line
			NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL,
			&info, &processInfo))
		{ // Created - close handles to it.
			CloseHandle(processInfo.hProcess);
			CloseHandle(processInfo.hThread);
		}

		
	}
	else
	{
		ClientMutex = OpenMutex(
			MUTEX_ALL_ACCESS,            // request full access
			FALSE,                       // handle not inheritable
			TEXT("ClientMutex"));

		ClientMutex2 = OpenMutex(
			MUTEX_ALL_ACCESS,
			FALSE,
			TEXT("ClientMutex"));
	}

	switch (processID)
	{
	case 1:
		Procedure1(NULL);
		break;
	case 2:
		Procedure2(NULL);
		break;
	case 3:
		Procedure3(NULL);
		break;
	case 4:
		Procedure4(NULL);
		break;
	case 5:
		Procedure5(NULL);
		break;
	}

	printf("resource1Count = %d\nresource2Count = %d\nresource3Count = %d\nresource4Count = %d\nresource5Count = %d\nresource6Count = %d\n", pMyData->resource7Count, pMyData->resource8Count, pMyData->resource9Count, pMyData->resource10Count, pMyData->resource11Count, pMyData->resource12Count);

	do
	{
		printf("Press enter to finish.");
	} while (getchar() != '\n');

	ReleaseMutex(ClientMutex);

}