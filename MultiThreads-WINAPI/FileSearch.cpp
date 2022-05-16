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
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::queue;


HANDLE hEvent = NULL;
HANDLE hSlave = NULL;
struct Data {
	queue<std::filesystem::path>* dir_list = nullptr;
	std::regex* pattern = nullptr;
	explicit Data() = delete;
	explicit Data(const string& dir, const string target) {
		dir_list = new queue<std::filesystem::path>();
		dir_list->push(dir);//, std::filesystem::path::native_format
		pattern = new std::regex("[[:print:]]*" + target + "[[:print:]]*", std::regex::icase);
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

bool match_file(const std::filesystem::path& path, std::regex*& pattern) {
	return std::regex_match(path.filename().string(), *pattern);
}

bool match_content(const string& content, std::regex*& pattern) {
	return std::regex_match(content, *pattern);
}
void Slave(Data* data) {
	auto dir_list = data->dir_list;
	if (dir_list->empty()) { cout << endl << "Path empty"; ExitThread(0); }
	DWORD dw;
	dw = WaitForSingleObject(hEvent, INFINITE);
	while (!dir_list->empty()) {
		std::filesystem::path path = dir_list->front();
		dir_list->pop();
		for (const auto& entry : std::filesystem::directory_iterator(path)) {
			if (entry.is_directory()) { dir_list->push(entry.path()); }
			if (match_file(entry.path(), data->pattern)) {
				cout << endl << entry.path();
			}
		}
	}
	ExitThread(0);
	
}


int main(void) {
    string dir, target;
	cout << "Search Path: " ;
	getline(cin, dir);
	cout << "Search Target: ";
	getline(cin, target);
	if (target == "" || dir == "") {return EXIT_FAILURE; }


	Data data(dir, target);
	DWORD masterThId = 0;
	DWORD slaveThId = 0;
	hEvent = CreateEvent(NULL, FALSE, FALSE, TEXT("Event"));
	hSlave= CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Slave, &data, 0, &slaveThId);

	SetEvent(hEvent);
	WaitForSingleObject(hSlave,INFINITE);

	CloseHandle(hSlave);

	return EXIT_SUCCESS;
}