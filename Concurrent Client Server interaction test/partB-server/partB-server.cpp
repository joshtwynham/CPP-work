// Example client-server program
// As long as you understand what this program is doing, you should not need to worry about the details
// The aim is that you can copy-paste the code to do the connections and just worry about the details of what to send and receive rather than how to send and receive

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

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

// Pick a port
#define DEFAULT_PORT 27015

// And choose a size for the buffer for data - make it big enough for any input
#define DEFAULT_BUFLEN 512

#define NUM_RESOURCES 12
#define NUM_CLIENTS 10

HDC hdc1;
HDC hdc2;

volatile int threadValues[NUM_CLIENTS]; // Stores how many times each thread sends data to server
volatile int resourceValues[NUM_RESOURCES]; // Stores how many times each resource is accessed

HWND resourceAccess;
HWND threadProgress;

CRITICAL_SECTION threadVals;
CRITICAL_SECTION resourceVals;

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

LRESULT CALLBACK resourceProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		// Added for the painting
		PAINTSTRUCT ps;
		hdc1 = BeginPaint(hwnd, &ps);
		{
			int aiValuesToShow[NUM_RESOURCES];

			for (int i = 0; i < NUM_RESOURCES; i++)
				aiValuesToShow[i] = resourceValues[i];

			// Now work out how high to make each bar
			int iMax = -10000000; int iMin = 10000000;
			for (int i = 0; i < 10; i++)
			{
				if (aiValuesToShow[i] < iMin) iMin = aiValuesToShow[i];
				if (aiValuesToShow[i] > iMax) iMax = aiValuesToShow[i];
			}
			if (iMin < 0) iMin = 0;
			if (iMax < (iMin + 1)) iMax = iMin + 1;
			int iDiff = iMax - iMin;

			//printf( "t%d b%d l%d r%d\n",rc.top,rc.bottom,rc.left,rc.right );
			HBRUSH hbrush[6];
			hbrush[0] = CreateSolidBrush(RGB(255, 0, 0));
			hbrush[1] = CreateSolidBrush(RGB(255, 255, 0));
			hbrush[2] = CreateSolidBrush(RGB(0, 255, 0));
			hbrush[3] = CreateSolidBrush(RGB(0, 255, 255));
			hbrush[4] = CreateSolidBrush(RGB(0, 0, 255));
			hbrush[5] = CreateSolidBrush(RGB(255, 0, 255));
			RECT rc;
			GetClientRect(hwnd, &rc);
			RECT rect[NUM_RESOURCES];
			for (int i = 0; i < NUM_RESOURCES; i++)
				rect[i] = rc; // Copy original size
			for (int i = 1; i < NUM_RESOURCES; i++)
				rect[i - 1].right = rect[i].left = rc.right * i / NUM_RESOURCES;
			// Fix heights to be relative to total
			int iFullHeight = rc.bottom - rc.top;
			for (int i = 0; i < NUM_RESOURCES; i++)
				rect[i].top = rect[i].bottom - (iFullHeight * aiValuesToShow[i]) / iMax;
			for (int i = 0; i < NUM_RESOURCES; i++)
				FillRect(hdc1, &rect[i], hbrush[i % 6]);
			for (int i = 0; i < 6; i++)
				DeleteObject(hbrush[i]); // Free the brush resources
		} // End of draw the background
		EndPaint(hwnd, &ps);
		break;
	case WM_USER + 1:
		
		resourceValues[wParam] = lParam; // Update total number of times resource is used


		InvalidateRect(hwnd, NULL, true); // Windows needs redrawing
		UpdateWindow(hwnd); // Redraw this window.
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK threadProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
	{	// Added for the painting
		PAINTSTRUCT ps;
		HDC hdc2 = BeginPaint(hwnd, &ps);
		{
			int aiValuesToShow[NUM_CLIENTS];
			
			for (int i = 0; i < NUM_CLIENTS; i++)
				aiValuesToShow[i] = threadValues[i];

			// Now work out how high to make each bar
			int iMax = -10000000; int iMin = 10000000;
			for (int i = 0; i < 10; i++)
			{
				if (aiValuesToShow[i] < iMin) iMin = aiValuesToShow[i];
				if (aiValuesToShow[i] > iMax) iMax = aiValuesToShow[i];
			}
			if (iMin < 0) iMin = 0;
			if (iMax < (iMin + 1)) iMax = iMin + 1;
			int iDiff = iMax - iMin;

			//printf( "t%d b%d l%d r%d\n",rc.top,rc.bottom,rc.left,rc.right );
			HBRUSH hbrush[6];
			hbrush[0] = CreateSolidBrush(RGB(255, 0, 0));
			hbrush[1] = CreateSolidBrush(RGB(255, 255, 0));
			hbrush[2] = CreateSolidBrush(RGB(0, 255, 0));
			hbrush[3] = CreateSolidBrush(RGB(0, 255, 255));
			hbrush[4] = CreateSolidBrush(RGB(0, 0, 255));
			hbrush[5] = CreateSolidBrush(RGB(255, 0, 255));
			RECT rc;
			GetClientRect(hwnd, &rc);
			RECT rect[NUM_RESOURCES];
			for (int i = 0; i < NUM_CLIENTS; i++)
				rect[i] = rc; // Copy original size
			for (int i = 1; i < NUM_CLIENTS; i++)
				rect[i - 1].right = rect[i].left = rc.right * i / NUM_CLIENTS;
			// Fix heights to be relative to total
			int iFullHeight = rc.bottom - rc.top;
			for (int i = 0; i < NUM_CLIENTS; i++)
				rect[i].top = rect[i].bottom - (iFullHeight * aiValuesToShow[i]) / iMax;
			for (int i = 0; i < NUM_CLIENTS; i++)
				FillRect(hdc2, &rect[i], hbrush[i % 6]);
			for (int i = 0; i < 6; i++)
				DeleteObject(hbrush[i]); // Free the brush resources
		} // End of draw the background
		EndPaint(hwnd, &ps);
		break;
	}
	case WM_USER + 1:
		threadValues[wParam] += 1; // Add to total number of times thread called SendDataToServer()
		
		InvalidateRect(hwnd, NULL, true); // Windows needs redrawing
		UpdateWindow(hwnd); // Redraw this window.
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}



