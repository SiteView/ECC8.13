#ifndef _SiteView_Ecc_POP_MENU_H_
#define _SiteView_Ecc_POP_MENU_H_

#include <string>

using namespace std;

// �Ҽ������˵�
class CEccPopMenu
{
public:
    CEccPopMenu();              // ���캯��
    ~CEccPopMenu();             // ��������
    const string ShowMenu();    // �õ��Ҽ��˵�����
private:
    string m_szMenu;            // �Ҽ��˵�
};


#endif