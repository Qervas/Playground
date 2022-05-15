#include<iostream>
#include<Windows.h>
using std::cout;
using std::endl;

#define KERNEL_OWNS_MUTEX
#define ABANDON
/*About the Mutex Kernel Object
* Mutex -> Mutual exclusion(no two threads can access the same resource at the same time)
*
* Recursion counter -> how many times a thread has acquired the mutex kernel object
*
* Ownership of Mutex: The thread which is the owner of the thread, if that comes to end
* then the mutex kernel object will be destroyed by the kernel
* Launch only one instance of the application using mutex App.exe
*
*
*/
HANDLE hMutex = NULL;

int main() {
#ifdef KERNEL_OWNS_MUTEX
	hMutex = CreateMutex(NULL, FALSE, TEXT("M1"));//mutex belongs to kernel
#else
	hMutex = CreateMutex(NULL, TRUE, TEXT("M1"));//mutex belongs to the thread as its HANDLE referring
#endif // KERNEL_OWNS_MUTEX

	int err = GetLastError();
	if (err != 0 && err != ERROR_ALREADY_EXISTS) {
		cout << endl << "The mutex initalization failed ...";
		return EXIT_FAILURE;
	}

	/*This Function call will acquire the mutex kernel object
	if it is signaled but if not siganled, then it will wait till the time specified
	if it is acquired by the thread, then after acquiring it, it will make it
	non siagnled at the same time which means than no other thread can now acquire it*/
#ifdef  ABANDON
	DWORD dw = WaitForSingleObject(hMutex, INFINITE);

	if (dw == WAIT_ABANDONED) {
		cout << endl << "Wait abandoned on mutex";
		return EXIT_FAILURE;
	}
#else

	DWORD dw = WaitForSingleObject(hMutex, 0);

	if (dw == WAIT_TIMEOUT) {
		cout << endl << "one instance of event kernel object is running...";
		return EXIT_FAILURE;
	}

#endif //  ABANDON


	if (dw == WAIT_ABANDONED || dw == WAIT_FAILED || dw == WAIT_TIMEOUT) {
		cout << endl << "The wait failed";
		return EXIT_FAILURE;
	}

	cout << endl << "App is running and press any key to get this closed";
	getchar();

	ReleaseMutex(hMutex);
	CloseHandle(hMutex);

	return 0;
}