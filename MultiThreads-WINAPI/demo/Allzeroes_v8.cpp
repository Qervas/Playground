#include<iostream>
#include<Windows.h>
using std::cout;
using std::endl;
using std::cin;
/*Close "Calculator" program*/

int main(void) {
	HWND h = FindWindow(NULL, TEXT("Calculator"));
	char ch = 'N';
	if (h != NULL) {
		cout << endl << "Do you want to close the calculator?";
		cin >> ch;
	}
	else {
		cout << endl << "No calculator window opened";
		exit(0);
	}
	if (ch == 'Y') {
		SendMessage(h, WM_CLOSE, 0,0);
	}
	return 0;
}
