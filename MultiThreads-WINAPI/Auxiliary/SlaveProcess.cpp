#include<iostream>
#include<Windows.h>
using std::cout;
using std::endl;

//Slave
int main() {

	HANDLE hEvent = CreateEvent(NULL, true, FALSE, TEXT("EVT1"));
	/*NULL: Security Descriptor, true : a manual reset event
	FALSE: is not signaled*/
	int err = GetLastError();
	if (err != 0 && err != ERROR_ALREADY_EXISTS) {
		cout << endl << "Event Kernel Object was not created";
		return EXIT_FAILURE;
	}
	
	DWORD dw = WaitForSingleObject(hEvent, INFINITE);
	if (dw != WAIT_FAILED) {
		cout << endl << "Master is up and running ";
	}

	cout << endl << "Press Enter key to exit from slave";
	getchar();
	CloseHandle(hEvent);

	return 0;


}



