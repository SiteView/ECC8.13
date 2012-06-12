/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// adddevice3rd.cpp
// 添加设备的第三步，快速添加监测器
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "adddevice3rd.h"
#include "resstring.h"
#include "mainview.h"
#include "treeview.h"
#include "rightview.h"
#include "basefunc.h"
#include "debuginfor.h"
#include "basedefine.h"
#include "eccobjfunc.h"
#include "listtable.h"

#include "../../opens/libwt/WebSession.h"
#include "../../opens/libwt/WScrollArea"
#include "../../opens/libwt/WPushButton"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WCheckBox"
#include "../../opens/libwt/WLabel"
#include "../../opens/libwt/WImage"
#include "../../opens/libwt/WText"

#include "../userright/User.h"

#include "../base/OperateLog.h"

typedef bool(ListDevice)(const char* szQuery, char* szReturn, int &nSize);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 构造函数
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
CEccAddDevice3rd::CEccAddDevice3rd(WContainerWidget *parent):
CEccBaseTable(parent),
m_pSave(NULL),
m_pHideButton(NULL)
{
    setStyleClass("panel");
    initForm(false);

    connect(&m_mapMinitor, SIGNAL(mapped(int)), this, SLOT(selAllByMonitorType(int)));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 析构函数
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
CEccAddDevice3rd::~CEccAddDevice3rd()
{
    removeMapping();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 初始化
// 参数
//      是否创建帮助按钮
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice3rd::initForm(bool bHasHelp)
{
    // 基类初始化
    CEccBaseTable::createTitle(bHasHelp);
    // 设置标题栏文字
    if(m_pTitle)
        m_pTitle->setText(SVResString::getResString("IDS_Quick_Add"));

    int nRow = numRows();

    // 内容
    WTable *pSub = new WTable(elementAt(nRow, 0));
    elementAt(nRow, 0)->setStyleClass("height95p");
    if(pSub)
    {
        pSub->setStyleClass("panel");
        // 滚动区
        WScrollArea *pScroll = new WScrollArea(elementAt(nRow, 0));
        if(pScroll)
        {
            pScroll->setWidget(pSub);
            pScroll->setStyleClass("panel");
        }

        // 实际数据表
        CEccListTable *pSubList = new CEccListTable(pSub->elementAt(0, 0), false, false, false, false);
        if(pSubList)
        {
            // 设置标题
            pSubList->setTitle(SVResString::getResString("IDS_Quick_Add"));
            m_pContent = pSubList->getListTable();
        }
        // 对齐方式
        pSub->elementAt(0, 0)->setContentAlignment(AlignTop);
    }

    // 创建操作
    createOperate();
    // 创建隐藏按钮
    createHideButton();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 创建操作
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice3rd::createOperate()
{
    int nRow = numRows();
    m_pOperate = new WTable(elementAt(nRow, 0));
    if(m_pOperate)
    {
        m_pOperate->setStyleClass("widthauto");
        int nRow = m_pOperate->numRows();
        // 保存
        m_pSave = new CEccImportButton(SVResString::getResString("IDS_Add"), SVResString::getResString("IDS_Save_Sel_Monitor_Tip"),
            "", m_pOperate->elementAt(nRow, 0));
        if(m_pSave)
        {
            WObject::connect(m_pSave, SIGNAL(clicked()), "showbar()", this, SLOT(saveAllSelMonitors()),
                WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        }

        new WText("&nbsp;", m_pOperate->elementAt(nRow, 1));

        // 取消
        CEccButton *pCancel = new CEccButton(SVResString::getResString("IDS_Cancel"), SVResString::getResString("IDS_Cancel_Add_Monitor_Tip"),
            "", m_pOperate->elementAt(nRow, 2));
        if(pCancel)
        {
            WObject::connect(pCancel, SIGNAL(clicked()), "showbar();", this, SLOT(Cancel()),
                WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        }

        // 设置对齐方式
        nRow = static_cast<WTableCell*>(m_pOperate->parent())->row();
        elementAt(nRow, 0)->setContentAlignment(AlignBottom | AlignCenter);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 创建隐藏按钮
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice3rd::createHideButton()
{
    int nRow = numRows();
    m_pHideButton = new WPushButton("", elementAt(nRow, 0));
    if(m_pHideButton)
    {
        m_pHideButton->hide();
        WObject::connect(m_pHideButton, SIGNAL(clicked()), "showbar();", this, SLOT(EnumDynData()), 
            WObject::ConnectionType::JAVASCRIPTDYNAMIC);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 取消添加监测器
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice3rd::Cancel()
{
    // 显示新添加的设备
    CEccMainView::m_pRightView->showNewDevice(m_szDeviceID);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 保存全部选择的监测器
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice3rd::saveAllSelMonitors()
{
    unsigned long ulStart = GetTickCount();

	string strQuickAddMonitorName("");
    irow it;
    int nPos = 0;
    // 枚举每一条数据
    for(it = m_svValueList.begin(); it != m_svValueList.end(); it ++)
    {
        // 当前数据是否被选择
        SVTableCell *pCell =  (*it).second.Cell(0);
        if(pCell && pCell->Type() == adCheckBox)
        {
            string szText = ((WCheckBox*)pCell->Value())->label()->text();
            nPos = static_cast<int>(szText.find(SVResString::getResString("IDS_Monitor_Point_Lack_Tip")));
            if(nPos >= 0)
                szText = szText.substr(0, nPos);

            ((WCheckBox*)pCell->Value())->label()->setText(szText);
            if(((WCheckBox*)pCell->Value())->isChecked())
            {// 选择状态
                string szLable = ((WCheckBox*)pCell->Value())->label()->text();
                // 保存监测器
                if(!saveMonitor((*it).second.getTag(),(*it).second.getProperty(), pCell->Property(), szLable.c_str()))
                {// 保存失败， 显示错误信息
                    ((WCheckBox*)pCell->Value())->label()->setText(((WCheckBox*)pCell->Value())->label()->text() + 
                        SVResString::getResString("IDS_Monitor_Point_Lack_Tip"));
                    ((WCheckBox*)pCell->Value())->label()->setStyleClass("table_data_input_error");
                    return;
				}
            }
        }
    }
    CEccMainView::m_pRightView->showNewDevice(m_szDeviceID);

    InsertHitRecord(CEccTreeView::m_SVSEUser.getUserID(), "treeview", "CEccAddDevice3rd.saveAllSelMonitors", SVResString::getResString("IDS_Save_Sel_Monitor_Tip"), 
        0, 0);

    InsertHitRecord(CEccTreeView::m_SVSEUser.getUserID(), "treeview", "CEccAddDevice3rd.saveAllSelMonitors", SVResString::getResString("IDS_Save_Sel_Monitor_Tip"), 
        0, GetTickCount() - ulStart);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 枚举动态参数
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice3rd::EnumDynData()
{
    // 枚举每个监测器模板
    list<monitor_templet>::iterator lstItem;
    for(lstItem = m_lsMonitorTemplet.begin(); lstItem != m_lsMonitorTemplet.end(); lstItem ++)
    {      
        char szTpl [32] = {0};
        // 配置动态调用参数
        int nLen = sprintf(szTpl, "_TemplateID=%d&", (*lstItem).nMonitorID);
        string szQuery(szTpl);
        szQuery += m_szRunParam;

        int nSize = static_cast<int>(szQuery.length()) + 2;
        char *pszQueryString = new char[nSize];
        if(pszQueryString)
        { 
            memset(pszQueryString, 0 , nSize);
            strcpy(pszQueryString , szQuery.c_str());
            PrintDebugString(pszQueryString);
            char *pPos = pszQueryString;
            while((*pPos) != '\0' )
            {
                if((*pPos) == '&')
                    (*pPos) = '\0';
                pPos ++;
            }
            if((*lstItem).pTable)
            {
                (*lstItem).pTable->clear();
                AddDynData((*lstItem).pTable, pszQueryString,  nSize, (*lstItem).nMonitorID, (*lstItem).szDllName, 
                    (*lstItem).szFuncName, (*lstItem).szSaveName, (*lstItem).bSel);
            }
            delete []pszQueryString;
        } 
    }

    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 快速添加
// 参数
//      设备ID
//      设备名称
//      运行参数
//      快速添加监测器列表
//      缺省选择的监测器列表
//      设备是否是网络设备
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice3rd::QuickAdd(string szDeviceId, string szDevName, string szRunParam, string szQuickAdd, 
                                string szQuickAddSel, string szNetworkset)
{
    bool bHasDyn = false;

    removeMapping();

    if(m_pContent)
       m_pContent->clear();

    m_lsMonitorTemplet.clear();
    m_svValueList.clear();

    m_szDeviceID = szDeviceId;
    m_szNetworkSet = szNetworkset;
    m_szDevName = szDevName;
    m_szRunParam = szRunParam.substr(0, szRunParam.length() - 1);

    list<string> lstMonitors;
    // 解析成功
    if(sv_split(szQuickAdd.c_str(), ",", lstMonitors, false) > 0)
    {
        list<string>::iterator lstItem;
        int nPos = 0;
        bool bSelect;
        // 枚举每一监测器模板
        for(lstItem = lstMonitors.begin(); lstItem != lstMonitors.end(); lstItem ++)
        {
            // 缺省是否选择
			bSelect = false;
			nPos = static_cast<int>(szQuickAddSel.find((*lstItem).c_str()));
			if(nPos >= 0)
			{
				const char *pValue = szQuickAddSel.c_str();
				if( *(pValue + nPos +(*lstItem).length()) == ',' || *(pValue + nPos +(*lstItem).length()) == '\0')
					bSelect = true;
			}

            // 根据监测器模板ID枚举重要属性并进行记录
            int nMonitorID = atoi((*lstItem).c_str());
            OBJECT objMonitor = GetMonitorTemplet(nMonitorID, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
            if(objMonitor != INVALID_VALUE)
            {
                MAPNODE node = GetMTMainAttribNode(objMonitor);
                monitor_templet monitor;
                monitor.nMonitorID = nMonitorID;
				monitor.bSel = bSelect;
                // 名称 描述 扩展动态库（枚举动态数据使用，缺省使用sv_dll）
                // 扩展函数明
                // 扩展保存
                if(!FindNodeValue(node, svLabel, monitor.szName))
                    FindNodeValue(node, svName, monitor.szName);
                else
                    monitor.szName = SVResString::getResString(monitor.szName.c_str());

                if(FindNodeValue(node, svDescription, monitor.szLabel))
                    monitor.szLabel = SVResString::getResString(monitor.szLabel.c_str());

                FindNodeValue(node, svExtraDll, monitor.szDllName);
                if(monitor.szDllName.empty())
                    FindNodeValue(node, svDLL, monitor.szDllName);
                FindNodeValue(node, svExtraFunc, monitor.szFuncName);
                FindNodeValue(node, svExtraSave, monitor.szSaveName);
                list<monitor_templet>::iterator lstItem;
                // 子内容表是否成功创建
                if(m_pContent)
                {
                    // 子内容表的当前行数
                    int nRow = m_pContent->numRows();
                    WCheckBox *pCheck = NULL;
                    // 是否需要使用动态数据
                    if(!monitor.szDllName.empty() && !monitor.szFuncName.empty())
                    {// 需要
                        bHasDyn = true;
                        // 创建全选 checkbox
                        WCheckBox* pSelAll = new WCheckBox(monitor.szLabel, m_pContent->elementAt(nRow, 0));
                        if(pSelAll)
                        {
                            pSelAll->label()->setStyleClass("tgrouptitle2");
                            // tooltip
                            pSelAll->setToolTip(SVResString::getResString("IDS_All_Select"));
                            // 是否选择
                            pSelAll->setChecked(bSelect);
                            // 绑定 click
                            WObject::connect(pSelAll, SIGNAL(clicked()), "showbar();", &m_mapMinitor, SLOT(map()), 
                                WObject::ConnectionType::JAVASCRIPTDYNAMIC);

                            m_mapMinitor.setMapping(pSelAll, nMonitorID);
                            m_lsCkMT.push_back(pSelAll);
                        }
                        m_pContent->elementAt(nRow, 0)->setStyleClass("padding_top");
                        m_pContent->GetRow(nRow)->setStyleClass("table_data_input_rows");

                        nRow ++;
                        // 扩展保存属性参数名称是否为空
                        if(monitor.szSaveName.empty())
                        {
                            // 显示错误信息
                            new WText(SVResString::getResString("IDS_Monitor_Templet_Error"), m_pContent->elementAt(nRow, 0));
                        }
                        else
                        {
                            // 创建子表以便能放置动态数据
                            monitor.pTable = new WTable(m_pContent->elementAt(nRow, 0));
                            if(monitor.pTable)
                            {
                                new WText("loading...", monitor.pTable->elementAt(0, 0));
                            }
                        }
                        m_pContent->elementAt(nRow, 0)->setStyleClass("padding_4");
                    }
                    else
                    {
                        // 监测描述文本
                        WText *pName = new WText(monitor.szLabel, m_pContent->elementAt(nRow, 0));
                        if(pName)
                            pName->setStyleClass("tgrouptitle2");
                        // 设置此行的显示样式表
                        m_pContent->elementAt(nRow, 0)->setStyleClass("padding_top");
                        m_pContent->GetRow(nRow)->setStyleClass("table_data_input_rows");

                        nRow ++;
                        // 在下一行内创建显示文字为监测器描述文字的checkbox
                        pCheck = new WCheckBox(monitor.szName, m_pContent->elementAt(nRow, 0));
                        m_pContent->elementAt(nRow, 0)->setStyleClass("padding_4");
                    }

                    nRow ++;
                    new WImage("../Images/space.gif", m_pContent->elementAt(nRow, 0));
                    m_pContent->elementAt(nRow, 0)->setStyleClass("table_data_input_space");

                    if(pCheck)
                    {// 创建成功
                        // 是否选择
						pCheck->setChecked(bSelect);
                        char szIndex[32] = {0};
                        sprintf(szIndex, "%d", nMonitorID);
                        SVTableCell svCell;
                        svCell.setType(adCheckBox);
                        svCell.setValue(pCheck);
                        // 记录
                        m_svValueList.WriteCell((nRow + 1) * 10, 0, svCell);
                        SVTableRow *pRow = m_svValueList.Row((nRow + 1) * 10);
                        if (pRow)
                            pRow->setTag(nMonitorID);
                    }
                }
                m_lsMonitorTemplet.push_back(monitor);

                CloseMonitorTemplet(objMonitor);
            }
        }
    }

    string szCmd = "hiddenbar();";
    if(bHasDyn && m_pHideButton)
    {
        if(!m_pHideButton->getEncodeCmd("xclicked()").empty())
            szCmd = "update('" + m_pHideButton->getEncodeCmd("xclicked()") + "');";
    }
    WebSession::js_af_up = szCmd;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 根据监测器模板索引全部选择枚举出来的此类监测器
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice3rd::selAllByMonitorType(int nMTID)
{
    bool bSel = true;
    WCheckBox* pSelAll = reinterpret_cast<WCheckBox*>(m_mapMinitor.mapping(nMTID));
    if(pSelAll)
        bSel = pSelAll->isChecked();

    irow it;
    for(it = m_svValueList.begin(); it != m_svValueList.end(); it ++)
    {
        if((*it).second.getTag() == nMTID)
        {
            SVTableCell *pCell =  (*it).second.Cell(0);
            if(pCell && pCell->Type() == adCheckBox)
                ((WCheckBox*)pCell->Value())->setChecked(bSel);
        }
    }
    WebSession::js_af_up = "hiddenbar();";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 AddDynData
// 说明 增加显示动态数据
// 参数
//      增加动态参数的表格
//      运行参数
//      运行参数大小
//      监测器模板ID
//      动态连接库名称
//      函数名称
//      存储名称
//      缺省是否选择
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice3rd::AddDynData(WTable * pTable, const char* pszQuery, const int &nQuerySize, const int &nMonitorID, 
                            const string &szDllName, const string &szFuncName, const string &szSaveName, const bool &bSel)
{
// 是否是在Windows 平台下运行
    bool bGetDyn = false;
    char szReturn [svBufferSize] = {0};
    int nSize = sizeof(szReturn);

    if(FindSEID(m_szDeviceID) == "1")
    {
#ifdef WIN32
    string szDllName(makeDllName(szDllName));
    string szMsg = "Dll Name: " + szDllName + " Function Name: " + szFuncName;
    PrintDebugString(szMsg.c_str());
    // 打开动态链接库
    HINSTANCE hDll = LoadLibrary(szDllName.c_str());
    if (hDll)
    {
        // 获得函数
        ListDevice* func = (ListDevice*)GetProcAddress(hDll, szFuncName.c_str());
        if (func && szReturn)
        {
            bGetDyn = (*func)(pszQuery, szReturn, nSize);
        }
        // 关闭动态链接库
        FreeLibrary(hDll);
    }
#else
#endif
    }
    else
    {
        bGetDyn = ReadWriteDynQueue(m_szDeviceID, szDllName, szFuncName, pszQuery, nQuerySize, szReturn, nSize);
    }

    if(bGetDyn)
    {
        int nRow = pTable->numRows();
        char *pos = strstr(szReturn, "error");
        if(pos == NULL)
        {
            pos = szReturn;
            map<string , string, less<string> > dynData;
            while(*pos != '\0')
            {
                int nSize = static_cast<int>(strlen(pos));
                char *pPosition = strchr(pos, '=');
                if(pPosition)
                {
                    (*pPosition) = '\0';
                    ++pPosition;
                    dynData[pPosition] = pos;
                }
                pos = pos + nSize + 1;
            }
            
            // 为每一个动态数据创建一行
            int nParentRow = nMonitorID * 10;
            map<string , string, less<string> >::iterator it;
            for(it = dynData.begin(); it != dynData.end(); it++)
            {
                WCheckBox *pCheck = new WCheckBox(it->first, pTable->elementAt(nRow, 0));
                if(pCheck)
                {
					pCheck->setChecked(bSel);
                    SVTableCell svCell;
                    svCell.setType(adCheckBox);
                    svCell.setValue(pCheck);
                    svCell.setProperty(it->second.c_str());
                    m_svValueList.WriteCell(nParentRow + nRow, 0, svCell);
                    SVTableRow *pRow = m_svValueList.Row(nParentRow + nRow);
                    if (pRow)
                    {
                        pRow->setProperty(szSaveName.c_str());
                        pRow->setTag(nMonitorID);
                    }
                }
                nRow ++;
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 saveMonitor
// 说明 保存监测器
// 参数
//      监测模板ID
//      动态参数的存储名称
//      扩展参数值
//      扩展参数显示文字
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CEccAddDevice3rd::saveMonitor(int nMonitorID, const char* pszSaveName, const char *pszExtraParam, 
                                   const char *pszExtraLable)
{
    CEccTreeDevice *pDevice = NULL;
    const CEccTreeNode *pNode = CEccMainView::m_pTreeView->getECCObject(m_szDeviceID);
    if(pNode)
        pDevice = static_cast<CEccTreeDevice*>(const_cast<CEccTreeNode*>(pNode));
    // 创建监测器
    OBJECT objMonitor = CreateMonitor();
    // 打开监测器模板
    OBJECT objMonitorTmp = GetMonitorTemplet(nMonitorID, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
    if(objMonitor != INVALID_VALUE && objMonitorTmp != INVALID_VALUE)
    {// 创建监测器和打开模板都成功
        string szMonitroName("");
        // 得到监测器模板主节点
        MAPNODE mainnode = GetMonitorMainAttribNode(objMonitor);
        // 得到监测器主节点
        MAPNODE nodeTmp  = GetMTMainAttribNode(objMonitorTmp);
        if(mainnode != INVALID_VALUE && nodeTmp != INVALID_VALUE)
        {
            char chMTID [8] = {0};
            string szLabel (""), szPoint ("");;
            string szMonitorName ("");
            if(!FindNodeValue(nodeTmp, svLabel, szMonitorName))
                FindNodeValue(nodeTmp, svName, szMonitorName);
            else
               szMonitorName  = SVResString::getResString(szMonitorName.c_str());
            if(m_szNetworkSet != "true")
            {// 不是网络设备
                FindNodeValue(nodeTmp, svIntPos, szPoint);
                
                if(szPoint.empty())
                    szPoint = "1";
                // 已用监测器点数
                int nMonitorCount = getUsingMonitorCount();

                int nPoint = atoi(szPoint.c_str());
                if(nPoint <= 0)
                    nPoint = 0;
                nMonitorCount += nPoint;
                // 检测是否超点
                if(!checkMonitorsPoint(nMonitorCount))
                {
                    WebSession::js_af_up = "showMonitorCountErr('" + SVResString::getResString("IDS_PointPoor") + "','" +
                        SVResString::getResString("IDS_Affirm") + "');hiddenbar();";
                    return false;
                }
            }
            else
            {// 网络设备
                // 已用网络设备
                // 网络设备已用点数
                int nNetworkCount = getUsingNetworkCount(m_szDeviceID);
                // 检测是否超点
                if(!checkNetworkPoint(nNetworkCount))
                {
                    WebSession::js_af_up = "showMonitorCountErr('" + SVResString::getResString("IDS_PointPoor") + "','" +
                        SVResString::getResString("IDS_Affirm") + "');hiddenbar();";
                    return false;
                }
            }
            // 是否是网络设备，是网络设备监测点数置为零
            if(m_szNetworkSet == "true")
                szPoint = "0";
            sprintf(chMTID, "%d", nMonitorID);
            if(pszExtraLable && strlen(pszExtraLable) > 0 && szMonitorName.compare(pszExtraLable) != 0)
                szMonitroName = szMonitorName + ":"  + pszExtraLable;
            else if(pszExtraParam && strlen(pszExtraParam) > 0)
                szMonitroName = szMonitorName + ":"  + pszExtraParam;
            else
                szMonitroName = szMonitorName;
            AddNodeAttrib(mainnode, svName, szMonitroName);
            AddNodeAttrib(mainnode, svMonitorType, chMTID);
            AddNodeAttrib(mainnode, svIntPos, szPoint);
            saveDisableByParent(mainnode, SiteView_ECC_Device, m_szDeviceID);
        }
        // 监测器基本参数
        saveMonitorBaseParam(objMonitor, objMonitorTmp, pszSaveName, pszExtraParam);
        // 监测器高级参数
        saveMonitorAdvParam(objMonitor, objMonitorTmp, pszSaveName, pszExtraParam);
        // 监测器监测阀值
        saveMonitorCondition(objMonitor, objMonitorTmp);
        // 添加新的监测器
        string szRealIndex = AddNewMonitor(objMonitor, m_szDeviceID, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
        if(!szRealIndex.empty())
        {// 成功添加
            // 设置显示顺序
            int nIndex = FindIndexByID(szRealIndex);            
            if(pDevice)
                nIndex = pDevice->AppendMonitor(szRealIndex, szMonitroName, nMonitorID);

            char szIndex[16] = {0};
            sprintf(szIndex, "%d", nIndex);
            AddNodeAttrib(mainnode, svShowIndex, szIndex);

            // 创建监测数据表
            InsertTable(szRealIndex, nMonitorID, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
            // 配置权限
            CEccTreeView::m_SVSEUser.AddUserScopeAllRight(szRealIndex, SiteView_ECC_Monitor);
        }
    }
    // 关闭监测器
    if(objMonitor != INVALID_VALUE)
        CloseMonitor(objMonitor);
    // 关闭监测器模板
    if(objMonitorTmp != INVALID_VALUE)
        CloseMonitorTemplet(objMonitorTmp);

    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 saveMonitorBaseParam
// 说明 保存基础参数
// 参数
//      监测器对象
//      监测器模板对象
//      存储命名称
//      扩展参数值
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CEccAddDevice3rd::saveMonitorBaseParam(OBJECT &objMonitor, OBJECT objMonitorTemp, const char* pszSaveName, const char *pszExtraParam)
{
    // 监测器基本节点
    MAPNODE objMonitorNode = GetMonitorParameter(objMonitor);
    if(objMonitorNode != INVALID_VALUE)
    {
        LISTITEM lsItem;
        // 枚举监测器模板的每一条基本属性
        if( FindMTParameterFirst(objMonitorTemp, lsItem))
        {
            MAPNODE objNode;
            while( (objNode = FindNext(lsItem)) != INVALID_VALUE )
            {
                // 属性参数名称 缺省值 是否与其他值计算
                string szName (""), szValue (""), szAccValue ("");
                FindNodeValue(objNode, svName, szName);
                FindNodeValue(objNode, svValue, szValue);
                FindNodeValue(objNode, svAccountWith, szAccValue);
                if(!szAccValue.empty())
                    AddNodeAttrib(objMonitorNode, szName + "1", szValue);

                if(pszSaveName && strlen(pszSaveName) > 0 && szName.compare(pszSaveName) == 0)
                {
                    if(pszExtraParam && strlen(pszExtraParam) > 0)
                        AddNodeAttrib(objMonitorNode, szName, pszExtraParam);
                    else
                        AddNodeAttrib(objMonitorNode, szName, "");
                }
                else
                    AddNodeAttrib(objMonitorNode, szName, szValue);
            }
        }
        // 描述 报告描述 任务计划 校验错误 错误时监测频率保存值 错误时监测频率 错误时监测频率时间单位
        AddNodeAttrib(objMonitorNode, svDescription,    "");
        AddNodeAttrib(objMonitorNode, svReportDesc,     "");
        AddNodeAttrib(objMonitorNode, svPlan,           "7*24");
        AddNodeAttrib(objMonitorNode, svCheckErr,       "false");
        AddNodeAttrib(objMonitorNode, svErrFreqSave,    "");
        AddNodeAttrib(objMonitorNode, svErrFreq,        "0");
        AddNodeAttrib(objMonitorNode, svErrFreqUnit,    "1");
    }

    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 saveMonitorCondition
// 说明 保存监测器的监测阀值
// 参数
//      监测器对象
//      监测器模板对象
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CEccAddDevice3rd::saveMonitorCondition(OBJECT &objMonitor, OBJECT objMonitorTemp)
{
    // 错误阀值
    MAPNODE alertnode = GetMonitorErrorAlertCondition(objMonitor);
    MAPNODE alertnodeTmp = GetMTErrorAlertCondition(objMonitorTemp);
    if(alertnode != INVALID_VALUE && alertnodeTmp != INVALID_VALUE)
    {
        saveAlertNodeValue(alertnode, alertnodeTmp);
    }

    // 警告阀值
    alertnode = GetMonitorWarningAlertCondition(objMonitor);
    alertnodeTmp = GetMTWarningAlertCondition(objMonitorTemp);
    if(alertnode != INVALID_VALUE && alertnodeTmp != INVALID_VALUE)
    {
        saveAlertNodeValue(alertnode, alertnodeTmp);
    }

    // 正常阀值
    alertnode = GetMonitorGoodAlertCondition(objMonitor);
    alertnodeTmp = GetMTGoodAlertCondition(objMonitorTemp);
    if(alertnode != INVALID_VALUE && alertnodeTmp != INVALID_VALUE)
    {
        saveAlertNodeValue(alertnode, alertnodeTmp);
    }

    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 saveMonitorAdvParam
// 说明 保存高级参数
// 参数
//      监测器对象
//      监测器模板对象
//      扩展参数存储名称
//      扩展参数值
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CEccAddDevice3rd::saveMonitorAdvParam(OBJECT &objMonitor, OBJECT objMonitorTemp, const char* pszSaveName, const char *pszExtraParam)
{
    // 监测器高级节点
    MAPNODE objMonitorNode = GetMonitorAdvanceParameterNode(objMonitor);
    if(objMonitorNode != INVALID_VALUE)
    {
        LISTITEM lsItem;
        // 枚举监测器模板的每一条高级属性
        if( FindMTAdvanceParameterFirst(objMonitorTemp, lsItem))
        {
            MAPNODE objNode;
            while( (objNode = FindNext(lsItem)) != INVALID_VALUE )
            {
                // 参数名称 缺省值 计算方式
                string szName (""), szValue (""), szAccValue ("");
                FindNodeValue(objNode, svName, szName);
                FindNodeValue(objNode, svValue, szValue);
                FindNodeValue(objNode, svAccountWith, szAccValue);
                if(!szAccValue.empty())
                    AddNodeAttrib(objMonitorNode, szName + "1", szValue);

                if(pszSaveName && strlen(pszSaveName) > 0 && szName.compare(pszSaveName) == 0)
                {
                    if(pszExtraParam && strlen(pszExtraParam) > 0)
                        AddNodeAttrib(objMonitorNode, szName, pszExtraParam);
                    else
                        AddNodeAttrib(objMonitorNode, szName, "");
                }
                else
                    AddNodeAttrib(objMonitorNode, szName, szValue);
            }
        }
    }
    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 saveAlertNodeValue
// 说明 保存阀值
// 参数
//      监测器报警节点对象
//      监测器报警节点模板对象
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CEccAddDevice3rd::saveAlertNodeValue(MAPNODE &alertnode, MAPNODE &alertnodeTmp)
{
    string szRelationCount("");
    FindNodeValue(alertnodeTmp, svConditionCount, szRelationCount);
    if(!szRelationCount.empty())
    {
        char szKey [16] = {0};
        string szCondition (""), szExpression(""), szReturn (""), szParamValue ("") , szRelation ("");
        int nCount = 0;

        AddNodeAttrib(alertnode, svConditionCount, szRelationCount);

        FindNodeValue(alertnodeTmp, svExpression, szExpression);
        AddNodeAttrib(alertnode, svExpression, szExpression);

        nCount = atoi(szRelationCount.c_str());
        for(int i = 1; i <= nCount - 1; i++)
        {   
            sprintf(szKey, "sv_relation%d", i);
            FindNodeValue(alertnodeTmp, szKey, szRelation);
            AddNodeAttrib(alertnode, szKey, szRelation);

            sprintf(szKey, "sv_paramname%d", i);
            FindNodeValue(alertnodeTmp, szKey, szReturn);
            AddNodeAttrib(alertnode, szKey, szReturn);

            sprintf(szKey, "sv_operate%d", i);
            FindNodeValue(alertnodeTmp, szKey, szCondition);
            AddNodeAttrib(alertnode, szKey, szCondition);
            
            sprintf(szKey, "sv_paramvalue%d", i);
            FindNodeValue(alertnodeTmp, szKey, szParamValue);
            AddNodeAttrib(alertnode, szKey, szParamValue);
        }
        sprintf(szKey, "sv_paramname%d", i);
        FindNodeValue(alertnodeTmp, szKey, szReturn);
        AddNodeAttrib(alertnode, szKey, szReturn);

        sprintf(szKey, "sv_operate%d", i);
        FindNodeValue(alertnodeTmp, szKey, szCondition);
        AddNodeAttrib(alertnode, szKey, szCondition);
        
        sprintf(szKey, "sv_paramvalue%d", i);
        FindNodeValue(alertnodeTmp, szKey, szParamValue);
        AddNodeAttrib(alertnode, szKey, szParamValue);
    }
    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 移除绑定
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice3rd::removeMapping()
{
    list<WCheckBox*>::iterator it;
    for(it = m_lsCkMT.begin(); it != m_lsCkMT.end(); it++)
        m_mapMinitor.removeMappings((*it));

    m_lsCkMT.clear();
}

