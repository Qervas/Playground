#include<iostream>
#include<Windows.h>

/*
HANDLE: Index of the kernel object used by your process/program in execution.
HANDLE and Process HANDLE Table
HANDLE :index of a kernel obj used in your program
main thread is the parent for all the threads. If main is done, rest of threads are meaningless
*/

int nArr[10] = { 0, };
HANDLE thReader;
HANDLE thWriter;
DWORD readerID;
DWORD writerID;

void Reader() {
	//Read from the array
	for (int nIndex = 0; nIndex < 10; nIndex++) {
		std::cout << std::endl << nArr[nIndex];
		Sleep(1000);
	}
}

void Writer() {
	//Write to the array
	for (int nIndex = 0; nIndex < 10; nIndex++) {
		nArr[nIndex] = (nIndex + 1) * 2;
		std::cout << std::endl << "Writing count...";
		Sleep(1000);
	}
	std::cout << std::endl << "Writing stopped";
}

int main() {
	//std::cout << std::endl << "The thread id for main thread is: " << GetCurrentThreadId();
	//std::cout << std::endl << "The priority of main thread is:" << GetThreadPriority(GetCurrentThread());
	thWriter = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Writer,
		NULL, 0, &writerID);
	/*(lpThreadAttributes: Priority inherits; dwStackSize: whatever the size will applicable to the thread(stackSize default:1MB),
	* dwCreationFlags: schedule the thread*/
	std::cout << std::endl << "The thread ID for writer thread:" << writerID;

	thReader = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Reader,
		NULL, CREATE_SUSPENDED, &readerID);
	std::cout << std::endl << "The thread ID for reader thread:" << readerID;

	HANDLE th[2] = { thWriter, thReader };
	WaitForMultipleObjects(2, th, TRUE, INFINITE);

	return 0;


}



/*
A process is inert.
A process is a container of threads
Every process must have one thread at least to start the execution
The only thread(if it is only one thread in process), is main thread
The thread itself inside a program is not a kernel object but
There is an associated kernel object through which this thread is managed

Lower the priority number, higher the priority

*/