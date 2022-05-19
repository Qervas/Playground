#pragma once

#include<iostream>
#include<string>
#include<queue>
#include<filesystem>
#include<regex>
#include<fstream>
#include<Windows.h>
#include<sal.h>
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::queue;

#define NORMAL_MESSAGE 3
#define QUIT_MESSAGE 2
#define TEST_MESSAGE 1


//fonts color
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



struct Data {
	//queue<string>* out_buffer = nullptr; //share between Reader() and Writer()
	std::filesystem::path* _work_dir;
	std::regex* _pattern = nullptr;
	string _target_extension;
	explicit Data() = default;
	//Default searching *.txt files, for other types you need to deal with magic numbers of files
	explicit Data(_In_opt_ const std::string& work_dir,_In_opt_ const string& str_to_find, _In_ const string& target_extension = "txt") {
		_work_dir = new std::filesystem::path(work_dir);
		//out_buffer = new queue<string>();
		_pattern = new std::regex(str_to_find,std::regex::icase);
		_target_extension = "." + target_extension;
	}
	~Data() {
		if (_work_dir != nullptr) {
			delete _work_dir;
			_work_dir = nullptr;

		}
		//if (out_buffer != nullptr) {
		//	while (!out_buffer->empty()) { out_buffer->pop(); }
		//	delete out_buffer;
		//	out_buffer = nullptr;
		//}
		if (_pattern != nullptr) {
			delete _pattern;
			_pattern = nullptr;
		}
	}
};
