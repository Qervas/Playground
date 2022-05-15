#include<iostream>
#include<Windows.h>
using std::cout;
using std::endl;

#define KERNEL_OWNS_MUTEX
#define ABANDON
/*Mutex Kernel Object Exercise
Two applications: 1.writing to DB 2.reading from DB
Need to synchronize the access between the two
*
*/
HANDLE hMutex = NULL;

int main() {
	hMutex = CreateMutex(NULL, FALSE, TEXT("M1"));
	int err = GetLastError();
	if (err != 0 && err != ERROR_ALREADY_EXISTS) {
		cout << endl << "The mutex initialization failed...";
		return EXIT_FAILURE;
	}

	//Assume that we are wrting sth to DB
	DWORD dw = WaitForSingleObject(hMutex, INFINITE);
	cout << endl << "Press any key when the message comes that DB is updated";
	Sleep(10000);
	cout << endl << "DB writing completed, Press any key";
	getchar();


	ReleaseMutex(hMutex);
	CloseHandle(hMutex);
	return 0;
}