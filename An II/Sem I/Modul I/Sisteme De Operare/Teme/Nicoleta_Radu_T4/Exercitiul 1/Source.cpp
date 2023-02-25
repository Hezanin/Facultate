#include <windows.h>
#include <stdio.h>  

#define MAX_THREADS 3 
// In Win32, functiile asociate firelor de executie se declara astfel
// DWORD WINAPI <nume_functie>(LPVOID);

DWORD WINAPI factorial(LPVOID);

HANDLE hThreads[MAX_THREADS];
DWORD  id[MAX_THREADS];
DWORD  dExitCode[MAX_THREADS];
DWORD  waiter;

DWORD WINAPI factorial(LPVOID n)
{
	int copyN = (int)n;
	int tempCopy{0};
	//char temp[100];

	if (copyN == 1 || copyN == 0)
	{
		return 1;
	}
	else
	{
		printf("%d\n", copyN);
		tempCopy = copyN - 1;
		return copyN * factorial((LPVOID)tempCopy);
	}
}

int main()
{
	//int CONSTANT = 2000;
	//char myString[30];
	//strcpy_s(myString, "Thread-urile sunt simple!");

	//hThreads[0] = CreateThread(NULL, 0, genericThreadFunc1, (LPVOID)0, NULL, &id[0]);
	int userInput{ 0 }, rezultat{0};
	char buffer[100];

	printf("n = "); scanf_s("%d", &userInput);
	dExitCode[0] = factorial((LPVOID)userInput);
	sprintf_s(buffer, "%lu", (unsigned int)dExitCode[0]);
	rezultat = atoi(buffer);
	printf("%d\n", rezultat);

	waiter = WaitForMultipleObjects(MAX_THREADS, hThreads,
		TRUE, INFINITE);

	for (int i = 0; i < MAX_THREADS; i++) {
		CloseHandle(hThreads[i]);
	}		 return 0;
}
