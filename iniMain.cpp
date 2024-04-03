#include "IniFile.h"
using namespace std;
int main() {
    IniFile ini("config.ini");
    bool fs = ini.readBool("Window", "fullscreen", false);
    int uiScale = ini.readInt("Window", "UIScale", 1);
    cout << fs << endl;
    return 0;
}