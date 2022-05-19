#include<iostream>
#include<Windows.h>
using std::cout;
using std::endl;

/* What is semaphore

*/

HANDLE hSem = NULL;

int main(void) {
	hSem = CreateSemaphore(NULL, 0, 3, TEXT("SEM"));//0: initial availble, 3:maximum available
	
	int err = GetLastError();
	if (err != 0 && err != ERROR_ALREADY_EXISTS) {
		cout << endl << "Semaphore Not Created";
		return EXIT_FAILURE;
	}
	DWORD dw = WaitForSingleObject(hSem, INFINITE);
	if (dw == WAIT_FAILED || dw == WAIT_ABANDONED || dw == WAIT_TIMEOUT) {
		cout << endl << "wait on semaphore failed";
		return EXIT_FAILURE;
	}
	cout << endl << "Press any key to close this app";
	CloseHandle(hSem);
	return 0;
}
