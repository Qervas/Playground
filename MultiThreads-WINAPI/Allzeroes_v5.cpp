#include<iostream>
#include<Windows.h>
using std::cout;
using std::endl;

/*Use the event kernel object and critical section to enable the 
communication among the 2 threads

Sender should send the message to reciever only when the reciever 
is ready to recieve
*/
#define MSGEXIT 4

HANDLE hSender = NULL;
HANDLE hReciever = NULL;
HANDLE hEvent = NULL;
CRITICAL_SECTION cs;
DWORD thIDSender;
DWORD thIDReciever;

//shouldn't be able to send any message til the reciever says that it's ok
void Sender() {
	DWORD dw = WaitForSingleObject(hEvent, INFINITE);
	if (dw != WAIT_FAILED && dw != WAIT_ABANDONED && dw != WAIT_TIMEOUT) {
		for (int i = 0; i < 5; ++i) {
			EnterCriticalSection(&cs);
			cout << endl << "Sending the message...";
			Sleep(1000);
			PostThreadMessage(thIDReciever, i, NULL, NULL);
			LeaveCriticalSection(&cs);
		}
	}
}

void Reciever() {
	MSG m;
	SetEvent(hEvent);
	while (GetMessage(&m, NULL, 0, 0)) {
		EnterCriticalSection(&cs);
		if (m.message == MSGEXIT) {
			cout << endl << "The message to exit has been recieved";
			LeaveCriticalSection(&cs);
			break;
		}
		cout << endl << "The message recieved:" << m.message;
		Sleep(1000);
		LeaveCriticalSection(&cs);
	}
	
}


int main() {
	HANDLE hEvent = CreateEvent(NULL, TRUE, FALSE, TEXT("Evt1"));
	InitializeCriticalSection(&cs);
	hReciever = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Reciever,
		NULL, 0, &thIDReciever);
	hSender = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Sender,
		NULL, 0, &thIDSender);
	HANDLE hArr[2] = { hSender, hReciever };
	WaitForMultipleObjects(2, hArr, TRUE, INFINITE);
	DeleteCriticalSection(&cs);
	return 0;
}