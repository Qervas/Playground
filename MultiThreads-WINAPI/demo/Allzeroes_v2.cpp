#include<iostream>
#include<Windows.h>

/* Create two threads(Reader and Writer)
And synchronize them using Critical Section w.r.t read and write operations
CRITICAL_SECTION is a user mode synchronization object.
i.e. This synchronization object can only synchronize the threads running 
	under the same process.
Recursion count: How many times a thread has acquired a critical section object
and to the same number of times you need to release it. i.e. you need to just LEAVE
the critical section those many times.

Spin count: The number of the times the API(TryEnterCriticalSection) will poll
the critical section object to find if it is available.
*/

int nArr[10] = { 0, };
HANDLE thReader;
HANDLE thWriter;
DWORD readerID;
DWORD writerID;

CRITICAL_SECTION cs;

void Reader() {
	//Read from the array
	EnterCriticalSection(&cs);
	for (int nIndex = 0; nIndex < 10; nIndex++) {
		std::cout << std::endl << nArr[nIndex];
		//Sleep(1000);
	}
	LeaveCriticalSection(&cs);
}

void Writer() {
	//Write to the array
	EnterCriticalSection(&cs);
	std::cout << std::endl << "Spin count : " << cs.SpinCount;

	//std::cout << std::endl << "Recursion count : " << cs.RecursionCount;
	for (int nIndex = 0; nIndex < 10; nIndex++) {
		nArr[nIndex] = (nIndex + 1) * 2;
		std::cout << std::endl << "Writing count...";
		//Sleep(1000);
	}
	std::cout << std::endl << "Writing stopped";
	LeaveCriticalSection(&cs);

}

int main() {


	//InitializeCriticalSection(&cs);
	InitializeCriticalSectionAndSpinCount(&cs, 100);
	thWriter = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Writer,
		NULL, 0, &writerID);
	/*(lpThreadAttributes: Priority inherits; dwStackSize: whatever the size will applicable to the thread(stackSize default:1MB),
	* dwCreationFlags: schedule the thread*/
	std::cout << std::endl << "The thread ID for writer thread:" << writerID;

	thReader = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Reader,
		NULL, 0, &readerID);
	std::cout << std::endl << "The thread ID for reader thread:" << readerID;

	HANDLE th[2] = { thWriter, thReader };
	WaitForMultipleObjects(2, th, TRUE, INFINITE);

	DeleteCriticalSection(&cs);

	return 0;


}



/*


*/