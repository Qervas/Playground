/*
要求：
输入：待扫描目录和字符串，比如c:\TestDir，abcd，即对c盘中TestDir全部文件进行扫描，看看有没有abcd字符串。
输出：匹配的文件名，偏移值，一个文件包含多个重复字符串需要全部报告。
*/
#include"ContentSearch.h"
constexpr auto hSize = 6;

HANDLE hScanEvent = NULL;
HANDLE hReadEvent = NULL;
HANDLE hWriteEvent = NULL;
HANDLE hScanner = NULL;
HANDLE hReader = NULL;
HANDLE hWriter = NULL;
DWORD scannerThId = 0;
DWORD readerThId = 0;
DWORD writerThId = 0;
DWORD readerMessageQueueCounter = 0;
DWORD writerMeesageQueueCounter = 0;


bool match_filename(_In_ const std::filesystem::path& path,_In_ std::regex*& pattern) {
	return std::regex_match(path.filename().string(), *pattern);
}

bool match_content(_In_ const string& content,_In_  std::regex*& pattern) {
	return std::regex_match(content, *pattern);
}
void Scanner(_Inout_opt_ const string& dir) {//Find out all files under the user defined dir
	cout << "ScannerThId:" << GetCurrentThreadId() << endl;

	std::filesystem::path path(dir);
	auto* dir_list = new queue<std::filesystem::path>();
	dir_list->push(path);
	DWORD dw;
	dw = WaitForSingleObject(hScanEvent, INFINITE);
	if (dw == WAIT_FAILED || dw == WAIT_ABANDONED || dw == WAIT_TIMEOUT) {
		cout << endl << "Event wait failed...";
		ExitThread(1);
	}
	//PostThreadMessage(readerThId, TEST_MESSAGE, 0, 0);
	while (!dir_list->empty()) {
		path = dir_list->front();
		dir_list->pop();
		for (const auto& entry : std::filesystem::directory_iterator(path)) {
			if (entry.is_directory()) { dir_list->push(entry.path()); }
			if(entry.is_regular_file()){
				printf(KGRN "%s " NONE "sending", entry.path().filename().string().c_str());
				printDots(3, 300);
				
				PostThreadMessage(readerThId, NORMAL_MESSAGE, NULL , (LPARAM)& entry.path());
				cout << *(std::filesystem::path*)((LPARAM)&entry.path()) << endl;
				readerMessageQueueCounter++;
				
				//cout << endl << entry.path().filename() << " is sending...";
				//ResetEvent(hScanEvent);
				Sleep(100);//Must be shorter than Sleep() in Reader()
			}

		}
	}
	WaitForSingleObject(hScanEvent, INFINITE); //Waiting for Writer end
	PostThreadMessage(readerThId, QUIT_MESSAGE, NULL, NULL);
	if (dir_list != nullptr) {
		while (!dir_list->empty()) { dir_list->pop(); }
		delete dir_list;
		dir_list = nullptr;
	}
	printf(KRED "Scanner Exit\n" NONE);
	ExitThread(0);

}

void Reader() {//Recieve filenames-->scan their contents-->write results into a file
	cout << "ReaderThId:" << GetCurrentThreadId() << endl;

	DWORD dw;
	dw = WaitForSingleObject(hReadEvent, INFINITE);
	if (dw == WAIT_FAILED || dw == WAIT_ABANDONED || dw == WAIT_TIMEOUT) {
		cout << endl << "Event wait failed...";
		ExitThread(1);
	}
	MSG msg;
	SetEvent(hScanEvent);//start scanner
	std::filesystem::path filename;
	while (GetMessage(&msg, NULL, 0, 0)) {
		printf(KBLU "%d" NONE "Recieved\n ", msg.message);
		if (msg.message == QUIT_MESSAGE) {
			cout << endl << "The message to exit has been recieved\n";
			break;
		}
		else if(msg.message == NORMAL_MESSAGE) {
			readerMessageQueueCounter--;
			filename = (*(std::filesystem::path*)msg.lParam).filename();
			printf(KCYN "%s" NONE " recieved\n", filename.string().c_str());
			SetEvent(hWriteEvent);
			if (readerMessageQueueCounter == 0) {//All message processed
				SetEvent(hScanEvent);//Notify hScanner to send QuitMessage
			}

		}
	}
	printf(KRED "Reader Exit\n" NONE);
	ExitThread(0);


}

void Writer(_Inout_opt_ Data* data) {
	cout << "WriterThId:" << GetCurrentThreadId() << endl;
	SetEvent(hReadEvent);
	DWORD dw;
	dw = WaitForSingleObject(hWriteEvent, INFINITE);
	if (dw == WAIT_FAILED || dw == WAIT_ABANDONED || dw == WAIT_TIMEOUT) {
		cout << endl << "Event wait failed...";
		ExitThread(1);
	}
	printf(KYEL "Writting\n" NONE);
	printDots(3, 500);
	//ResetEvent(hReadEvent);
	printf(KRED "Writer Exit\n" NONE);
	ExitThread(0);
}

int main(void) {
	string dir, target_extension="txt", str_to_find;
	cout << "Search Path: ";
	//getline(cin, dir);
	dir = "C:\\Users\\djmax\\Desktop\\lab\\VS\\MultiThreads_bistu\\data\\folder";
	cout << dir << endl;
	cout << "Search target_extension: " << "txt\n";
	//getline(cin, target_extension);
	getline(cin, str_to_find);
	if (target_extension == "" || dir == "" || str_to_find == "") { return EXIT_FAILURE; }


	Data data(dir, str_to_find);

	int err;
	hScanEvent = CreateEvent(NULL, TRUE, FALSE, TEXT("ScanfFilenamesEvent"));
	err = GetLastError();
	if (err != 0) {
		cout << "Create Event Failed..." << endl;
		return EXIT_FAILURE;
	}
	hReadEvent = CreateEvent(NULL, TRUE, FALSE, TEXT("ReadSinglefileEvent"));
	err = GetLastError();
	if (err != 0) {
		cout << "Create Event Failed..." << endl;
		return EXIT_FAILURE;
	}
	hWriteEvent = CreateEvent(NULL, TRUE, FALSE, TEXT("WriteSinglefileEvent"));
	err = GetLastError();
	if (err != 0) {
		cout << "Create Event Failed..." << endl;
		return EXIT_FAILURE;
	}
	hScanner = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Scanner, &dir, 0, &scannerThId);
	if (err != 0) {
		cout << "Create Reader Thread Failed..." << endl;
		return EXIT_FAILURE;
	}
	hReader = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Reader, NULL, 0, &readerThId);
	if (err != 0) {
		cout << "Create Reader Thread Failed..." << endl;
		return EXIT_FAILURE;
	}
	hWriter = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Writer, &data, 0, &writerThId);
	if (err != 0) {
		cout << "Create Writer Thread Failed..." << endl;
		return EXIT_FAILURE;
	}
	//For debug
	SetThreadDescription(hScanner, TEXT("Sacnner()"));
	SetThreadDescription(hReader, TEXT("Reader()"));
	SetThreadDescription(hWriter, TEXT("Writer()"));

	HANDLE hArr[hSize] = {hScanner,hReader, hWriter, hScanEvent, hReadEvent, hWriteEvent};
	//WaitForSingleObject(hReader, INFINITE);
	WaitForMultipleObjects(hSize, hArr, TRUE, INFINITE);

	for (int i = 0; i < hSize; i++) {
		CloseHandle(hArr[i]);
	}

	return EXIT_SUCCESS;
}