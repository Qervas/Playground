/*
 * @Author: FrankTudor
 * @Date: 2022-05-19 18:45:53
 * @LastEditors: FrankTudor
 * @Description: This file is created, edited, contributed by FrankTudor
 * @LastEditTime: 2022-05-22 23:54:18
 */
#include "ContentSearch.h"

constexpr auto THREAD_SIZE = 3;
void* Scanner(void*);
void* Reader(void*);
void* Writer(void*);


int main() {
    fs::path directory_to_search, directory_for_output;
    std::string filetype, tofind;
    std::string input;
    std::cout << "Search directory_to_search[./]: ";
    getline(std::cin, input);
    if(input.empty()){
        directory_to_search = fs::current_path();
    }else{
        directory_to_search = fs::path(input);
    }
    std::cout << "Output directory[./]: ";
    getline(std::cin, input);
    if(input.empty()){
        directory_for_output = fs::current_path();
    }else{
        directory_for_output = fs::path(input);
    }
    std::cout << "Search filetype[All text files]: ";
    getline(std::cin, filetype);
    std::cout << "Search contents[Not null]:";
    getline(std::cin, tofind);
    std::cout << "Case sensitive[Y/n]?";
    char Yes_or_No;
    scanf("%c",&Yes_or_No);
    bool case_sensitive = Yes_or_No == 'Y' || Yes_or_No == 'y';
    Data data(directory_to_search, directory_for_output, tofind, case_sensitive, filetype);
    void *(*fun[3])(void*) = {Scanner, Reader, Writer};

    pthread_t th[THREAD_SIZE];
    int err;
    for(int i = 0; i < THREAD_SIZE; i++){
        err = pthread_create(&th[i], nullptr, fun[i], (void*)&data);
        if(err != 0){
            perror("thread creation failed");
        }
    }


    for(unsigned long i : th){
        err = pthread_join(i, nullptr);
        if(err != 0){
            perror("thread join failed");
        }
    }


    return EXIT_SUCCESS;

}
