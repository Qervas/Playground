#include<iostream>
#include<Windows.h>
using std::cout;
using std::endl;

/* What is semaphore
-> Used for resource counting and synchronizing the access accordingly
->Server, maximum it  can accept 20 connections
->Writer, n-Readers
Initialize a semaphore
*/

HANDLE hSem = NULL;

int main(void) {
	hSem = CreateSemaphore(NULL, 1, 3,TEXT("SEM"));
	int err = GetLastError();
	if (err != 0 && err != ERROR_ALREADY_EXISTS) {
		cout << endl << "Semaphore Not Created";
		return EXIT_FAILURE;
	}
	cout << endl << "Press any key to make resources available";
	getchar();
	ReleaseSemaphore(hSem, 2, NULL);//Only release 2 sem
	CloseHandle(hSem);

}
