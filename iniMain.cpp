// #include "IniFile.h"
#include <string>
#include <iostream>


using namespace std;

void cleanupStr(std::string& str) {
	size_t end = str.find(';');
	if (end != string::npos) {
		str = str.substr(0, end);
	}
}
int main() {
    string str = "new rome asdfasdf";
    cleanupStr(str);
    cout << str << endl;
}