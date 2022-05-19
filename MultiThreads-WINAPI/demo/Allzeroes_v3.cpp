#include<iostream>
#include<Windows.h>


/*
* GetMessage is a blocking call and it waits till it gets a new message
* in the message queue
* PostThreadMessage is not a block call 
*/
#define MESSAGE_ENTER 0
#define MESSAGE_1 1
#define MESSAGE_2 2
#define MESSAGE_3 3
#define MESSAGE_4 4
#define MESSAGE_EXIT 5


HANDLE thSender;
HANDLE thReceiver;
DWORD senderID;
DWORD receiverID;

const char* sMessages[6] = {
	"Welcome Message",
	"First Message by sender",
	"Second Message by sender",
	"Third Message by sender",
	"Fourth Message by sender",
	"Exiting Message by sender",
};

void Sender() {

	for (int nIndex = 0; nIndex < 6; nIndex++) {
		Sleep(1000);
		PostThreadMessage(receiverID, nIndex, NULL, NULL);
	}

}

void Receiver() {
	MSG msg;
	while (GetMessage(&msg, NULL,0,0)) {
		std::cout << std::endl << sMessages[msg.message];
		if (msg.message == MESSAGE_EXIT) {
			break;
		}
	}
}
int main() {

	thReceiver = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Receiver,
		NULL, 0, &receiverID);
	Sleep(1000);
	
	thSender = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Sender,
		NULL, 0, &senderID);



	HANDLE th[2] = { thSender, thReceiver };
	WaitForMultipleObjects(2, th, TRUE, INFINITE);


	return 0;


}



