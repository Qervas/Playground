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

void Scanner(_In_opt_ const Data& data) {//Find out all files under the user defined dir
	printf(KCYN "Scanner Enter\n" NONE);
	DWORD dw;
	std::filesystem::path path = *(data._work_dir);
	auto* dir_list = new std::queue<std::filesystem::path>();
	dir_list->push(path);//Remeber freeing space that you would claime on heap
	dw = WaitForSingleObject(hScanEvent, INFINITE);
	if (dw == WAIT_FAILED || dw == WAIT_ABANDONED || dw == WAIT_TIMEOUT) {
		std::cout << std::endl << "Event wait failed...";
		ExitThread(1);
	}
	while (!dir_list->empty()) {
		path = dir_list->front();
		dir_list->pop();
		for (const auto& entry : std::filesystem::directory_iterator(path)) {
			if (entry.is_directory()) { dir_list->push(entry.path()); }
			//extension might be a list~
			if(entry.is_regular_file() &&( entry.path().extension().string() == data._target_extension)) {//todo: file type filter
				printf(KGRN "%s " NONE "sending\n", entry.path().filename().string().c_str());
				
				PostThreadMessage(readerThId, NORMAL_MESSAGE, NULL , (LPARAM)& entry.path());
				//cout << *(std::filesystem::path*)((LPARAM)&entry.path()) << endl; //for Debug
				readerMessageQueueCounter++;
				Sleep(100);//Must be shorter than Sleep() in Reader()
			}
		}
	}
	WaitForSingleObject(hScanEvent, INFINITE); //Wait for Reader to finish work
	PostThreadMessage(readerThId, QUIT_MESSAGE, NULL, NULL);
	if (dir_list != nullptr) {
		while (!dir_list->empty()) { dir_list->pop(); }
		delete dir_list;
		dir_list = nullptr;
	}
	printf(KRED "Scanner Exit\n" NONE);
	ExitThread(0);

}

void Reader(_In_opt_ const Data& data) {//Recieve filenames-->scan their contents-->write results into a file
	printf(KCYN "Reader Enter\n" NONE);

	DWORD dw;
	MSG msg; //Remeber freeing space that you would claim on heap
	std::string line;
	std::filesystem::path filepath;
	std::string str_to_write;
	std::queue <std::string> posList;
	DWORD line_number = 0; 
	BOOL matched = FALSE;
	dw = WaitForSingleObject(hReadEvent, INFINITE);
	if (dw == WAIT_FAILED || dw == WAIT_ABANDONED || dw == WAIT_TIMEOUT) {
		std::cout << std::endl << "Event wait failed...";
		ExitThread(1);
	}
	SetEvent(hScanEvent);//start scanner
	while (GetMessage(&msg, NULL, 0, 0)) {
		if (msg.message == QUIT_MESSAGE) {
			std::cout << std::endl << "The message to exit has been recieved\n";
			break;
		}
		else if(msg.message == NORMAL_MESSAGE) {
			readerMessageQueueCounter--;
			filepath = (*(std::filesystem::path*)msg.lParam);
			printf(KCYN "%s" NONE " recieved\n", filepath.filename().string().c_str());
			
			std::ifstream infile(filepath.string()); //open file to read
			str_to_write = filepath.filename().string() + " "; //assign filename to str_to_write
			while (std::getline(infile, line)) {//Read the file line by line
				//match all substrings
				std::sregex_iterator iter(line.begin(), line.end(), *(data._pattern)), end ;//end is default value
				if (iter != end) {matched = TRUE;}
				while (iter != end) {
					str_to_write.append("(" + std::to_string(line_number) + ", " + std::to_string(iter->position()) + ") ");
					//printf(KMAG " (%d, %ld) " NONE, line_number, iter->position());
					++iter;
				}
				++line_number;
			}
			infile.close();
			line_number = 0; //Reset
			if (matched) {
				PostThreadMessage(writerThId, NORMAL_MESSAGE, NULL, (LPARAM)&str_to_write);
				writerMeesageQueueCounter++;
				matched = FALSE;
			}
			else {
				PostThreadMessage(writerThId, INVALID_MESSAGE, NULL, NULL);
			}
			SetEvent(hWriteEvent);//Notify Writer to go on
			if (readerMessageQueueCounter == 0) {//All message processed
				SetEvent(hScanEvent);//Notify hScanner to send QuitMessage
			}
		}
	}
	WaitForSingleObject(hReadEvent, INFINITE); // Wait for writer to finish work
	PostThreadMessage(writerThId, QUIT_MESSAGE, NULL, NULL);
	printf(KRED "Reader Exit\n" NONE);
	ExitThread(0);
}

