#ifndef _SiteView_Ecc_POP_MENU_H_
#define _SiteView_Ecc_POP_MENU_H_

#include <string>

using namespace std;

// 右键弹出菜单
class CEccPopMenu
{
public:
    CEccPopMenu();              // 构造函数
    ~CEccPopMenu();             // 析构函数
    const string ShowMenu();    // 得到右键菜单文字
private:
    string m_szMenu;            // 右键菜单
};


#endif