DWORD WINAPI HandleConnection(LPVOID lpData)
{
	// Grab the info that was passed in ...
	DataForThread* pDataPassedIn = (DataForThread*)lpData;
	SOCKET ClientSocket = pDataPassedIn->ClientSocket;
	int iConnectionNumber = pDataPassedIn->iConnectionNumber;
	// And then delete the data that was passed in
	// (We could just keep using it and delete it later but this prevents forgetting to do so)
	free(pDataPassedIn); // Matches the malloc below (search for it if not sure)
	// Now all of our data is on the stack - so will be tidied up for us

	// We have our own buffer for receiving data
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;
	int iResult;

	// New for handling a struct-based system.
	int iReceiveIndex = 0; // Index into struct that we are getting
	WrapperDataClientToServer dataReceived = { 0 }; // Initialise the structure to 0

	// Receive until the peer shuts down the connection
	do
	{
	
		iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
		//printf("iResult = %d\n", iResult);
		if (iResult > 0)
		{
			//printf("Connection %d: Bytes received: %d\n", iConnectionNumber, iResult);

			// This code will handle the current message
			for (int i = 0; i < iResult; i++)
			{ // Copy the bytes in
				dataReceived.b[iReceiveIndex++] = recvbuf[i];

				// As soon as a message is completed then handle it
				if (iReceiveIndex >= sizeof(DataClientToServer))
				{ // We have a full message now so do something with it:
					iReceiveIndex = 0; // Go back to start for the next one.

					// First copy any received values that we think we will need

					EnterCriticalSection(&threadVals);
					threadValues[dataReceived.a.procID] += 1;
					LeaveCriticalSection(&threadVals);

					EnterCriticalSection(&resourceVals);
					resourceValues[6] = dataReceived.a.resource7Count;
					resourceValues[7] = dataReceived.a.resource8Count;
					resourceValues[8] = dataReceived.a.resource9Count;
					resourceValues[9] = dataReceived.a.resource10Count;
					resourceValues[10] = dataReceived.a.resource11Count;
					resourceValues[11] = dataReceived.a.resource12Count;
					LeaveCriticalSection(&resourceVals);
					
					
					InvalidateRect(threadProgress, NULL, true); // Windows needs redrawing
					InvalidateRect(resourceAccess, NULL, true);

					UpdateWindow(threadProgress); // Redraw this window.
					UpdateWindow(resourceAccess);

					

				} // End of if condition for the whole message having been received.
			} // End of for loop, looping through the received data

		}
		else if (iResult == 0)
		{
			//printf("Connection %d: Connection closing...\n", iConnectionNumber);
		}
			
		else
		{
			printf("ClientSocket recv failed with error: %d\n", WSAGetLastError());
			closesocket(ClientSocket);
			WSACleanup();
			return 1;
		}
	} while (iResult > 0);


	// shutdown the connection since we're done
	iResult = shutdown(ClientSocket, SD_SEND);
	if (iResult == SOCKET_ERROR)
	{
		printf("ClientSocket shutdown failed with error: %d\n", WSAGetLastError());
	}

	// cleanup
	closesocket(ClientSocket);
	return 0; // success
}

