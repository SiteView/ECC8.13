/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// adddevice3rd.cpp
// ����豸�ĵ�������������Ӽ����
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

//#define ODS_USING // ע�������־��ʹ����ͨ��ODS_ǰ׺�����������Ϣ�Ĵ���ʧЧ��
#include "../../base/StringHelper.h"

typedef bool(ListDevice)(const char* szQuery, char* szReturn, int &nSize);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���캯��
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
// ��������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
CEccAddDevice3rd::~CEccAddDevice3rd()
{
    removeMapping();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��ʼ��
// ����
//      �Ƿ񴴽�������ť
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice3rd::initForm(bool bHasHelp)
{
    // �����ʼ��
    CEccBaseTable::createTitle(bHasHelp);
    // ���ñ���������
    if(m_pTitle)
        m_pTitle->setText(SVResString::getResString("IDS_Quick_Add"));

    int nRow = numRows();

    // ����
    WTable *pSub = new WTable(elementAt(nRow, 0));
    elementAt(nRow, 0)->setStyleClass("height95p");
    if(pSub)
    {
        pSub->setStyleClass("panel");
        // ������
        WScrollArea *pScroll = new WScrollArea(elementAt(nRow, 0));
        if(pScroll)
        {
            pScroll->setWidget(pSub);
            pScroll->setStyleClass("panel");
        }

        // ʵ�����ݱ�
        CEccListTable *pSubList = new CEccListTable(pSub->elementAt(0, 0), false, false, false, false);
        if(pSubList)
        {
            // ���ñ���
            pSubList->setTitle(SVResString::getResString("IDS_Quick_Add"));
            m_pContent = pSubList->getListTable();
        }
        // ���뷽ʽ
        pSub->elementAt(0, 0)->setContentAlignment(AlignTop);
    }

    // ��������
    createOperate();
    // �������ذ�ť
    createHideButton();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice3rd::createOperate()
{
    int nRow = numRows();
    m_pOperate = new WTable(elementAt(nRow, 0));
    if(m_pOperate)
    {
        m_pOperate->setStyleClass("widthauto");
        int nRow = m_pOperate->numRows();
        // ����
        m_pSave = new CEccImportButton(SVResString::getResString("IDS_Add"), SVResString::getResString("IDS_Save_Sel_Monitor_Tip"),
            "", m_pOperate->elementAt(nRow, 0));
        if(m_pSave)
        {
            WObject::connect(m_pSave, SIGNAL(clicked()), "showbar()", this, SLOT(saveAllSelMonitors()),
                WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        }

        new WText("&nbsp;", m_pOperate->elementAt(nRow, 1));

        // ȡ��
        CEccButton *pCancel = new CEccButton(SVResString::getResString("IDS_Cancel"), SVResString::getResString("IDS_Cancel_Add_Monitor_Tip"),
            "", m_pOperate->elementAt(nRow, 2));
        if(pCancel)
        {
            WObject::connect(pCancel, SIGNAL(clicked()), "showbar();", this, SLOT(Cancel()),
                WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        }

        // ���ö��뷽ʽ
        nRow = static_cast<WTableCell*>(m_pOperate->parent())->row();
        elementAt(nRow, 0)->setContentAlignment(AlignBottom | AlignCenter);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �������ذ�ť
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
// ȡ����Ӽ����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice3rd::Cancel()
{
    // ��ʾ����ӵ��豸
    CEccMainView::m_pRightView->showNewDevice(m_szDeviceID);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����ȫ��ѡ��ļ����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice3rd::saveAllSelMonitors()
{
    unsigned long ulStart = GetTickCount();

	string strQuickAddMonitorName("");
    irow it;
    int nPos = 0;
    // ö��ÿһ������
    for(it = m_svValueList.begin(); it != m_svValueList.end(); it ++)
    {
        // ��ǰ�����Ƿ�ѡ��
        SVTableCell *pCell =  (*it).second.Cell(0);
        if(pCell && pCell->Type() == adCheckBox)
        {
            string szText = ((WCheckBox*)pCell->Value())->label()->text();
            nPos = static_cast<int>(szText.find(SVResString::getResString("IDS_Monitor_Point_Lack_Tip")));
            if(nPos >= 0)
                szText = szText.substr(0, nPos);

            ((WCheckBox*)pCell->Value())->label()->setText(szText);
            if(((WCheckBox*)pCell->Value())->isChecked())
            {// ѡ��״̬
                string szLable = ((WCheckBox*)pCell->Value())->label()->text();
                // ��������
                if(!saveMonitor((*it).second.getTag(),(*it).second.getProperty(), pCell->Property(), szLable.c_str()))
                {// ����ʧ�ܣ� ��ʾ������Ϣ
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
// ö�ٶ�̬����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice3rd::EnumDynData()
{
    // ö��ÿ�������ģ��
    list<monitor_templet>::iterator lstItem;
    for(lstItem = m_lsMonitorTemplet.begin(); lstItem != m_lsMonitorTemplet.end(); lstItem ++)
    {      
        char szTpl [32] = {0};
        // ���ö�̬���ò���
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
// �������
// ����
//      �豸ID
//      �豸����
//      ���в���
//      ������Ӽ�����б�
//      ȱʡѡ��ļ�����б�
//      �豸�Ƿ��������豸
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
    // �����ɹ�
    if(sv_split(szQuickAdd.c_str(), ",", lstMonitors, false) > 0)
    {
        list<string>::iterator lstItem;
        int nPos = 0;
        bool bSelect;
        // ö��ÿһ�����ģ��
        for(lstItem = lstMonitors.begin(); lstItem != lstMonitors.end(); lstItem ++)
        {
            // ȱʡ�Ƿ�ѡ��
			bSelect = false;
			nPos = static_cast<int>(szQuickAddSel.find((*lstItem).c_str()));
			if(nPos >= 0)
			{
				const char *pValue = szQuickAddSel.c_str();
				if( *(pValue + nPos +(*lstItem).length()) == ',' || *(pValue + nPos +(*lstItem).length()) == '\0')
					bSelect = true;
			}

            // ���ݼ����ģ��IDö����Ҫ���Բ����м�¼
            int nMonitorID = atoi((*lstItem).c_str());
            OBJECT objMonitor = GetMonitorTemplet(nMonitorID, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
            if(objMonitor != INVALID_VALUE)
            {
                MAPNODE node = GetMTMainAttribNode(objMonitor);
                monitor_templet monitor;
                monitor.nMonitorID = nMonitorID;
				monitor.bSel = bSelect;
                // ���� ���� ��չ��̬�⣨ö�ٶ�̬����ʹ�ã�ȱʡʹ��sv_dll��
                // ��չ������
                // ��չ����
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
                // �����ݱ��Ƿ�ɹ�����
                if(m_pContent)
                {
                    // �����ݱ�ĵ�ǰ����
                    int nRow = m_pContent->numRows();
                    WCheckBox *pCheck = NULL;
                    // �Ƿ���Ҫʹ�ö�̬����
                    if(!monitor.szDllName.empty() && !monitor.szFuncName.empty())
                    {// ��Ҫ
                        bHasDyn = true;
                        // ����ȫѡ checkbox
                        WCheckBox* pSelAll = new WCheckBox(monitor.szLabel, m_pContent->elementAt(nRow, 0));
                        if(pSelAll)
                        {
                            pSelAll->label()->setStyleClass("tgrouptitle2");
                            // tooltip
                            pSelAll->setToolTip(SVResString::getResString("IDS_All_Select"));
                            // �Ƿ�ѡ��
                            pSelAll->setChecked(bSelect);
                            // �� click
                            WObject::connect(pSelAll, SIGNAL(clicked()), "showbar();", &m_mapMinitor, SLOT(map()), 
                                WObject::ConnectionType::JAVASCRIPTDYNAMIC);

                            m_mapMinitor.setMapping(pSelAll, nMonitorID);
                            m_lsCkMT.push_back(pSelAll);
                        }
                        m_pContent->elementAt(nRow, 0)->setStyleClass("padding_top");
                        m_pContent->GetRow(nRow)->setStyleClass("table_data_input_rows");

                        nRow ++;
                        // ��չ�������Բ��������Ƿ�Ϊ��
                        if(monitor.szSaveName.empty())
                        {
                            // ��ʾ������Ϣ
                            new WText(SVResString::getResString("IDS_Monitor_Templet_Error"), m_pContent->elementAt(nRow, 0));
                        }
                        else
                        {
                            // �����ӱ��Ա��ܷ��ö�̬����
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
                        // ��������ı�
                        WText *pName = new WText(monitor.szLabel, m_pContent->elementAt(nRow, 0));
                        if(pName)
                            pName->setStyleClass("tgrouptitle2");
                        // ���ô��е���ʾ��ʽ��
                        m_pContent->elementAt(nRow, 0)->setStyleClass("padding_top");
                        m_pContent->GetRow(nRow)->setStyleClass("table_data_input_rows");

                        nRow ++;
                        // ����һ���ڴ�����ʾ����Ϊ������������ֵ�checkbox
                        pCheck = new WCheckBox(monitor.szName, m_pContent->elementAt(nRow, 0));
                        m_pContent->elementAt(nRow, 0)->setStyleClass("padding_4");
                    }

                    nRow ++;
                    new WImage("../Images/space.gif", m_pContent->elementAt(nRow, 0));
                    m_pContent->elementAt(nRow, 0)->setStyleClass("table_data_input_space");

                    if(pCheck)
                    {// �����ɹ�
                        // �Ƿ�ѡ��
						pCheck->setChecked(bSelect);
                        char szIndex[32] = {0};
                        sprintf(szIndex, "%d", nMonitorID);
                        SVTableCell svCell;
                        svCell.setType(adCheckBox);
                        svCell.setValue(pCheck);
                        // ��¼
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
// ���ݼ����ģ������ȫ��ѡ��ö�ٳ����Ĵ�������
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
// ���� AddDynData
// ˵�� ������ʾ��̬����
// ����
//      ���Ӷ�̬�����ı��
//      ���в���
//      ���в�����С
//      �����ģ��ID
//      ��̬���ӿ�����
//      ��������
//      �洢����
//      ȱʡ�Ƿ�ѡ��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice3rd::AddDynData(WTable * pTable, const char* pszQuery, const int &nQuerySize, const int &nMonitorID, 
                            const string &szDllName, const string &szFuncName, const string &szSaveName, const bool &bSel)
{
// �Ƿ�����Windows ƽ̨������
    bool bGetDyn = false;
    char szReturn [svBufferSize] = {0};
    int nSize = sizeof(szReturn);

    if(FindSEID(m_szDeviceID) == "1")
    {
#ifdef WIN32
    string szDllName(makeDllName(szDllName));
    string szMsg = "Dll Name: " + szDllName + " Function Name: " + szFuncName;
    PrintDebugString(szMsg.c_str());
    // �򿪶�̬���ӿ�
    HINSTANCE hDll = LoadLibrary(szDllName.c_str());
    if (hDll)
    {
        // ��ú���
        ListDevice* func = (ListDevice*)GetProcAddress(hDll, szFuncName.c_str());
        if (func && szReturn)
        {
            bGetDyn = (*func)(pszQuery, szReturn, nSize);
        }
        // �رն�̬���ӿ�
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

				// 2007/7/24 ����
				// ���⣺����ԭ��Ʋ������ݸ�ʽû�п��ǲ����ַ��а���'='�ַ�����������µ������ַ����г���'='�ַ�
				// ʱ�������⡣����unix����ʱ�ͳ������޷��������ӽ����������а���'='�ַ����̵�����
				// ���������
				// 1. �޸���monitor.dll��SERVICES�����ķ���ֵ�㷨����ԭ����[������]=[������]�ķ���ֵ�θ�ʽ��Ϊ
				//    "[������]"=[������]��
				// 2. �����µĲ��������㷨���ò���������SH::CParamsParser�Է���ֵ���ַ������н�����
				//    SH::CParamsParser�ڽ����ַ���ʱ���Ὣ""��ס���ַ������������ַ�������������ʹ����ֵ��
				//    ����ַ����г�����'='����Ҳ����Ӱ������������"[������]"=[������]����ȷ��'='�ַ��ֽ类��
				//    ��Ϊ���������ַ���������ַ���������ʾ���ұ��ַ�����Ϊ�����ò�����
				// ++++++ �µļ�����ö�ٷ���ֵ�����㷨 ++++++
				SH::CParamsParser pp;
				pp.SetEndTag("\\0"); // ���ÿ��ַ�Ϊ��ֹ�ַ�
				// ��������£�Ӧ�����÷�����Ψһ��һ�������
				if (pp.Analysis(pos) == 1)
				{
					string szValue (""), szLabel ("");
					szValue = pp.Find(0, szLabel);
					SH::Trim(szValue, "\"");
					SH::Trim(szLabel, "\"");
					dynData[szLabel] = szValue;
					ODS_OUTDEBUGD("CEccAddDevice3rd::AddDynData{pos=[%s], szValue=[%s], szLabel=[%s]} for debug", pos, szValue.c_str(), szLabel.c_str());
				}
				// ------ �µļ�����ö�ٷ���ֵ�����㷨 ------

				/* 2007/7/24 ���� �޸��˼�����ö�ٷ���ֵ�ĸ�ʽ����˲����µķ���ֵ�����㷨��֧���ڷ���ֵ�ַ����а���'='���š�
                char *pPosition = strchr(pos, '=');
                if(pPosition)
                {
                    (*pPosition) = '\0';
                    ++pPosition;
                    dynData[pPosition] = pos;
                }
				*/

                pos = pos + nSize + 1;
            }
            
            // Ϊÿһ����̬���ݴ���һ��
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
// ���� saveMonitor
// ˵�� ��������
// ����
//      ���ģ��ID
//      ��̬�����Ĵ洢����
//      ��չ����ֵ
//      ��չ������ʾ����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CEccAddDevice3rd::saveMonitor(int nMonitorID, const char* pszSaveName, const char *pszExtraParam, 
                                   const char *pszExtraLable)
{
    CEccTreeDevice *pDevice = NULL;
    const CEccTreeNode *pNode = CEccMainView::m_pTreeView->getECCObject(m_szDeviceID);
    if(pNode)
        pDevice = static_cast<CEccTreeDevice*>(const_cast<CEccTreeNode*>(pNode));
    // ���������
    OBJECT objMonitor = CreateMonitor();
    // �򿪼����ģ��
    OBJECT objMonitorTmp = GetMonitorTemplet(nMonitorID, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
    if(objMonitor != INVALID_VALUE && objMonitorTmp != INVALID_VALUE)
    {// ����������ʹ�ģ�嶼�ɹ�
        string szMonitroName("");
        // �õ������ģ�����ڵ�
        MAPNODE mainnode = GetMonitorMainAttribNode(objMonitor);
        // �õ���������ڵ�
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
            {// ���������豸
                FindNodeValue(nodeTmp, svIntPos, szPoint);
                
                if(szPoint.empty())
                    szPoint = "1";
                // ���ü��������
                int nMonitorCount = getUsingMonitorCount();

                int nPoint = atoi(szPoint.c_str());
                if(nPoint <= 0)
                    nPoint = 0;
                nMonitorCount += nPoint;
                // ����Ƿ񳬵�
                if(!checkMonitorsPoint(nMonitorCount))
                {
                    WebSession::js_af_up = "showMonitorCountErr('" + SVResString::getResString("IDS_PointPoor") + "','" +
                        SVResString::getResString("IDS_Affirm") + "');hiddenbar();";
                    return false;
                }
            }
            else
            {// �����豸
                // ���������豸
                // �����豸���õ���
                int nNetworkCount = getUsingNetworkCount(m_szDeviceID);
                // ����Ƿ񳬵�
                if(!checkNetworkPoint(nNetworkCount))
                {
                    WebSession::js_af_up = "showMonitorCountErr('" + SVResString::getResString("IDS_PointPoor") + "','" +
                        SVResString::getResString("IDS_Affirm") + "');hiddenbar();";
                    return false;
                }
            }
            // �Ƿ��������豸���������豸��������Ϊ��
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
        // �������������
        saveMonitorBaseParam(objMonitor, objMonitorTmp, pszSaveName, pszExtraParam);
        // ������߼�����
        saveMonitorAdvParam(objMonitor, objMonitorTmp, pszSaveName, pszExtraParam);
        // �������ֵⷧ
        saveMonitorCondition(objMonitor, objMonitorTmp);
        // ����µļ����
        string szRealIndex = AddNewMonitor(objMonitor, m_szDeviceID, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
        if(!szRealIndex.empty())
        {// �ɹ����
            // ������ʾ˳��
            int nIndex = FindIndexByID(szRealIndex);            
            if(pDevice)
                nIndex = pDevice->AppendMonitor(szRealIndex, szMonitroName, nMonitorID);

            char szIndex[16] = {0};
            sprintf(szIndex, "%d", nIndex);
            AddNodeAttrib(mainnode, svShowIndex, szIndex);

            // ����������ݱ�
            InsertTable(szRealIndex, nMonitorID, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
            // ����Ȩ��
            CEccTreeView::m_SVSEUser.AddUserScopeAllRight(szRealIndex, SiteView_ECC_Monitor);
        }
    }
    // �رռ����
    if(objMonitor != INVALID_VALUE)
        CloseMonitor(objMonitor);
    // �رռ����ģ��
    if(objMonitorTmp != INVALID_VALUE)
        CloseMonitorTemplet(objMonitorTmp);

    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� saveMonitorBaseParam
// ˵�� �����������
// ����
//      ���������
//      �����ģ�����
//      �洢������
//      ��չ����ֵ
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CEccAddDevice3rd::saveMonitorBaseParam(OBJECT &objMonitor, OBJECT objMonitorTemp, const char* pszSaveName, const char *pszExtraParam)
{
    // ����������ڵ�
    MAPNODE objMonitorNode = GetMonitorParameter(objMonitor);
    if(objMonitorNode != INVALID_VALUE)
    {
        LISTITEM lsItem;
        // ö�ټ����ģ���ÿһ����������
        if( FindMTParameterFirst(objMonitorTemp, lsItem))
        {
            MAPNODE objNode;
            while( (objNode = FindNext(lsItem)) != INVALID_VALUE )
            {
                // ���Բ������� ȱʡֵ �Ƿ�������ֵ����
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
        // ���� �������� ����ƻ� У����� ����ʱ���Ƶ�ʱ���ֵ ����ʱ���Ƶ�� ����ʱ���Ƶ��ʱ�䵥λ
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
// ���� saveMonitorCondition
// ˵�� ���������ļ�ֵⷧ
// ����
//      ���������
//      �����ģ�����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CEccAddDevice3rd::saveMonitorCondition(OBJECT &objMonitor, OBJECT objMonitorTemp)
{
    // ����ֵ
    MAPNODE alertnode = GetMonitorErrorAlertCondition(objMonitor);
    MAPNODE alertnodeTmp = GetMTErrorAlertCondition(objMonitorTemp);
    if(alertnode != INVALID_VALUE && alertnodeTmp != INVALID_VALUE)
    {
        saveAlertNodeValue(alertnode, alertnodeTmp);
    }

    // ���淧ֵ
    alertnode = GetMonitorWarningAlertCondition(objMonitor);
    alertnodeTmp = GetMTWarningAlertCondition(objMonitorTemp);
    if(alertnode != INVALID_VALUE && alertnodeTmp != INVALID_VALUE)
    {
        saveAlertNodeValue(alertnode, alertnodeTmp);
    }

    // ������ֵ
    alertnode = GetMonitorGoodAlertCondition(objMonitor);
    alertnodeTmp = GetMTGoodAlertCondition(objMonitorTemp);
    if(alertnode != INVALID_VALUE && alertnodeTmp != INVALID_VALUE)
    {
        saveAlertNodeValue(alertnode, alertnodeTmp);
    }

    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� saveMonitorAdvParam
// ˵�� ����߼�����
// ����
//      ���������
//      �����ģ�����
//      ��չ�����洢����
//      ��չ����ֵ
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CEccAddDevice3rd::saveMonitorAdvParam(OBJECT &objMonitor, OBJECT objMonitorTemp, const char* pszSaveName, const char *pszExtraParam)
{
    // ������߼��ڵ�
    MAPNODE objMonitorNode = GetMonitorAdvanceParameterNode(objMonitor);
    if(objMonitorNode != INVALID_VALUE)
    {
        LISTITEM lsItem;
        // ö�ټ����ģ���ÿһ���߼�����
        if( FindMTAdvanceParameterFirst(objMonitorTemp, lsItem))
        {
            MAPNODE objNode;
            while( (objNode = FindNext(lsItem)) != INVALID_VALUE )
            {
                // �������� ȱʡֵ ���㷽ʽ
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
// ���� saveAlertNodeValue
// ˵�� ���淧ֵ
// ����
//      ����������ڵ����
//      ����������ڵ�ģ�����
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
// �Ƴ���
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice3rd::removeMapping()
{
    list<WCheckBox*>::iterator it;
    for(it = m_lsCkMT.begin(); it != m_lsCkMT.end(); it++)
        m_mapMinitor.removeMappings((*it));

    m_lsCkMT.clear();
}

