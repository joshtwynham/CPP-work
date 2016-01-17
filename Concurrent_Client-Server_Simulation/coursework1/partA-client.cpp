// This file contains:

// 1: Code for you to copy into your main program file
// 2: Code for you to copy-paste into your windows procedures to avoid having to write drawing code yourself


// You MUST include this header file at the top of your main program file and MUST NOT modify the contents of the header file.
// We will use our own version of this header file for the marking.
#include "DoNotChangeThese.h"
#include "stdio.h"

volatile DWORD resource1Count;
volatile DWORD resource2Count;
volatile DWORD resource3Count;
volatile DWORD resource4Count;
volatile DWORD resource5Count;
volatile DWORD resource6Count;

CRITICAL_SECTION criticalSection;

// The following functions should all be in your main program file that you included the header above into
// IMPORTANT: You may ADD to the following functions but you MUST NOT delete anything
// Our tests on your final code will need everything that was there before and will use this to test your code.

HWND resourceAccess = FindWindow("resourceClass", NULL);
HWND threadProgress = FindWindow("threadClass", NULL);

void TestCase1()
{
	StartingFunction(1); // Do not remove - for testing purposes


	InterlockedIncrement(&resource1Count);

	EnterCriticalSection(&criticalSection);

	UseResource(1);	// Do not remove - for testing purposes

	LeaveCriticalSection(&criticalSection);

	EndingFunction(1); // Do not remove - for testing purposes
}

void TestCase2()
{
	StartingFunction(2); // Do not remove - for testing purposes

	InterlockedIncrement(&resource2Count);

	EnterCriticalSection(&criticalSection);

	UseResource(2);	// Do not remove - for testing purposes

	LeaveCriticalSection(&criticalSection);

	EndingFunction(2); // Do not remove - for testing purposes
}

void TestCase3()
{
	StartingFunction(3); // Do not remove - for testing purposes

	InterlockedIncrement(&resource3Count);

	EnterCriticalSection(&criticalSection);

	UseResource(3);	// Do not remove - for testing purposes
	
	LeaveCriticalSection(&criticalSection);

	EndingFunction(3); // Do not remove - for testing purposes
}

void TestCase4()
{
	StartingFunction(4); // Do not remove - for testing purposes

	InterlockedIncrement(&resource4Count);

	EnterCriticalSection(&criticalSection);

	UseResource(4);	// Do not remove - for testing purposes

	LeaveCriticalSection(&criticalSection);

	EndingFunction(4); // Do not remove - for testing purposes
}

void TestCase5()
{
	StartingFunction(5); // Do not remove - for testing purposes

	InterlockedIncrement(&resource5Count);

	EnterCriticalSection(&criticalSection);

	UseResource(5);	// Do not remove - for testing purposes

	LeaveCriticalSection(&criticalSection);

	EndingFunction(5); // Do not remove - for testing purposes
}

void TestCase6()
{
	StartingFunction(6); // Do not remove - for testing purposes

	InterlockedIncrement(&resource1Count);
	InterlockedIncrement(&resource2Count);

	EnterCriticalSection(&criticalSection);

	UseTwoResources(1, 2);	// Do not remove - for testing purposes

	LeaveCriticalSection(&criticalSection);

	EndingFunction(6); // Do not remove - for testing purposes
}

void TestCase7()
{
	StartingFunction(7); // Do not remove - for testing purposes

	InterlockedIncrement(&resource2Count);
	InterlockedIncrement(&resource3Count);

	EnterCriticalSection(&criticalSection);

	UseTwoResources(2, 3);	// Do not remove - for testing purposes

	LeaveCriticalSection(&criticalSection);

	EndingFunction(7); // Do not remove - for testing purposes
}

void TestCase8()
{
	StartingFunction(8); // Do not remove - for testing purposes

	InterlockedIncrement(&resource3Count);
	InterlockedIncrement(&resource5Count);
	InterlockedIncrement(&resource6Count);

	EnterCriticalSection(&criticalSection);

	int iTemp = StartToUseResource(3); // Do not remove - for testing purposes
	UseTwoResources(5, 6);  // Do not remove - for testing purposes
	FinishUsingResource(3, iTemp); // Do not remove - for testing purposes

	LeaveCriticalSection(&criticalSection);

	EndingFunction(8); // Do not remove - for testing purposes
}

void TestCase9()
{
	StartingFunction(9); // Do not remove - for testing purposes

	InterlockedIncrement(&resource4Count);

	EnterCriticalSection(&criticalSection);

	int iTemp = StartToUseResource(4); // Do not remove - for testing purposes
	TestCase6(); // Do not remove - for testing purposes
	FinishUsingResource(4, iTemp); // Do not remove - for testing purposes

	LeaveCriticalSection(&criticalSection);

	EndingFunction(9); // Do not remove - for testing purposes
}

void TestCase10()
{
	StartingFunction(10); // Do not remove - for testing purposes

	InterlockedIncrement(&resource1Count);

	EnterCriticalSection(&criticalSection);

	int iTemp = StartToUseResource(1); // Do not remove - for testing purposes
	TestCase7(); // Do not remove - for testing purposes
	FinishUsingResource(1, iTemp); // Do not remove - for testing purposes

	LeaveCriticalSection(&criticalSection);

	EndingFunction(10); // Do not remove - for testing purposes
}