DWORD WINAPI DoServer(LPVOID lpParm)
{
	int iResult;
	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;

	struct sockaddr_in localaddress;
	localaddress.sin_family = AF_INET;
	localaddress.sin_addr.s_addr = inet_addr("127.0.0.1");
	localaddress.sin_port = htons(DEFAULT_PORT);

	// Create a SOCKET for connecting to server
	ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ListenSocket == INVALID_SOCKET)
	{
		printf("socket failed with error: %ld\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}

	// Setup the TCP listening socket
	iResult = bind(ListenSocket, (SOCKADDR *)&localaddress, sizeof(localaddress));
	if (iResult == SOCKET_ERROR)
	{
		printf("bind failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR)
	{
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		return 1;
	}

	int iConnectionNumber = 0;

	// wait for incoming connections and accept them as they come in:
	while (TRUE)
	{
		//printf("Awaiting connection...");
		// Accept a client socket
		ClientSocket = accept(ListenSocket, NULL, NULL);
		if (ClientSocket == INVALID_SOCKET)
		{
			printf("accept failed with error: %d\n", WSAGetLastError());
			closesocket(ListenSocket);
			return 1;
		}

		// Allocate some memory to store any data we need to pass to the thread
		DataForThread* p = (DataForThread*)malloc(sizeof(DataForThread));
		p->ClientSocket = ClientSocket; // Socket to get data from
		p->iConnectionNumber = iConnectionNumber + 1; // number of this connection - add 1 to make it 1-based
		// Set any other data that you want to pass as well
		// Note - we assume that the client thread frees the memory - search for free( above this

		HANDLE h = CreateThread(NULL, 0, HandleConnection, p, 0, NULL);

	}
}


int main()
{
	WSADATA wsaData;
	// Initialize Winsock
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	WNDCLASSEX wc;
	//Step 1: Registering the Window Class
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = resourceProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetModuleHandle(NULL);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "resourceClass";
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	resourceAccess = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		"resourceClass", // NEEDS TO MATCH THE CLASS NAME
		"Resource Access",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 350, 120,
		NULL, NULL, GetModuleHandle(NULL), NULL);
	if (resourceAccess == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	ShowWindow(resourceAccess, SW_SHOW);
	UpdateWindow(resourceAccess);

	WNDCLASSEX wc2;
	//Step 1: Registering the Window Class
	wc2.cbSize = sizeof(WNDCLASSEX);
	wc2.style = 0;
	wc2.lpfnWndProc = threadProc;
	wc2.cbClsExtra = 0;
	wc2.cbWndExtra = 0;
	wc2.hInstance = GetModuleHandle(NULL);
	wc2.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc2.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc2.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc2.lpszMenuName = NULL;
	wc2.lpszClassName = "threadClass";
	wc2.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	if (!RegisterClassEx(&wc2))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	threadProgress = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		"threadClass", // NEEDS TO MATCH THE CLASS NAME
		"Thread Progress",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 350, 120,
		NULL, NULL, GetModuleHandle(NULL), NULL);
	if (threadProgress == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
	ShowWindow(threadProgress, SW_SHOW);
	UpdateWindow(threadProgress);

	InitializeCriticalSection(&threadVals);
	InitializeCriticalSection(&resourceVals);

	HANDLE thread1 = CreateThread(NULL, 0, DoServer, NULL, 0, NULL);

	MSG Msg;

	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	DeleteCriticalSection(&threadVals);
	DeleteCriticalSection(&resourceVals);

	CloseHandle(thread1);

	return Msg.wParam;


}