void Writer(_Inout_opt_ Data* data) {
	printf(KCYN "Writer Enter\n" NONE);
	SetEvent(hReadEvent);
	DWORD dw;//Remeber freeing space that you would claime on heap
	std::string str_to_write;
	dw = WaitForSingleObject(hWriteEvent, INFINITE);
	if (dw == WAIT_FAILED || dw == WAIT_ABANDONED || dw == WAIT_TIMEOUT) {
		std::cout << std::endl << "Event wait failed...";
		ExitThread(1);
	}
	MSG msg;
	std::ofstream outfile("./output.txt");
	while (GetMessage(&msg, NULL, 0, 0)) {
		if (msg.message == INVALID_MESSAGE) {
			continue;
		}
		else if (msg.message == NORMAL_MESSAGE) {
			printf(KMAG  "Writing..." NONE "\n");
			writerMeesageQueueCounter--;
			str_to_write = *((std::string*)msg.lParam);
			outfile << str_to_write << "\n";
			if (writerMeesageQueueCounter == 0) {
				SetEvent(hReadEvent);
			}
		}
		else if (msg.message == QUIT_MESSAGE) {
			std::cout << std::endl << "The message to exit has been recieved\n";
			break;
		}
		
	}
	outfile.close();
	printf("outcome is written to" KGRN" ./output.txt\n" NONE KRED "Writer Exit\n" NONE);
	ExitThread(0);
}

int main(void) {
	std::string input, dir, target_extension="txt", str_to_find;
	char confirm;
	std::cout << "Search Path(default: \".\\\"): ";
	getline(std::cin, input);
	std::cin.ignore();
	dir = input.empty() ? "" : input;
	std::cout << "Search target_extension:(default: [txt/c/cpp/h/java/md/py...] non format only)";
	getline(std::cin, input);
	target_extension = input.empty() ? "txt" : input;
	std::cout << "Search contents:";
	getline(std::cin, str_to_find);
	if (str_to_find.empty()) { throw std::runtime_error("Search contents cannot be empty! :D"); }
	std::cout << "Case-sensitive?[Y/n]";
	scanf_s("%c", &confirm); 
	BOOL case_sensitive = confirm == 'Y' ? TRUE : FALSE;

	Data data(dir, str_to_find, case_sensitive, target_extension);//data is shared within 3 threads


	//Events and Threads create
	int err;
	hScanEvent = CreateEvent(NULL, TRUE, FALSE, TEXT("ScanfFilenamesEvent"));
	err = GetLastError();
	if (err != 0) {
		std::cout << "Create Event Failed..." << std::endl;
		return EXIT_FAILURE;
	}
	hReadEvent = CreateEvent(NULL, TRUE, FALSE, TEXT("ReadSinglefileEvent"));
	err = GetLastError();
	if (err != 0) {
		std::cout << "Create Event Failed..." << std::endl;
		return EXIT_FAILURE;
	}
	hWriteEvent = CreateEvent(NULL, TRUE, FALSE, TEXT("WriteSinglefileEvent"));
	err = GetLastError();
	if (err != 0) {
		std::cout << "Create Event Failed..." << std::endl;
		return EXIT_FAILURE;
	}
	hScanner = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Scanner, &data, 0, &scannerThId);
	if (err != 0) {
		std::cout << "Create Reader Thread Failed..." << std::endl;
		return EXIT_FAILURE;
	}
	hReader = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Reader, &data, 0, &readerThId);
	if (err != 0) {
		std::cout << "Create Reader Thread Failed..." << std::endl;
		return EXIT_FAILURE;
	}
	hWriter = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Writer, &data, 0, &writerThId);
	if (err != 0) {
		std::cout << "Create Writer Thread Failed..." << std::endl;
		return EXIT_FAILURE;
	}
	//For debug
	SetThreadDescription(hScanner, TEXT("Sacnner()"));
	SetThreadDescription(hReader, TEXT("Reader()"));
	SetThreadDescription(hWriter, TEXT("Writer()"));

	//Threads start order: hWriter-->hReader-->hScanner
	//Threads end order: hScanner-->hReader-->hWriter
	HANDLE hArr[hSize] = {hScanner,hReader, hWriter, hScanEvent, hReadEvent, hWriteEvent};
	WaitForMultipleObjects(hSize, hArr, TRUE, INFINITE);

	for (int i = 0; i < hSize; i++) {
		CloseHandle(hArr[i]);
	}

	return EXIT_SUCCESS;
}