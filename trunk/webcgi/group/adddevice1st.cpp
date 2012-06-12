#include "adddevice1st.h"

#include "../../opens/libwt/WPushButton"
#include "../../opens/libwt/WScrollArea"
#include "../../opens/libwt/WebSession.h"

#include "../../kennel/svdb/svapi/svapi.h"

#include "resstring.h"

extern void PrintDebugString(const char * szMsg);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
SVDeviceList::SVDeviceList(WContainerWidget * parent,string szIDCUser, string szIDCPwd):
WTable(parent)
{
    setStyleClass("t5");        // 样式表    
    m_pContentTable = NULL;     // 内容表
    m_pSubContent= NULL;        // 子内容表
    m_szIDCUser = szIDCUser;    // 
    m_szIDCPwd = szIDCPwd;      //
    initForm();                 // 初始化页面
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 initForm
// 说明 初始化
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDeviceList::initForm()
{
    connect(&m_DeviceMap, SIGNAL(mapped(const std::string)), this, SLOT(addDevice(const std::string)));
    createTitle();
    if(m_pSubContent)
    {
        m_pSubContent->setStyleClass("t8");
        enumDeviceGroup();
    }
    createOperate();   
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 createTitle
// 说明 创建标题栏
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDeviceList::createTitle()
{
    // 得到当前行
    int nRow = numRows();
    // 引入 basic.js 文件
	new WText("<SCRIPT language='JavaScript' src='/basic.js'></SCRIPT>",elementAt(nRow, 0));

	nRow ++;
    // 标题栏文字
    WText *pTitle = new WText(SVResString::getResString("IDS_Add_Device_Title"), (WContainerWidget*)elementAt(nRow, 0));
    elementAt(nRow, 0)->setStyleClass("t1title");

	// 根据是否是翻版本决定是否创建 翻译和刷新按钮
    int bTrans = GetIniFileInt("translate", "translate", 0, "general.ini");
	if(bTrans == 1)
	{ // 创建 翻译 按钮
        new WText("&nbsp;&nbsp;&nbsp;&nbsp;", (WContainerWidget *)elementAt(nRow, 0));
	    m_pTranslateBtn = new WPushButton(SVResString::getResString("IDS_Translate"), (WContainerWidget *)elementAt(nRow, 0));
	    if(m_pTranslateBtn)
	    {
		    connect(m_pTranslateBtn, SIGNAL(clicked()), this, SLOT(Translate()));	
		    m_pTranslateBtn->setToolTip(SVResString::getResString("IDS_Translate_Tip"));
        }
	}

    // 创建内容表
    nRow ++;
    m_pContentTable = new WTable(elementAt(nRow,0));	
    if(m_pContentTable)
    {
        m_pContentTable->setCellPadding(0);
        m_pContentTable->setCellSpaceing(0);

        // 滚动区
        WScrollArea * pScrollArea = new WScrollArea(elementAt(nRow,0));
        if(pScrollArea)
        {
            pScrollArea->setStyleClass("t5"); 
            pScrollArea->setWidget(m_pContentTable);
        }
        m_pContentTable->setStyleClass("t5"); 
        elementAt(nRow, 0)->setStyleClass("t7");

        // 创建子内容表
        nRow = m_pContentTable->numRows();
        m_pSubContent = new WTable((WContainerWidget*)m_pContentTable->elementAt(nRow, 0));
        m_pContentTable->elementAt(nRow, 0)->setContentAlignment(AlignTop);
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 Translate
// 说明 显示翻译界面
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDeviceList::Translate()
{
    // 
	WebSession::js_af_up = "showTranslate('";
	WebSession::js_af_up += "groupRes";
	WebSession::js_af_up += "')";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 addDeviceByID
// 说明 根据设备模板的名称枚举参数并添加此设备模板到指定表内
// 参数
//      szDeviceID，设备模板的名称
//      pTable， 存放参数的表格指针
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDeviceList::addDeviceByID(string &szDeviceID, SVShowTable *pTable)
{
    // 得到 设备模板入口点
    OBJECT objDevice = GetEntityTemplet(szDeviceID, m_szIDCUser, m_szIDCPwd);
    if(objDevice != INVALID_VALUE)
    {
        MAPNODE node = GetEntityTempletMainAttribNode(objDevice);
        if(node != INVALID_VALUE)
        {
            string szLabel(""), szName(""), szHidden("");
            if(FindNodeValue(node, "sv_description", szLabel))      // 说明
                szLabel = SVResString::getResString(szLabel.c_str());

            if(!FindNodeValue(node, "sv_label", szName))
                FindNodeValue(node, "sv_name", szName);             // 名称
            else
                szName = SVResString::getResString(szName.c_str());

            FindNodeValue(node, "sv_hidden", szHidden);             // 是否隐藏
            if(szHidden != "true")
            {
                WTable * pSub = pTable->createSubTable();           // 创建子表
                if(pSub)
                {
                    // 得到当前行
                    int nSubRow = pSub->numRows();
                    if(!szName.empty())
                    {
                        // 创建 文本（模板的名称）
                        WText *pName = new WText(szName, (WContainerWidget*)pSub->elementAt(nSubRow, 0));
                        if(pName)
                        {
                            connect(pName, SIGNAL(clicked()), "showbar();" ,  &m_DeviceMap, SLOT(map()) , WObject::ConnectionType::JAVASCRIPTDYNAMIC);
                            m_DeviceMap.setMapping(pName, szDeviceID.c_str());
                            // 样式表（颜色：#669 ）
                            sprintf(pName->contextmenu_, "style='color:#669;cursor:pointer;' onmouseover='" \
                                "this.style.textDecoration=\"underline\"' " \
                                "onmouseout='this.style.textDecoration=\"none\"'");
                            pName->setToolTip(szLabel);
                        }
                        pSub->elementAt(nSubRow, 0)->setStyleClass("cell_40");
                        new WText(szLabel, (WContainerWidget*)pSub->elementAt(nSubRow, 1));
                    }
                }
            }
        }
        // 关闭设备模板
        CloseEntityTemplet(objDevice);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 enumDeviceGroup
// 说明 枚举所有设备组
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDeviceList::enumDeviceGroup()
{
    PAIRLIST lsDGName;
    PAIRLIST::iterator lsItem;

    map<int, string, less<int> > mapET;
    map<int, string, less<int> > mapETGroup;
    map<int, string, less<int> >::iterator mapETItem;
    map<int, string, less<int> >::iterator mapItem;

    // 得到所有的设备组
    if(GetAllEntityGroups(lsDGName, "sv_label", m_szIDCUser, m_szIDCPwd) || 
        GetAllEntityGroups(lsDGName, "sv_name", m_szIDCUser, m_szIDCPwd))
    {// 成功
        list<string> lsDevice;
        list<string>::iterator lstItem;
        string szHidden(""), szIndex("");
        for(lsItem = lsDGName.begin(); lsItem != lsDGName.end(); lsItem ++)
        {// 枚举每一个设备组
            string szValue = SVResString::getResString((*lsItem).value.c_str());
            string szID = (*lsItem).name;
            // 打开设备组
            OBJECT objDG = GetEntityGroup(szID, m_szIDCUser, m_szIDCPwd);
            if(objDG != INVALID_VALUE)
            {// 打开设备组成功
                // 得到 Main MAPNODE
                szHidden = "";
                szIndex = "";
                MAPNODE node = GetEntityGroupMainAttribNode(objDG);
                if(node != INVALID_VALUE)
                {
                    FindNodeValue(node, "sv_hidden", szHidden); // 是否隐藏
                    FindNodeValue(node, "sv_index", szIndex);   // 显示索引
                }
                if(szHidden != "true")
                {// 不是隐藏组
                    if(!szIndex.empty())
                    {// 显示顺序已定义
                        mapETGroup[atoi(szIndex.c_str())] = szID;
                    }
                    else
                    {// 显示顺序未定义
                        // 得到 子内容表当前行数
                        int nRow = m_pSubContent->numRows();
                        // 创建隐藏/显示功能表
                        SVShowTable * pTable = new SVShowTable((WContainerWidget*)m_pSubContent->elementAt(nRow, 0));
                        if(pTable)
                        {// 创建带隐藏/显示功能表成功
                            // 设置此表标题
                            if(!szValue.empty())
                                pTable->setTitle(szValue.c_str());
                            else
                                pTable->setTitle(szID.c_str());
                            
                            // 清理 设备模板 列表
                            lsDevice.clear();
                            if(GetSubEntityTempletIDByEG(lsDevice, objDG))
                            {// 
                                for(lstItem = lsDevice.begin(); lstItem != lsDevice.end(); lstItem ++)
                                {// 枚举每一个设备模板
                                    string szDeviceID = (*lstItem).c_str(); 
                                    addDeviceByID(szDeviceID, pTable);
                                }
                            }
                            // 隐藏此表的子表
                            pTable->HideSubTable();
                        }
                    }
                }
                // 关闭设备模板组
                CloseEntityGroup(objDG);
            }
        }
        string szName("");
        // 根据显示顺序 创建设备组表
        for(mapItem = mapETGroup.begin(); mapItem != mapETGroup.end(); mapItem ++)
        {
            OBJECT objDG = GetEntityGroup(mapItem->second, m_szIDCUser, m_szIDCPwd);
            if(objDG != INVALID_VALUE)
            {
                MAPNODE node = GetEntityGroupMainAttribNode(objDG);
                if(node != INVALID_VALUE)
                {
                    szName = ("");
                    if(!FindNodeValue(node, "sv_label", szName))
                        FindNodeValue(node, "sv_name", szName);
                    else
                        szName = SVResString::getResString(szName.c_str());
                    int nRow = m_pSubContent->numRows();
                    SVShowTable * pTable = new SVShowTable((WContainerWidget*)m_pSubContent->elementAt(nRow, 0));
                    if(pTable)
                    {
                        pTable->setTitle(szName.c_str());
                        lsDevice.clear();
                        if(GetSubEntityTempletIDByEG(lsDevice, objDG))
                        {
                            for(lstItem = lsDevice.begin(); lstItem != lsDevice.end(); lstItem ++)
                            {
                                string szDeviceID = (*lstItem).c_str();
                                addDeviceByID(szDeviceID, pTable);
                            }
                        }
                        pTable->HideSubTable();
                    }
                }
                CloseEntityGroup(objDG);
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 addDevice
// 说明 根据选定设备类型添加设备
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDeviceList::addDevice(const std::string szIndex)
{
    // 触发 添加设备 事件
    emit AddNewDevice(szIndex);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 createOperate
// 说明 创建操作按钮
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDeviceList::createOperate()
{
    // 得到当前行数
    int nRow = numRows();
    // 创建新的按钮
    WPushButton * pCancel = new WPushButton(SVResString::getResString("IDS_Cancel_Add"), (WContainerWidget*)elementAt(nRow, 0));
    if(pCancel)
    {
        // 绑定 click 事件
        pCancel->setToolTip(SVResString::getResString("IDS_Cancel_Add_Device_Tip"));
        WObject::connect(pCancel, SIGNAL(clicked()), "showbar();", this, SLOT(cancel()), WObject::ConnectionType::JAVASCRIPTDYNAMIC);
    }
    elementAt(nRow, 0)->setContentAlignment(AlignBottom | AlignCenter);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 cancel
// 说明 取消添加并返回主页面
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SVDeviceList::cancel()
{
    emit backPreview();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// end file