#ifndef _SV_POP_MENU_H_
#define _SV_POP_MENU_H_

#include <string>

using namespace std;

class CSVPopMenu
{
public:
    CSVPopMenu();
    ~CSVPopMenu();
    const string ShowMenu();
private:
    string m_szMenu;
};


#endif