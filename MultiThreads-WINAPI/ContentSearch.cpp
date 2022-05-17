/*
要求：
输入：待扫描目录和字符串，比如c:\TestDir，abcd，即对c盘中TestDir全部文件进行扫描，看看有没有abcd字符串。
输出：匹配的文件名，偏移值，一个文件包含多个重复字符串需要全部报告。
*/

#include<iostream>
#include<string>
#include<queue>
#include<filesystem>
#include<regex>
#include<Windows.h>
#include<sal.h>
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::queue;

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
//end color
#define NONE        "\033[0m"
//background color
#define BBLACK      "40m"
#define BRED        "41m"
#define BGREEN      "42m"
#define BYELLOW     "43m"
#define BBLUE       "44m"
#define BPURPLE     "45m"
#define D_BGREEN    "46m"
#define BWHITE      "47m"


HANDLE hEvent = NULL;
HANDLE hReader = NULL;
HANDLE hWriter = NULL;
DWORD writerThId = 0;
DWORD readerThId = 0;

void printDots(int n, DWORD milliseconds) {
	while (n--) {
		printf(".");
		Sleep(milliseconds);
	}
}

struct Data {
	queue<std::filesystem::path>* dir_list = nullptr;
	std::regex* pattern = nullptr;
	string _target_extension;
	string _str_to_find;
	explicit Data() = delete;
	//Default searching *.txt files, for other types you need to deal with magic numbers of files
	explicit Data(_In_opt_ const string& dir, _In_opt_ const string& str_to_find, _In_ const string& target_extension = "txt") {
		dir_list = new queue<std::filesystem::path>();
		dir_list->push(dir);//, std::filesystem::path::native_format
		pattern = new std::regex("[[:print:]]*" + target_extension + "[[:print:]]*", std::regex::icase);
		_str_to_find = str_to_find;
		_target_extension = target_extension;
	}
	~Data() {
		if (dir_list != nullptr) {
			while (!dir_list->empty()) { dir_list->pop(); }
			delete dir_list;
			dir_list = nullptr;
		}
		if (pattern != nullptr) {
			delete pattern;
			pattern = nullptr;
		}
	}

};

bool match_filename(_In_ const std::filesystem::path& path, _In_ std::regex*& pattern) {
	return std::regex_match(path.filename().string(), *pattern);
}

bool match_content(_In_ const string& content, _In_  std::regex*& pattern) {
	return std::regex_match(content, *pattern);
}
void Reader(_Inout_opt_ Data* data) {//Find out all files under the user defined dir
	if (data == nullptr) { throw std::runtime_error("data pointer is nullptr"); }
	auto dir_list = data->dir_list;
	if (dir_list->empty()) { cout << endl << "Path empty"; ExitThread(0); }
	DWORD dw;
	std::filesystem::path path;
	while (!dir_list->empty()) {
		dw = WaitForSingleObject(hEvent, INFINITE);
		cout << "set" << endl;
		if (dw == WAIT_FAILED || dw == WAIT_ABANDONED || dw == WAIT_TIMEOUT) {
			cout << endl << "Event wait failed...";
			ExitThread(1);
		}
		path = dir_list->front();
		dir_list->pop();
		for (const auto& entry : std::filesystem::directory_iterator(path)) {
			if (entry.is_directory()) { dir_list->push(entry.path()); }
			if (entry.is_regular_file()) {
				printf(KGRN "%s " NONE "sending", entry.path().filename().string().c_str());
				printDots(3, 500);
				printf("\n");
				PostThreadMessage(writerThId, 3, (WPARAM)&entry.path(), NULL);
				//cout << endl << entry.path().filename() << " is sending...";
				ResetEvent(hEvent);
				Sleep(1000);
			}

		}
	}
	//WaitForSingleObject(hEvent, INFINITE); //Waiting for Writer end
	PostThreadMessage(writerThId, FALSE, NULL, NULL);
	ExitThread(0);

}

void Writer() {//Recieve filenames-->scan their contents-->write results into a file
	MSG msg;
	SetEvent(hEvent);
	while (GetMessage(&msg, NULL, 0, 0)) {
		if (msg.message == FALSE) {
			cout << endl << "The message to exit has been recieved";
			ExitThread(0);
		}
		printf(KCYN "%s" NONE " recieved\n", (*(std::filesystem::path*)msg.wParam).filename().string().c_str());
		Sleep(1000);
		SetEvent(hEvent);//Resume Reader() to send filenames
	}


}

int main(void) {
	string dir, target_extension = "txt", str_to_find;
	cout << "Search Path: ";
	//getline(cin, dir);
	dir = "C:\\Users\\djmax\\Desktop\\lab\\VS\\MultiThreads_bistu\\data";
	cout << dir << endl;
	cout << "Search target_extension: " << "txt\n";
	//getline(cin, target_extension);
	getline(cin, str_to_find);
	if (target_extension == "" || dir == "" || str_to_find == "") { return EXIT_FAILURE; }


	Data data(dir, str_to_find);

	int err;
	hEvent = CreateEvent(NULL, TRUE, FALSE, TEXT("Event"));
	err = GetLastError();
	if (err != 0) {
		cout << "Create Event Failed..." << endl;
		return EXIT_FAILURE;
	}
	hReader = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Reader, &data, 0, &readerThId);
	if (err != 0) {
		cout << "Create Reader Thread Failed..." << endl;
		return EXIT_FAILURE;
	}
	hWriter = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Writer, NULL, 0, &writerThId);
	if (err != 0) {
		cout << "Create Writer Thread Failed..." << endl;
		return EXIT_FAILURE;
	}
	SetThreadDescription(hReader, TEXT("Reader()"));
	SetThreadDescription(hWriter, TEXT("Writer()"));
	HANDLE hArr[3] = { hReader, hWriter, hEvent };
	//WaitForSingleObject(hReader, INFINITE);
	WaitForMultipleObjects(3, hArr, TRUE, INFINITE);

	CloseHandle(hReader);
	CloseHandle(hWriter);
	CloseHandle(hEvent);

	return EXIT_SUCCESS;
}