#include<iostream>
#include<Windows.h>
using std::cout;
using std::endl;

HANDLE hMutex;
int main() {
	hMutex = CreateMutex(NULL, FALSE, TEXT("M1"));
	int err = GetLastError();
	if (err != 0 && err != ERROR_ALREADY_EXISTS) {
		cout << endl << "The mutex initialization failed...";
		return EXIT_FAILURE;
	}
	DWORD dw = WaitForSingleObject(hMutex, INFINITE);
	if (dw == WAIT_FAILED || dw == WAIT_ABANDONED || dw == WAIT_TIMEOUT) {
		cout << endl << "The Wait Failed";
	}
	cout << endl << "The DB read is ready. Once done, press any key";
	getchar();
	ReleaseMutex(hMutex);
	CloseHandle(hMutex);

	return 0;
}