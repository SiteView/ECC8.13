#include "eccobjfunc.h"
#include "basefunc.h"
#include "basedefine.h"
#include "mainview.h"
#include "debuginfor.h"
#include "treeview.h"

#include "../../base/des.h"
#include "../../tools/usbdog/doglib/safedog.h"

#include "../../opens/libwt/WComboBox"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� saveDisableByParent
// ˵�� ���ݸ���ֹ״̬�����ӵĽ�ֹ״̬
// ���� 
//      mainnode�� ��ǰ��������ڵ�
//      nObjType�� ���ݶ�������
//      szParentID�����ڵ�ID
// ���� �ɹ�����ʧ��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool saveDisableByParent(MAPNODE &mainnode, int nObjType, string szParentID)
{
    bool bSucc = true;
    OBJECT svObj = INVALID_VALUE;
    MAPNODE objNode = INVALID_VALUE;

    // �������ݶ������Ͳ����˶��󸸽ڵ�
    switch(nObjType)
    {
    case SiteView_ECC_Group:
        svObj = GetGroup(szParentID, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
        if(svObj != INVALID_VALUE)
            objNode = GetGroupMainAttribNode(svObj);
        break;
    case SiteView_ECC_Device:
        svObj = GetEntity(szParentID, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
        if(svObj != INVALID_VALUE)
            objNode = GetEntityMainAttribNode(svObj);
        break;
    }
    
    if(objNode != INVALID_VALUE)
    {
        // ��ֹ״̬ ��ʼʱ�� ��ֹʱ��
        string szDisable (""), szStartTime (""), szEndTime ("");
        FindNodeValue(objNode, svDisable, szDisable);
        FindNodeValue(objNode, svStartTime, szStartTime);
        FindNodeValue(objNode, svEndTime, szEndTime);

        AddNodeAttrib(mainnode, svDisable, szDisable);
        AddNodeAttrib(mainnode, svStartTime, szStartTime);
        AddNodeAttrib(mainnode, svEndTime, szEndTime);
    }
    switch(nObjType)
    {
    case SiteView_ECC_Group:
        CloseGroup(svObj);
        break;
    case SiteView_ECC_Device:
        CloseEntity(svObj);
        break;
    }
    return bSucc;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� makeDllName
// ˵�� ����DLL�ľ���·��
// ���� const string & szDll��DLL�ļ�������
// ���� ��ɺ��·��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string makeDllName(const string & szDll)
{
    string szDllName("");
    // �Ƿ�����ʾ��
    if(!isDemoMode())
        szDllName = GetSiteViewRootPath() + "\\fcgi-bin\\" + szDll;
    else
        szDllName = GetSiteViewRootPath() + "\\fcgi-bin\\GetRandomValue.dll";
    return szDllName;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� ReadWriteDynQueue
// ˵�� �ڶ�д�����ж�д��̬����
// ���� 
//      const string &szIndex����ǰ��������
//      const string &szDll��DLL��
//      const string &szFunc��������
//      const char *pszQuery�����в���
//      const int &nSize�����в�������
//      char *pBuffer�����ݻ�����
//      int &nRetSize����������С
// ���� ��ʱδʹ��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ReadWriteDynQueue(const string &szIndex, const string &szDll, const string &szFunc, const char *pszQuery, 
                       const int &nSize, char *pBuffer, int &nRetSize)
{
    static const string szLabel = "DYNPARAM";       // ��̬����
    static const string szDLLName = "DLL";          // DLL
    static const string szFUNC = "FUNC";            // FUNC
    static const string szParam = "PARAMS";         // ����
    static const char szSeparator = '#';            // �ָ���

    bool bRet = false;
    // �õ�ˢ�¶���
    string szRefreshQueue(getRefreshQueueName(szIndex)), szQueueName(makeQueueName());
    // �������У� ��д����
    string szParamQueue(szQueueName + "_R"), szRetQueue(szQueueName + "_W");
    // ������д����
    CreateQueue(szRetQueue, 1, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
    // ������������
    CreateQueue(szParamQueue, 1, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
    // ����ˢ�¶���
    CreateQueue(szRefreshQueue, 1, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);

    // ���ݴ�С
    int nDllSize = static_cast<int>(szDll.size()) + 2, nFuncSize = static_cast<int>(szFunc.size()) + 2;

    // ��̬�����ڴ�
    char *pDll = new char[nDllSize];
    if(pDll)
    {
        // �ڴ���������
        memset(pDll, 0, nDllSize);
        // ��������
        strcpy(pDll, szDll.c_str());
        // 
        if(PushMessage(szParamQueue, szDLLName, pDll, nDllSize, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr))
        {
            char *pFunc = new char[nFuncSize];
            if(pFunc)
            {
                memset(pFunc, 0, nFuncSize);
                strcpy(pFunc, szFunc.c_str());
                if(PushMessage(szParamQueue, szFUNC, pFunc, nFuncSize, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr))
                {
                    if(PushMessage(szParamQueue, szParam, pszQuery, nSize, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr))
                    {
                        int nQueueSize = static_cast<int>(szQueueName.size()) + 2;
                        char *pszQueue = new char[nQueueSize];
                        if(pszQueue)
                        {
                            memset(pszQueue, 0, nQueueSize);
                            strcpy(pszQueue, szQueueName.c_str());
                            if(PushMessage(szRefreshQueue, szLabel, pszQueue, nQueueSize, CEccMainView::m_szIDCUser, 
                                CEccMainView::m_szAddr))
                            {
                                int nTimes = 0;
                                while(!bRet)
                                {
                                    if(nTimes >= 40)
                                        break;

                                    // ��ȡ����
                                    bRet = ReadFromRetQueue(szRetQueue, pBuffer, nRetSize);
                                    nTimes ++;
                                }
                            }
                            delete []pszQueue;
                        }
                    }
                }
                delete []pFunc;
            }
        }
        delete []pDll;
    }
    // ɾ������
    DeleteQueue(szRetQueue, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);

    return bRet;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� ReadFromRetQueue
// ˵�� ��ָ�������ж�ȡ����
// ���� 
//      const string &szQueue��ָ������
//      char *pBuffer�����ݻ�����
//      int &nRetSize����������С
// ���� ��ʱδʹ��
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ReadFromRetQueue(const string &szQueue, char *pBuffer, int &nRetSize)
{
    bool bRet = false;
    static const string szDynLabel = "DYNPARAM";
    static const string szEnd   = "DYNEND";

    MQRECORD mrd = PopMessage(szQueue, 2000, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
	if(mrd != INVALID_VALUE)
	{
        string szLabel("");
         TTime ct;
	    unsigned int len = 0;
	    if(GetMessageData(mrd, szLabel, ct, NULL, len))
	    {
            if(szLabel == szDynLabel)
            {
                if(pBuffer && len <= static_cast<unsigned int>(nRetSize))
                {
                    if(!::GetMessageData(mrd, szLabel, ct, pBuffer, len))
                    {
                        memset(pBuffer, 0, nRetSize);
                    }
                    else
                    {
                        nRetSize = len;
                        bRet = true;
                    }
                }
            }
            else if(szLabel == szEnd)
            {
                bRet = true;
            }
        }
    }
    return bRet;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� getUsingNetworkCount
// ˵�� �õ���ʹ�������豸����
// ���� �����Ӽ����ʱָ���豸����
// ���� ��ʹ�������豸����
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int  getUsingNetworkCount(string szDeviceID)
{
    PAIRLIST retlist; 
    PAIRLIST::iterator lsItem;
    int nNetworkCount = 0, nMonitorCount = 0; 
    list<string> lstMonitors;
    
    // �õ����е������豸 
    GetAllEntitysInfo(retlist, svNetworkSet, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);

    // ö��ÿһ�������豸��������ʹ�õ������豸����
    for(lsItem = retlist.begin(); lsItem != retlist.end(); lsItem ++)
    {
        if((*lsItem).value == "true")
        {
            // ���豸
            OBJECT objEntity = GetEntity((*lsItem).name,  CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
            if(objEntity != INVALID_VALUE)
            {// �򿪳ɹ�
                // �õ������ڸ������豸�����м����
                if(GetSubMonitorsIDByEntity(objEntity, lstMonitors))
                {
                    // �õ����������
                    nMonitorCount = static_cast<int>(lstMonitors.size());
                    if(!szDeviceID.empty() && (*lsItem).name == szDeviceID)
                        nMonitorCount ++;
                    // ��������0���ܱ�30����
                    if(nMonitorCount == 30)
                        nNetworkCount ++;
                    else
                        nNetworkCount = nNetworkCount + nMonitorCount / 30 + 1;
                }
                else
                {
                    // ��ü����ʧ����ʹ�������豸������1
                    nNetworkCount ++;
                }

                lstMonitors.clear();
                CloseEntity(objEntity);
            }
            else
            {// ʧ�ܣ�ֱ�Ӹ������豸������1
                nNetworkCount ++;
            }
        }
    }
    return nNetworkCount;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� getUsingMonitorCount
// ˵�� �õ��Ѿ�ʹ�õļ��������
// ���� ��
// ���� ��ʹ�ü��������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int  getUsingMonitorCount()
{
    PAIRLIST retlist;
    PAIRLIST::iterator lsItem;
    int nMonitorCount = 0, nPoint = 0;
    
    // ������м������ÿ����������е�������
    GetAllMonitorsInfo(retlist, svIntPos, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
    for(lsItem = retlist.begin(); lsItem != retlist.end(); lsItem ++)
    {
        // ���������Ƿ�Ϊ���ַ���
        if((*lsItem).value.empty())
        {// Ϊ��
            // ��������� ��1
            nMonitorCount ++;
        }
        else
        {
            // �õ�����
            nPoint = atoi((*lsItem).value.c_str());
            if(nPoint <= 0)
                nPoint = 0;
            nMonitorCount += nPoint;
        }
    }
    return nMonitorCount;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� checkNetworkPoint
// ˵�� У�������豸�����Ƿ񳬵�
// ���� ��У������
// ���� ����||������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool checkNetworkPoint(int nNetworkCount)
{
	SafeDog pSafeDog;
	bool IsDogExit=false;
    string szNetworkCount ("");
	
    // �ж��Ƿ���ʽ�棬���ݹ��Ƿ����
	if( !pSafeDog.DogOnUsb(IsDogExit) )
	{
        // ��ʽ��
        // �ڹ��ж�ȡ�����豸��
		if(!pSafeDog.GetDeviceNum(szNetworkCount))
		{
            // ����ǲ��޵�
			if(szNetworkCount =="99999" )
                return true;

            int nPoint = atoi(szNetworkCount.c_str());
            if(nPoint < nNetworkCount)
                return false;
		}
        else
            return false;
	}
	else
	{
        // ���ð�
        // ��general.ini�ļ��ж�ȡ����
		szNetworkCount = GetIniFileString("license", "nw", "",  "general.ini");
        char szOutput[512] = {0};
        Des des;
        if(des.Decrypt(szNetworkCount.c_str(), szOutput))
            szNetworkCount = szOutput;
        else
            return false;

        // ����ǲ��޵�
        if(szNetworkCount == "9999")
            return true;

        int nPoint = atoi(szNetworkCount.c_str());
        if(nPoint < nNetworkCount)
            return false;
	}	
    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� checkMonitorsPoint
// ˵�� У�����������Ƿ񳬵�
// ���� ��У����������
// ���� ����||������
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool checkMonitorsPoint(int nMonitorsCount)
{
	SafeDog pSafeDog;
	bool IsDogExit=false;
	string szPointCount ("");

    // �ж��Ƿ���ʽ�棬���ݹ��Ƿ����
	if(pSafeDog.DogOnUsb(IsDogExit)==0)
	{
        // ��ʽ��
        // �ڹ��ж�ȡ��ʹ�ü��������
		if(!pSafeDog.GetNodeNum(szPointCount))
		{
            // ����ǲ��޵�
			if(szPointCount == "99999")
			    return true;

            int nPoint = atoi(szPointCount.c_str());

            if(nPoint < nMonitorsCount)
                return false;
		}
        else
            return false;
	}
	else
	{
        // ���ð�
        // ��general.ini�ļ��ж�ȡ����
		szPointCount = GetIniFileString("license", "point", "",  "general.ini");
        char szOutput[512] = {0};
        Des des;
        if(des.Decrypt(szPointCount.c_str(), szOutput))
            szPointCount = szOutput;
        else
            return false;

        // ����ǲ��޵�
        if(szPointCount == "9999")
            return true;

        int nPoint = atoi(szPointCount.c_str());

        if(nPoint < nMonitorsCount)
            return false;
	}	
    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� MakeRunParamStringByID
// ˵�� �����豸ID����ö���豸��ö�̬����ʱ�ı�Ҫ���в���
// ���� 
//      const string szIndex�豸����
//      int nMTID �����ģ������
// ���� ʹ��\v�ָ������в���
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
string MakeRunParamStringByID(const string &szIndex, int nMTID)
{
    string szRun("");
    // ���豸
    OBJECT objDevice = GetEntity(szIndex, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
    if(objDevice != INVALID_VALUE)
    {
        // �õ����ڵ�
        MAPNODE mainnode = GetEntityMainAttribNode(objDevice);
        if(mainnode != INVALID_VALUE)
        {
            string szDeviceType ("");
            map<string, string, less<string> > lsDeviceParam;
            // �õ��豸����
            if(FindNodeValue(mainnode, svDeviceType, szDeviceType))
            {
                // ���豸ģ��
                OBJECT objDeviceTmp = GetEntityTemplet(szDeviceType, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
                if(objDeviceTmp != INVALID_VALUE)
                {
                    // ö��ȫ���Ŀ��Ʋ���
                    LISTITEM lsItem;
                    if( FindETContrlFirst(objDeviceTmp, lsItem))
                    {
                        MAPNODE objNode;
                        while( (objNode = FindNext(lsItem)) != INVALID_VALUE )
                        {
                            string szName (""), szRun ("");
                            string szType ("");
                            // �õ��������ƣ��Ƿ��Ǳ�Ҫ�������Լ���������
                            FindNodeValue(objNode, svName, szName);
                            FindNodeValue(objNode, svRun, szRun);
                            FindNodeValue(objNode, svType, szType);
                            if(szRun == "true")
                                lsDeviceParam[szName] = szType;
                        }
                    }
                    // �ر��豸ģ��
                    CloseEntityTemplet(objDeviceTmp);
                }
            }

            // �ڵ�ǰ�豸��ö��ÿһ����Ҫ���в���
            map<string, string, less<string> >::iterator lstItem;
            for(lstItem = lsDeviceParam.begin(); lstItem != lsDeviceParam.end(); lstItem ++)
            {
                string szValue ("");
                FindNodeValue(mainnode, (lstItem->first), szValue);
                // �Ƿ�����������
                if((lstItem->second).compare(svPassword) == 0)
                {
                    // ����
                    char szOutput[512] = {0};
                    Des des;
                    if(des.Decrypt(szValue.c_str(), szOutput))
                        szValue = szOutput;
                }
                szRun = szRun + (lstItem->first) + "=" + szValue + "\v";
            }
        }
        // �ر��豸
        CloseEntity(objDevice);
    }

    char szTpl[32] = {0};
    sprintf(szTpl, "_TemplateID=%d", nMTID);
    szRun += szTpl;
    PrintDebugString(szRun);

    return szRun;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� AddTaskList
// ˵�� �������ƻ���ָ��combobox
// ���� 
//      WComboBox * pTask��������ݵ�combobox
// ���� ��
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AddTaskList(WComboBox * pTask)
{
    if(pTask)
    {
        list<string> lsTaskName;
        list<string>::iterator lsItem;

        // �õ����е�����ƻ�
        if(GetAllTaskName(lsTaskName))
        {
            for(lsItem = lsTaskName.begin(); lsItem != lsTaskName.end(); lsItem ++)
            {
                string szName = (*lsItem);
                pTask->addItem(szName);
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� isDisable
// ˵�� �жϵ�ǰ���ݶ����Ƿ񱻽�ֹ
// ����
//      const string &szID���ݶ�������
//      int nType����
// ���� ��ֹ || ������ֹ
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool isDisable(const string &szID, int nType)
{
    bool bDisable = false;

    // �������ʹ򿪲�ͬ����
    OBJECT objSV = INVALID_VALUE;
    switch(nType)
    {
    case SiteView_ECC_Group:
        objSV = GetGroup(szID, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
        break;
    case SiteView_ECC_Device:
        objSV = GetEntity(szID, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
        break;
    case SiteView_ECC_Monitor:
        objSV = GetMonitor(szID, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
        break;
    }

    // �Ƿ�򿪳ɹ�
    if(objSV != INVALID_VALUE)
    {
        // �õ����ڵ�
        MAPNODE mainnode = INVALID_VALUE;
        switch(nType)
        {
        case SiteView_ECC_Group:
            mainnode = GetGroupMainAttribNode(objSV);
            break;
        case SiteView_ECC_Device:
            mainnode = GetEntityMainAttribNode(objSV);
            break;
        case SiteView_ECC_Monitor:
            mainnode = GetMonitorMainAttribNode(objSV);
            break;
        }
    
        // �ж��Ǳ���ֹ
        if(mainnode != INVALID_VALUE)
        {
            string szDisable ("");
            FindNodeValue(mainnode, svDisable, szDisable);
            if(szDisable == "true")
            {// ����ֹ
                bDisable =  true;
            }
            else if( szDisable == "time")
            {// ����ʱ��ֹ
                // �жϵ�ǰʱ���Ƿ��ڽ�ֹʱ�����
                string szEndTime ("");
                FindNodeValue(mainnode, svEndTime, szEndTime);
                int nYear = 0, nMonth = 0, nDay = 0;
                int nHour = 0, nMinute = 0;
                if(!szEndTime.empty())
                {
                    sscanf(szEndTime.c_str(), "%d - %d - %d - %d : %d", &nYear, &nMonth, &nDay, &nHour, &nMinute);
                    
                     TTime ttime =  TTime::GetCurrentTimeEx();

                     TTime ttend = TTime::TTime(nYear, nMonth, nDay, nHour, nMinute, 0);
                    if(ttime < ttend)
                        bDisable =  true;                        
                }
            }
        }
        switch(nType)
        {
        case SiteView_ECC_Group:
            CloseGroup(objSV);
            break;
        case SiteView_ECC_Device:
            CloseEntity(objSV);
            break;
        case SiteView_ECC_Monitor:
            CloseMonitor(objSV);
            break;
        }
    }

    return bDisable;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� isCanBePasteDevice
// ˵�� �Ƿ����ճ��ָ���豸
// ���� 
//      const string &szID��ճ���豸����
// ���� ���� || ������
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool isCanBePasteDevice(const string &szID)
{
    const CEccTreeNode *pNode = CEccTreeView::getECCObject(szID);
    if(pNode)
    {
        // �õ����ϵ��豸�ڵ�
        CEccTreeDevice *pDevice = static_cast<CEccTreeDevice*>(const_cast<CEccTreeNode*>(pNode));
        if(pDevice->isNetworkSet() == "true")
        {// ���豸�������豸
            int nNetworkCount = getUsingNetworkCount();

            int nMonitorCount = pDevice->getMointorCount();

            if(nMonitorCount == 30)
                nNetworkCount ++;
            else
                nNetworkCount = nNetworkCount + nMonitorCount / 30 + 1;

            return checkNetworkPoint(nNetworkCount);
        }
        else
        {// ���������豸
            int nMonitorCount = getUsingMonitorCount() + pDevice->getMointorCount();
            return checkMonitorsPoint(nMonitorCount);
        }
    }
    return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� PasteDevice
// ˵�� ��ָ���豸ճ����Ŀ�����ڣ�ͬʱΪ���豸����ÿ��������������ݱ�
// ����
//      const string &szDestGroupIDĿ����
//      const string &szSrcDevID��ճ���豸
// ���� �µ��豸�������ɹ������߿��ַ���
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
string PasteDevice(const string &szDestGroupID, const string &szSrcDevID)
{
    string szNewDeviceID(EntityCopy(szSrcDevID, szDestGroupID, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr));
    if(!szNewDeviceID.empty())
    {
        const CEccTreeNode *pNode = CEccTreeView::getECCObject(szSrcDevID);
        if(pNode)
        {
            CEccTreeDevice *pDevice = static_cast<CEccTreeDevice*>(const_cast<CEccTreeNode*>(pNode));

            CEccTreeView::AppendDevice(szNewDeviceID, pDevice->getName(), pDevice->getDescription(), pDevice->getDependsID(),
                pDevice->getCondition(), pDevice->getRealDeviceType(), pDevice->getOSType(), pDevice->isNetworkSet());
        }
        createAllTableOfDevice(szNewDeviceID);
    }
    return szNewDeviceID;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� createAllTableOfDevice
// ˵�� Ϊָ�����豸�����м�����������ݱ�
// ���� 
//      const string &szDeviceIndexָ���豸����
// ���� ��
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void createAllTableOfDevice(const string &szDeviceIndex)
{
    // �õ����ϵ��豸
    const CEccTreeNode *pNode = CEccTreeView::getECCObject(szDeviceIndex);
    CEccTreeDevice *pDevice = NULL;
    if(pNode)
        pDevice = static_cast<CEccTreeDevice*>(const_cast<CEccTreeNode*>(pNode));

    // ���豸
    OBJECT objDevice = GetEntity(szDeviceIndex, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
    if(objDevice != INVALID_VALUE)
    {
        list<string> lsMonitorID;
        list<string>::iterator lstItem;
        // �õ����豸�����м����
        if (GetSubMonitorsIDByEntity(objDevice, lsMonitorID))
        {
            int nMTID = 0;
            string szName("");
            for(lstItem = lsMonitorID.begin(); lstItem != lsMonitorID.end(); lstItem ++)
            {
                szName = getMonitorNameMTID((*lstItem), nMTID);
                if(pDevice)
                    pDevice->AppendMonitor((*lstItem), szName, nMTID);
                // �������ݱ�
                InsertTable((*lstItem), nMTID, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
            }
        }
        CloseEntity(objDevice);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� getMonitorNameMTID
// ˵�� ���ݼ���������õ�����������ƺͼ����ģ�������ID
// ���� 
//      const string &szMonitorID���������
//      int &nMTID�����ģ�������ID
// ���� �����������
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
string getMonitorNameMTID(const string &szMonitorID, int &nMTID)
{
    string szName("");
    // �򿪼����
    OBJECT objMonitor = GetMonitor(szMonitorID, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
    if(objMonitor != INVALID_VALUE)
    {
        // �õ����ڵ�
        MAPNODE node = GetMonitorMainAttribNode(objMonitor);
        if(node != INVALID_VALUE)
        {
            // �õ����ƺͼ����ģ��
            FindNodeValue(node, svName, szName);
            string szMTID (""); FindNodeValue(node, svMonitorType, szMTID);
            nMTID = atoi(szMTID.c_str());
        }
        // �رռ����
        CloseMonitor(objMonitor);
    }
    return szName;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���� enumDeviceRunParam
// ˵�� �����豸ID����ö���豸��ö�̬����ʱ�ı�Ҫ���в���
// ���� 
//      const string szIndex�豸����
// ���� ʹ��\v�ָ������в���
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
string enumDeviceRunParam(const string &szDeviceIndex)
{
    string szQuery("");
    // ���豸
    OBJECT objDevice = GetEntity(szDeviceIndex, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
    if(objDevice != INVALID_VALUE)
    {
        // �õ��豸���ڵ�
        MAPNODE mainnode = GetEntityMainAttribNode(objDevice);
        if(mainnode != INVALID_VALUE)
        {
            // �õ��豸����
            string szDeviceType("");
            map<string, string, less<string> > lsDeviceParam;
            if(FindNodeValue(mainnode, svDeviceType, szDeviceType))
            {
                // ���豸ģ��
                OBJECT objDeviceTmp = GetEntityTemplet(szDeviceType, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
                if(objDeviceTmp != INVALID_VALUE)
                {
                    // ö��ÿ������
                    LISTITEM lsItem;
                    if( FindETContrlFirst(objDeviceTmp, lsItem))
                    {
                        MAPNODE objNode;
                        while( (objNode = FindNext(lsItem)) != INVALID_VALUE )
                        {
                            string szName(""), szRun("");
                            string szType("");
                            // �õ����� �Ƿ�������ʱ���� ��������
                            FindNodeValue(objNode, svName, szName);
                            FindNodeValue(objNode, svRun, szRun);
                            FindNodeValue(objNode, svType, szType);
                            if(szRun == "true")
                                lsDeviceParam[szName] = szType;
                        }
                    }
                    // �ر��豸ģ��
                    CloseEntityTemplet(objDeviceTmp);
                }
            }
            // �ڵ�ǰ�豸��ö��ÿ�����в���
            map<string, string, less<string> >::iterator lstItem;
            for(lstItem = lsDeviceParam.begin(); lstItem != lsDeviceParam.end(); lstItem ++)
            {
                string szValue("");
                FindNodeValue(mainnode, (lstItem->first), szValue);
                if((lstItem->second).compare(svPassword) == 0)
                {// �Ƿ���������������
                    // ����
                    char szOutput[512] = {0};
                    Des des;
                    if(des.Decrypt(szValue.c_str(), szOutput))
                        szValue = szOutput;
                }
                szValue = url_Encode(szValue.c_str());
                szQuery = szQuery + (lstItem->first) + "=" + szValue + "&";
            }
            szQuery = szQuery + "devicetype=" + szDeviceType;
        }
        // �ر��豸
        CloseEntity(objDevice);
    }
    PrintDebugString(szQuery.c_str());
    return szQuery;
}

