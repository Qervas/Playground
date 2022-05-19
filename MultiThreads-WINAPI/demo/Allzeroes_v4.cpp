#include<iostream>
#include<Windows.h>
using std::cout;
using std::endl;
/*Use the Event Kernel Object to let slave process know that master is up 
Manual Reset Events: It schedules all the threads waiting on an event
					ONCE the event gets signaled

Auto Reset Events: It schedules only one of the threads waiting on event 
					ONCE the event objtect gets signaled

*/
HANDLE thArr[4] = {NULL};
HANDLE hEvent = NULL;
void DemoThread() {
	cout << endl << "Thread ID:" << GetCurrentThreadId();
	DWORD dw = WaitForSingleObject(hEvent, INFINITE);
	if (dw != WAIT_FAILED && dw != WAIT_TIMEOUT && dw != WAIT_ABANDONED) {
		cout << endl << "Wait failed on the event kernel object";
		Sleep(3000);
		return;
	}
	else {
		cout << endl << "The Event got signaled... Ohter Thread need to wait 3 sec";
		SetEvent(hEvent);
	}
}
//Master
int main() {

	HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, TEXT("EVT1"));
		/*NULL: Security Descriptor, true : a manual reset event
		FALSE: is not signaled*/
	int err = GetLastError();
	if (err != 0 && err != ERROR_ALREADY_EXISTS) {
		cout << endl << "Event Kernel Object was not created";
		return EXIT_FAILURE;
	}

	for (int nIndex = 0; nIndex < 4; nIndex++) {
		thArr[nIndex] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)DemoThread,
			NULL, 0, NULL);
		int err = GetLastError();
		if (err != 0) {
			cout << endl << "The thread not created . sorry!";
			CloseHandle(hEvent);
			//TODO: close the thread handles as well
			//in case few threads inside the loop got created successfully
			return EXIT_FAILURE;
			
		}
	}

	cout << endl << "Press Enter key to singal the Auto Reset Event Object ";
	getchar();
	SetEvent(hEvent);

	WaitForMultipleObjects(4, thArr, TRUE, INFINITE);

	CloseHandle(hEvent);

	return 0;


}



