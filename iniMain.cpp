#include "IniFile.h"
using namespace std;
int main() {
    IniFile ini("config.ini");
    bool fs = ini.readBool("Window", "fullscreen", false);
    ini.writeInt("Window", "UIScale",3);
    int uiScale = ini.readInt("Window", "UIScale", 1);
    cout << fs << endl;
    return 0;
}