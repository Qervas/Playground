/*
 * @Author: FrankTudor
 * @Date: 2022-05-23 00:06:37
 * @LastEditors: FrankTudor
 * @Description: This file is created, edited, contributed by FrankTudor
 * @LastEditTime: 2022-05-23 14:41:14
 */

#ifndef CONTENTSEARCH_POSIX_H
#define CONTENTSEARCH_POSIX_H
#include <iostream>
#include <pthread.h>
#include<queue>
#include <regex>
#include <filesystem>
#include<fstream>
#include<unordered_set>
namespace fs = std::filesystem;
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


class Data{
public:
    std::unordered_set<std::string> _filetype_list;
    fs::path _directory_to_search;
    fs::path _directory_for_output;
    std::regex *_pattern ;
    bool scannerWorking, readerWorking;
    std::queue<fs::path> *file_list;
    std::queue<std::string> *print_list;

public:
    Data() =default;
    explicit Data(const fs::path& directory_to_search, const fs::path& directory_for_output,\
                  const std::string& tofind, const bool& casesensitive, const std::string& filetype);
    ~Data(){
        if(file_list != nullptr){
            while (!file_list->empty())file_list->pop();
            file_list = nullptr;
        }
        if(print_list != nullptr){
            while (!print_list->empty())print_list->pop();
            print_list = nullptr;
        }
        delete _pattern;
    }

    fs::path getDirectory_to_search(){
        return _directory_to_search;
    }
    fs::path getDirectory_for_output(){
        return _directory_for_output;
    }
    std::queue<fs::path>* getPtrFile_list(){return file_list;}
    std::queue<std::string>* getPtrPrint_list(){return print_list;}

    [[nodiscard]] bool getScannerIsWorking() const{return scannerWorking;}
    [[nodiscard]] bool getReaderIsWorking() const{return readerWorking;}
    void setScannerIsWorking(bool status){scannerWorking = status;}
    void setReaderIsWorking(bool status){readerWorking = status;}
    std::regex getPattern(){return *_pattern;}
    bool getFiletypeIsExist() const{
        return !_filetype_list.empty();
    }
    std::unordered_set<std::string>& getFiletypeList(){
        return _filetype_list;
    }
};


#endif //CONTENTSEARCH_POSIX_H
