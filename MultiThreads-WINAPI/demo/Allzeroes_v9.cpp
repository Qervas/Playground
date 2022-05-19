#include<iostream>
#include<Windows.h>
using std::cout;
using std::endl;

#define MESSAGE_1 100
#define MESSAGE_2 101
#define MESSAGE_3 102
#define MESSAGE_4 103
#define MESSAGE_5 104
#define QUIT_MESSAGE 99

//#define PEEK
typedef struct Test1 Test;
typedef struct Test1 {
	int nRoll;
	char sName[32 + 1];
}Test;
/*
GetMessage and PeekMessage
Sending data with mesage
*/
void Func() {
	MSG msg;
	int k;
#ifdef PEEK
	//last para of PeekMessage(): 0 is not removing the msg from msg queue, 1 is removing
	//Not a synchronizing function
	while ((k = PeekMessage(&msg, NULL, 0, 0, 1)) || 1) {//or 1 hack: when k==0 before msg is sent
		Sleep(1000);
		if (msg.message < QUIT_MESSAGE || msg.message > MESSAGE_5)continue;//to filter garbage msg
#else //GetMessage
	while (GetMessage(&msg, NULL, 0, 0)) { // NULL: indicates which window's sending msg
		//Really a synchronizing function
#endif // S1

		if (msg.message == QUIT_MESSAGE) {
			cout << endl << "Now quitting";
			ExitThread(0);
		}
		cout << endl << "The message got: " << msg.message;
		Test* t = (Test*)msg.wParam;
		cout << endl << "The name: " << t->sName << endl << "The Roll No." << t->nRoll;
		delete t;

	}
}

int main() {
	DWORD thId = 0;
	HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Func, NULL, 0, &thId);
	for (int i = MESSAGE_1; i <= MESSAGE_1 + 4; i++) {
		//char* t = new char[20];
		//strcpy_s(t, 20, "Lahdoon");
		Test* t = new Test;
		t->nRoll = 1000;
		strcpy_s(t->sName, "Frank");
		Sleep(1000);
		PostThreadMessage(thId, i, (WPARAM)t, 0);
	}
	PostThreadMessage(thId, QUIT_MESSAGE, 0, 0);
	WaitForSingleObject(hThread, INFINITE);
	return 0;
}