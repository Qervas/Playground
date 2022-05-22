//
// Created by franktudor on 5/21/22.
//
#include "ContentSearch.h"

void* Scanner(void* args){
    printf(KWHT "Scanner\n" NONE);
    Data * data = (Data*) args;
    std::queue<fs::path> path_list;
    auto file_list = data->getPtrFile_list();
    fs::path path = data->getDirectory_to_search();
    path_list.push(path);
    while(!path_list.empty()){
        path = path_list.front();
        for(const auto& entry: std::filesystem::directory_iterator(path)){
            if(entry.is_directory()){path_list.push(entry.path());}
            if(entry.is_regular_file()){
                printf(KGRN " %s " NONE "found\n", entry.path().string().c_str());
                file_list->push(entry.path());
                usleep(500000);
            }
        }
        path_list.pop();
    }
    data->setScannerIsWorking(false);
    printf(KRED "Scanner " NONE "exit\n");
    pthread_exit(nullptr);
}

void* Reader(void* args){
    printf(KWHT "Reader\n" NONE);
    Data* data = (Data*) args;
    std::queue<std::filesystem::path>* file_list = data->getPtrFile_list();
    std::queue<std::string>* print_list = data->getPtrPrint_list();
    fs::path file;
    std::string line;
    size_t line_number;
    bool matched = false;
    while(data->getScannerIsWorking() || !file_list->empty()){
        if(!file_list->empty()){
            file = file_list->front();
//            printf("Reading %s\n", file.string().c_str());
            file_list->pop();
            std::ifstream infile(file);
            std::string str_to_write = file.string() + ": ";
            line_number = 0;
            matched = false;
            printf(KGRN "%s " NONE "Reading....\n", file.filename().string().c_str());
            while(std::getline(infile, line)){
//                printf("%s\n", line.c_str());
                std::sregex_iterator end, iter(line.begin(), line.end(), *(data->_pattern));
                if(!iter->empty()){matched = true;}
                while(iter != end){
                    str_to_write.append("(" + std::to_string(line_number) + ", " + std::to_string(iter->position()) + ") ");
                    iter++;
                }
                line_number++;
            }
            if(matched){
                print_list->push(str_to_write);
//                printf(KMAG "%s\n" NONE, str_to_write.c_str());
            }
            infile.close();

        }else{
            printf("Reader is waiting...\n");
        }
        usleep(500000);
    }

    data->setReaderIsWorking(false);
    printf(KRED "Reader " NONE "exit\n");

    pthread_exit(nullptr);
}
void* Writer(void* args){
    printf(KWHT "Writer\n" NONE);
    Data* data = (Data*) args;
    std::queue<std::string>* print_list = data->getPtrPrint_list();
    fs::path outpath = data->getDirectory_for_output();
    std::ofstream outfile(outpath.string() + "/output.txt");
    while(data->getReaderIsWorking() || !print_list->empty()){
        if(!print_list->empty()){
            std::string str_to_write = print_list->front();
            outfile << str_to_write << "\n\n";
            print_list->pop();
        }
    }
    outfile.close();
    printf(KRED "Writer " NONE "exit\n");
    pthread_exit(nullptr);
}

Data::Data(const fs::path &directory_to_search, const fs::path &directory_for_output, const std::string &tofind,
           const bool &casesensitive, const std::string &filetype) {

    _directory_to_search = directory_to_search;
    _directory_for_output = directory_for_output;

    if (casesensitive) {
        _pattern = new std::regex(tofind);
    } else {
        _pattern = new std::regex(tofind, std::regex::icase);
    }
    file_list = new std::queue<fs::path>();
    print_list = new std::queue<std::string>();

    scannerWorking = true;
    readerWorking = true;
//        //Todo: filetype
}
