_Tips: The more files in the directory and the smaller each file, the faster the program runs._

Project: ContentSearch(ContentSearch.cpp ContentSearch.h)

Input: 
>the directory and string to be scanned, such as C:\TestDir, "abcd", that is,scan all TestDir files in the C: drive to see if there is "abcd" string.

Output:
> matching filenames, offsets, and a file containing multiple duplicate strings need to be reported in full.

### It creates 3 extra threads besides the main thread:{Scanner, Reader, Writer}

* Scanner`hScanner`: To scan all files which satisfy the user-customized file extension in the targeting directory and its subdirectories(implemented by `std::queue`) and send their path info to `hReader`(implemented by `PostThreadMessage`).

* Reader`hReader`: To accept the message from `hScanner` and match its contents with the string user is searching for. Mark the position as a string then send all position info in a file to `hWritter`.

* Writer `hWriter`: To accept the message from `hReader` and print them into a file (`ofstream`).

***
## Multithreading:
Threads start order: hWriter-->hReader-->hScanner
Threads end order: hScanner-->hReader-->hWriter
Scanning filenames and writing position info into a file both are asynchronous, which's controlled by Event Kernel Object's signals. 

Scanner: 
1. Waits for Reader to initialize at the beginning (Scanner: "May I start to work?" Reader: "Nah, I'm not ready yet")
2. After receiving `hScanEvent` signal from Reader, waits for sending `QUIT_MESSAGE` to Reader at the end. 
(Scanner: "Should I release my resource and leave?" Reader: "Hang on, lots of work to do"
...
Reader: "I finish my work! I'll meet you at the main thread hall" Scanner: "Well done. After you~")


Reader:
1. Waits for Writer to initialize at the beginning 
(Reader: "Shall I start my work and notify Scanner? " Writer: "One sec." ... Writer: "Good to go" Reader: "Copy, this is Reader. Scanner, you're ready for departure")
2. Waits for Scanner to send messages(`PostThreadMessage`) with files path info (Scanner: "Here's your task..." Reader: "Alright, I'll get it done")
3. Waits for Writer's `QUIT_MESSAGE` to exit thread also send  `QUIT_MESSAGE` to Scanner
(Reader: "Scanner is waiting... Before you exit, let me know~
...
Writer: "Job's done. Exfil to main thread basement"
Reader: "I got your six, Scanner, cover me"
)

Writer:
1. Waits for Reader's messages to write position info into a file. Exit thread when Reader sends `QUIT_MESSAGE`.
(Writer: "Writer stand by, waiting for your order, Reader"
...
Reader: "Bravo Zulu. Writer, take us back home"
Writer: "This is Writer. Exfil in 3, 2, 1...")

> Just for fun and better understanding :)
***

**Attention**: For now, it only supports non-format files like `txt/md/c/cpp/h/java/python` file(aka. all non format text files). The "Demo" and "Auxilary" folders only for example learning.


> Thanks to Varteta Learning Platform tutorials on Youtube https://www.youtube.com/channel/UC7-Ourn_kpT-EnvVoCxTgsw
