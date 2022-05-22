//
// Created by franktudor on 5/21/22.
//
#include "ContentSearch.h"

void* Scanner(void* args){
    printf(KWHT "Scanner\n" NONE);
    Data * data = (Data*) args;
    std::deque<std::filesystem::path> path_list;
    auto file_list = data->getPtrFile_list();
    fs::path path = data->getDirectory_to_search();
    path_list.push_back(path);
    while(!path_list.empty()){
        path = path_list.front();
        for(const auto& entry: std::filesystem::directory_iterator(path)){
            if(entry.is_directory()){path_list.push_back(entry.path());}
            if(entry.is_regular_file()){
                printf(KGRN " %s " NONE "found\n", entry.path().string().c_str());
                file_list->push(entry.path());
                usleep(500000);
            }
        }
        path_list.pop_front();
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
            while(std::getline(infile, line)){
//                printf("%s\n", line.c_str());
                std::sregex_iterator end, iter(line.begin(), line.end(), data->_pattern);
                if(!iter->empty()){matched = true;}
                while(iter != end){
                    str_to_write.append("(" + std::to_string(line_number) + ", " + std::to_string(iter->position()) + ") ");
                    iter++;
                }
                line_number++;
            }
            if(matched){
                print_list->push(str_to_write);
                printf(KMAG "%s\n" NONE, str_to_write.c_str());
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
//    std::queue<std::string>* print_list = data->getPrint_list();
////    std::filesystem::path* output_path = data->getDirectory_for_output();
////    std::ofstream outfile(output_path->string() + "./output.txt");
//    std::ofstream outfile("build/output.txt");
//    while(data->getReaderIsWorking() || !print_list->empty()){
//        if(!print_list->empty()){
//            std::string str_to_write = print_list->front();
//            outfile << str_to_write << "\n";
//            print_list->pop();
//        }
//    }
//    outfile.close();
    printf(KRED "Writer " NONE "exit\n");
    pthread_exit(nullptr);
}