void TestCase11()
{
	StartingFunction(11); // Do not remove - for testing purposes

	InterlockedIncrement(&resource3Count);
	InterlockedIncrement(&resource4Count);
	InterlockedIncrement(&resource5Count);
	InterlockedIncrement(&resource6Count);

	EnterCriticalSection(&criticalSection);
	
	int iTemp3 = StartToUseResource(3); // Do not remove - for testing purposes
	int iTemp4 = StartToUseResource(4); // Do not remove - for testing purposes

	UseTwoResources(5, 6);  // Do not remove - for testing purposes

	FinishUsingResource(3, iTemp3); // Do not remove - for testing purposes
	FinishUsingResource(4, iTemp4); // Do not remove - for testing purposes

	LeaveCriticalSection(&criticalSection);

	EndingFunction(11); // Do not remove - for testing purposes
}

void TestCase12()
{
	StartingFunction(12); // Do not remove - for testing purposes

	InterlockedIncrement(&resource5Count);

	EnterCriticalSection(&criticalSection);

	int iTemp = StartToUseResource(5); // Do not remove - for testing purposes
	TestCase3(); // Do not remove - for testing purposes
	FinishUsingResource(5, iTemp); // Do not remove - for testing purposes

	LeaveCriticalSection(&criticalSection);

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

	InterlockedIncrement(&resource4Count);
	InterlockedIncrement(&resource5Count);
	InterlockedIncrement(&resource6Count);

	EnterCriticalSection(&criticalSection);

	
	int iTemp4 = StartToUseResource(4); // Do not remove - for testing purposes
	int iTemp5 = StartToUseResource(5); // Do not remove - for testing purposes
	int iTemp6 = StartToUseResource(6); // Do not remove - for testing purposes

	FinishUsingResource(4, iTemp4); // Do not remove - for testing purposes
	FinishUsingResource(5, iTemp5); // Do not remove - for testing purposes
	FinishUsingResource(6, iTemp6); // Do not remove - for testing purposes

	LeaveCriticalSection(&criticalSection);

	EndingFunction(14); // Do not remove - for testing purposes
}

void TestCase15()
{
	StartingFunction(15); // Do not remove - for testing purposes

	InterlockedIncrement(&resource4Count);
	InterlockedIncrement(&resource5Count);
	InterlockedIncrement(&resource6Count);

	EnterCriticalSection(&criticalSection);

	
	int iTemp4 = StartToUseResource(4); // Do not remove - for testing purposes
	int iTemp5 = StartToUseResource(5); // Do not remove - for testing purposes
	int iTemp6 = StartToUseResource(6); // Do not remove - for testing purposes

	TestCase1(); // Do not remove - for testing purposes
	TestCase7(); // Do not remove - for testing purposes
	TestCase6(); // Do not remove - for testing purposes

	FinishUsingResource(4, iTemp4); // Do not remove - for testing purposes
	FinishUsingResource(5, iTemp5); // Do not remove - for testing purposes
	FinishUsingResource(6, iTemp6); // Do not remove - for testing purposes

	LeaveCriticalSection(&criticalSection);

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

	PostMessage(resourceAccess, WM_USER + 1, 0, resource1Count);
	PostMessage(resourceAccess, WM_USER + 1, 1, resource2Count);
	PostMessage(resourceAccess, WM_USER + 1, 2, resource3Count);
	PostMessage(resourceAccess, WM_USER + 1, 3, resource4Count);
	PostMessage(resourceAccess, WM_USER + 1, 4, resource5Count);
	PostMessage(resourceAccess, WM_USER + 1, 5, resource6Count);

	PostMessage(threadProgress, WM_USER+1, iProcessOrThreadID - 1, NULL);

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

	InitializeCriticalSection(&criticalSection);

	resource1Count = 0;
	resource2Count = 0;
	resource3Count = 0;
	resource4Count = 0;
	resource5Count = 0;
	resource6Count = 0;

	HANDLE thread1 = CreateThread(NULL, 0, Procedure1, NULL, 0, NULL);
	HANDLE thread2 = CreateThread(NULL, 0, Procedure2, NULL, 0, NULL);
	HANDLE thread3 = CreateThread(NULL, 0, Procedure3, NULL, 0, NULL);
	HANDLE thread4 = CreateThread(NULL, 0, Procedure4, NULL, 0, NULL);
	HANDLE thread5 = CreateThread(NULL, 0, Procedure5, NULL, 0, NULL);

	WaitForSingleObject(thread1, INFINITE);
	WaitForSingleObject(thread2, INFINITE);
	WaitForSingleObject(thread3, INFINITE);
	WaitForSingleObject(thread4, INFINITE);
	WaitForSingleObject(thread5, INFINITE);

	CloseHandle(thread1);
	CloseHandle(thread2);
	CloseHandle(thread3);
	CloseHandle(thread4);
	CloseHandle(thread5);

	printf("resource1Count = %d\nresource2Count = %d\nresource3Count = %d\nresource4Count = %d\nresource5Count = %d\nresource6Count = %d\n", resource1Count,resource2Count,resource3Count,resource4Count,resource5Count,resource6Count);

	DeleteCriticalSection(&criticalSection);

	do
	{
		printf("Press Enter to finish.");
	} while (getchar() != '\n');

}