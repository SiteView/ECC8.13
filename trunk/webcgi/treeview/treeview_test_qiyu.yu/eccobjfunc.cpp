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
// 函数 saveDisableByParent
// 说明 根据父禁止状态决定子的禁止状态
// 参数 
//      mainnode， 当前对象的主节点
//      nObjType， 数据对象类型
//      szParentID，父节点ID
// 返回 成功或者失败
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool saveDisableByParent(MAPNODE &mainnode, int nObjType, string szParentID)
{
    bool bSucc = true;
    OBJECT svObj = INVALID_VALUE;
    MAPNODE objNode = INVALID_VALUE;

    // 根据数据对象类型操作此对象父节点
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
        // 禁止状态 开始时间 终止时间
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
// 函数 makeDllName
// 说明 构造DLL的绝对路径
// 参数 const string & szDll，DLL文件的名称
// 返回 完成后的路径
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
string makeDllName(const string & szDll)
{
    string szDllName("");
    // 是否是演示版
    if(!isDemoMode())
        szDllName = GetSiteViewRootPath() + "\\fcgi-bin\\" + szDll;
    else
        szDllName = GetSiteViewRootPath() + "\\fcgi-bin\\GetRandomValue.dll";
    return szDllName;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 ReadWriteDynQueue
// 说明 在读写队列中读写动态数据
// 参数 
//      const string &szIndex，当前操作索引
//      const string &szDll，DLL名
//      const string &szFunc，函数名
//      const char *pszQuery，运行参数
//      const int &nSize，运行参数长度
//      char *pBuffer，数据缓冲区
//      int &nRetSize，缓冲区大小
// 返回 暂时未使用
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ReadWriteDynQueue(const string &szIndex, const string &szDll, const string &szFunc, const char *pszQuery, 
                       const int &nSize, char *pBuffer, int &nRetSize)
{
    static const string szLabel = "DYNPARAM";       // 动态参数
    static const string szDLLName = "DLL";          // DLL
    static const string szFUNC = "FUNC";            // FUNC
    static const string szParam = "PARAMS";         // 参数
    static const char szSeparator = '#';            // 分隔符

    bool bRet = false;
    // 得到刷新队列
    string szRefreshQueue(getRefreshQueueName(szIndex)), szQueueName(makeQueueName());
    // 参数队列， 回写队列
    string szParamQueue(szQueueName + "_R"), szRetQueue(szQueueName + "_W");
    // 创建回写队列
    CreateQueue(szRetQueue, 1, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
    // 创建参数队列
    CreateQueue(szParamQueue, 1, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
    // 创建刷新队列
    CreateQueue(szRefreshQueue, 1, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);

    // 数据大小
    int nDllSize = static_cast<int>(szDll.size()) + 2, nFuncSize = static_cast<int>(szFunc.size()) + 2;

    // 动态分配内存
    char *pDll = new char[nDllSize];
    if(pDll)
    {
        // 内存数据重设
        memset(pDll, 0, nDllSize);
        // 拷贝数据
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

                                    // 读取数据
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
    // 删除队列
    DeleteQueue(szRetQueue, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);

    return bRet;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 ReadFromRetQueue
// 说明 在指定队列中读取数据
// 参数 
//      const string &szQueue，指定队列
//      char *pBuffer，数据缓冲区
//      int &nRetSize，缓冲区大小
// 返回 暂时未使用
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
// 函数 getUsingNetworkCount
// 说明 得到已使用网络设备总数
// 参数 在增加监测器时指定设备索引
// 返回 已使用网络设备总数
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int  getUsingNetworkCount(string szDeviceID)
{
    PAIRLIST retlist; 
    PAIRLIST::iterator lsItem;
    int nNetworkCount = 0, nMonitorCount = 0; 
    list<string> lstMonitors;
    
    // 得到所有的网络设备 
    GetAllEntitysInfo(retlist, svNetworkSet, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);

    // 枚举每一个网络设备，计算已使用的网络设备点数
    for(lsItem = retlist.begin(); lsItem != retlist.end(); lsItem ++)
    {
        if((*lsItem).value == "true")
        {
            // 打开设备
            OBJECT objEntity = GetEntity((*lsItem).name,  CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
            if(objEntity != INVALID_VALUE)
            {// 打开成功
                // 得到隶属于该网络设备的所有监测器
                if(GetSubMonitorsIDByEntity(objEntity, lstMonitors))
                {
                    // 得到监测器总数
                    nMonitorCount = static_cast<int>(lstMonitors.size());
                    if(!szDeviceID.empty() && (*lsItem).name == szDeviceID)
                        nMonitorCount ++;
                    // 总数大于0且能被30整除
                    if(nMonitorCount == 30)
                        nNetworkCount ++;
                    else
                        nNetworkCount = nNetworkCount + nMonitorCount / 30 + 1;
                }
                else
                {
                    // 获得监测器失败已使用网络设备总数加1
                    nNetworkCount ++;
                }

                lstMonitors.clear();
                CloseEntity(objEntity);
            }
            else
            {// 失败，直接给已用设备点数加1
                nNetworkCount ++;
            }
        }
    }
    return nNetworkCount;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 getUsingMonitorCount
// 说明 得到已经使用的监测器总数
// 参数 无
// 返回 已使用监测器总数
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int  getUsingMonitorCount()
{
    PAIRLIST retlist;
    PAIRLIST::iterator lsItem;
    int nMonitorCount = 0, nPoint = 0;
    
    // 获得所有监测器并每个监测器带有点数属性
    GetAllMonitorsInfo(retlist, svIntPos, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
    for(lsItem = retlist.begin(); lsItem != retlist.end(); lsItem ++)
    {
        // 点数属性是否为空字符串
        if((*lsItem).value.empty())
        {// 为空
            // 监测器总数 加1
            nMonitorCount ++;
        }
        else
        {
            // 得到点数
            nPoint = atoi((*lsItem).value.c_str());
            if(nPoint <= 0)
                nPoint = 0;
            nMonitorCount += nPoint;
        }
    }
    return nMonitorCount;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 checkNetworkPoint
// 说明 校验网络设备总数是否超点
// 参数 待校验数据
// 返回 超点||不超点
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool checkNetworkPoint(int nNetworkCount)
{
	SafeDog pSafeDog;
	bool IsDogExit=false;
    string szNetworkCount ("");
	
    // 判断是否正式版，根据狗是否存在
	if( !pSafeDog.DogOnUsb(IsDogExit) )
	{
        // 正式版
        // 在狗中读取网络设备数
		if(!pSafeDog.GetDeviceNum(szNetworkCount))
		{
            // 如果是不限点
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
        // 试用版
        // 在general.ini文件中读取数据
		szNetworkCount = GetIniFileString("license", "nw", "",  "general.ini");
        char szOutput[512] = {0};
        Des des;
        if(des.Decrypt(szNetworkCount.c_str(), szOutput))
            szNetworkCount = szOutput;
        else
            return false;

        // 如果是不限点
        if(szNetworkCount == "9999")
            return true;

        int nPoint = atoi(szNetworkCount.c_str());
        if(nPoint < nNetworkCount)
            return false;
	}	
    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 checkMonitorsPoint
// 说明 校验监测器总数是否超点
// 参数 待校验监测器总数
// 返回 超点||不超点
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool checkMonitorsPoint(int nMonitorsCount)
{
	SafeDog pSafeDog;
	bool IsDogExit=false;
	string szPointCount ("");

    // 判断是否正式版，根据狗是否存在
	if(pSafeDog.DogOnUsb(IsDogExit)==0)
	{
        // 正式版
        // 在狗中读取可使用监测器总数
		if(!pSafeDog.GetNodeNum(szPointCount))
		{
            // 如果是不限点
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
        // 试用版
        // 在general.ini文件中读取数据
		szPointCount = GetIniFileString("license", "point", "",  "general.ini");
        char szOutput[512] = {0};
        Des des;
        if(des.Decrypt(szPointCount.c_str(), szOutput))
            szPointCount = szOutput;
        else
            return false;

        // 如果是不限点
        if(szPointCount == "9999")
            return true;

        int nPoint = atoi(szPointCount.c_str());

        if(nPoint < nMonitorsCount)
            return false;
	}	
    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 MakeRunParamStringByID
// 说明 根据设备ID索引枚举设备获得动态参数时的必要运行参数
// 参数 
//      const string szIndex设备索引
//      int nMTID 监测器模板名称
// 返回 使用\v分隔的运行参数
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
string MakeRunParamStringByID(const string &szIndex, int nMTID)
{
    string szRun("");
    // 打开设备
    OBJECT objDevice = GetEntity(szIndex, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
    if(objDevice != INVALID_VALUE)
    {
        // 得到主节点
        MAPNODE mainnode = GetEntityMainAttribNode(objDevice);
        if(mainnode != INVALID_VALUE)
        {
            string szDeviceType ("");
            map<string, string, less<string> > lsDeviceParam;
            // 得到设备类型
            if(FindNodeValue(mainnode, svDeviceType, szDeviceType))
            {
                // 打开设备模板
                OBJECT objDeviceTmp = GetEntityTemplet(szDeviceType, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
                if(objDeviceTmp != INVALID_VALUE)
                {
                    // 枚举全部的控制参数
                    LISTITEM lsItem;
                    if( FindETContrlFirst(objDeviceTmp, lsItem))
                    {
                        MAPNODE objNode;
                        while( (objNode = FindNext(lsItem)) != INVALID_VALUE )
                        {
                            string szName (""), szRun ("");
                            string szType ("");
                            // 得到参数名称，是否是必要参数，以及数据类型
                            FindNodeValue(objNode, svName, szName);
                            FindNodeValue(objNode, svRun, szRun);
                            FindNodeValue(objNode, svType, szType);
                            if(szRun == "true")
                                lsDeviceParam[szName] = szType;
                        }
                    }
                    // 关闭设备模板
                    CloseEntityTemplet(objDeviceTmp);
                }
            }

            // 在当前设备中枚举每一个必要运行参数
            map<string, string, less<string> >::iterator lstItem;
            for(lstItem = lsDeviceParam.begin(); lstItem != lsDeviceParam.end(); lstItem ++)
            {
                string szValue ("");
                FindNodeValue(mainnode, (lstItem->first), szValue);
                // 是否是密码类型
                if((lstItem->second).compare(svPassword) == 0)
                {
                    // 解密
                    char szOutput[512] = {0};
                    Des des;
                    if(des.Decrypt(szValue.c_str(), szOutput))
                        szValue = szOutput;
                }
                szRun = szRun + (lstItem->first) + "=" + szValue + "\v";
            }
        }
        // 关闭设备
        CloseEntity(objDevice);
    }

    char szTpl[32] = {0};
    sprintf(szTpl, "_TemplateID=%d", nMTID);
    szRun += szTpl;
    PrintDebugString(szRun);

    return szRun;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 AddTaskList
// 说明 添加任务计划到指定combobox
// 参数 
//      WComboBox * pTask待添加数据的combobox
// 返回 无
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AddTaskList(WComboBox * pTask)
{
    if(pTask)
    {
        list<string> lsTaskName;
        list<string>::iterator lsItem;

        // 得到所有的任务计划
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
// 函数 isDisable
// 说明 判断当前数据对象是否被禁止
// 参数
//      const string &szID数据对象索引
//      int nType类型
// 返回 禁止 || 不被禁止
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool isDisable(const string &szID, int nType)
{
    bool bDisable = false;

    // 根据类型打开不同对象
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

    // 是否打开成功
    if(objSV != INVALID_VALUE)
    {
        // 得到主节点
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
    
        // 判断是被禁止
        if(mainnode != INVALID_VALUE)
        {
            string szDisable ("");
            FindNodeValue(mainnode, svDisable, szDisable);
            if(szDisable == "true")
            {// 被禁止
                bDisable =  true;
            }
            else if( szDisable == "time")
            {// 被临时禁止
                // 判断当前时间是否在禁止时间段内
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
// 函数 isCanBePasteDevice
// 说明 是否可以粘贴指定设备
// 参数 
//      const string &szID待粘贴设备索引
// 返回 可以 || 不可以
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool isCanBePasteDevice(const string &szID)
{
    const CEccTreeNode *pNode = CEccTreeView::getECCObject(szID);
    if(pNode)
    {
        // 得到数上的设备节点
        CEccTreeDevice *pDevice = static_cast<CEccTreeDevice*>(const_cast<CEccTreeNode*>(pNode));
        if(pDevice->isNetworkSet() == "true")
        {// 此设备是网络设备
            int nNetworkCount = getUsingNetworkCount();

            int nMonitorCount = pDevice->getMointorCount();

            if(nMonitorCount == 30)
                nNetworkCount ++;
            else
                nNetworkCount = nNetworkCount + nMonitorCount / 30 + 1;

            return checkNetworkPoint(nNetworkCount);
        }
        else
        {// 不是网络设备
            int nMonitorCount = getUsingMonitorCount() + pDevice->getMointorCount();
            return checkMonitorsPoint(nMonitorCount);
        }
    }
    return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 PasteDevice
// 说明 将指定设备粘贴到目标组内，同时为新设备的中每个监测器创建数据表
// 参数
//      const string &szDestGroupID目标组
//      const string &szSrcDevID待粘贴设备
// 返回 新的设备索引（成功）或者空字符串
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
// 函数 createAllTableOfDevice
// 说明 为指定的设备内所有监测器创建数据表
// 参数 
//      const string &szDeviceIndex指定设备索引
// 返回 无
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void createAllTableOfDevice(const string &szDeviceIndex)
{
    // 得到树上的设备
    const CEccTreeNode *pNode = CEccTreeView::getECCObject(szDeviceIndex);
    CEccTreeDevice *pDevice = NULL;
    if(pNode)
        pDevice = static_cast<CEccTreeDevice*>(const_cast<CEccTreeNode*>(pNode));

    // 打开设备
    OBJECT objDevice = GetEntity(szDeviceIndex, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
    if(objDevice != INVALID_VALUE)
    {
        list<string> lsMonitorID;
        list<string>::iterator lstItem;
        // 得到此设备的所有监测器
        if (GetSubMonitorsIDByEntity(objDevice, lsMonitorID))
        {
            int nMTID = 0;
            string szName("");
            for(lstItem = lsMonitorID.begin(); lstItem != lsMonitorID.end(); lstItem ++)
            {
                szName = getMonitorNameMTID((*lstItem), nMTID);
                if(pDevice)
                    pDevice->AppendMonitor((*lstItem), szName, nMTID);
                // 创建数据表
                InsertTable((*lstItem), nMTID, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
            }
        }
        CloseEntity(objDevice);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 getMonitorNameMTID
// 说明 根据监测器索引得到监测器的名称和监测器模板的索引ID
// 参数 
//      const string &szMonitorID监测器索引
//      int &nMTID监测器模板的索引ID
// 返回 监测器的名称
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
string getMonitorNameMTID(const string &szMonitorID, int &nMTID)
{
    string szName("");
    // 打开监测器
    OBJECT objMonitor = GetMonitor(szMonitorID, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
    if(objMonitor != INVALID_VALUE)
    {
        // 得到主节点
        MAPNODE node = GetMonitorMainAttribNode(objMonitor);
        if(node != INVALID_VALUE)
        {
            // 得到名称和监测器模板
            FindNodeValue(node, svName, szName);
            string szMTID (""); FindNodeValue(node, svMonitorType, szMTID);
            nMTID = atoi(szMTID.c_str());
        }
        // 关闭监测器
        CloseMonitor(objMonitor);
    }
    return szName;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 函数 enumDeviceRunParam
// 说明 根据设备ID索引枚举设备获得动态参数时的必要运行参数
// 参数 
//      const string szIndex设备索引
// 返回 使用\v分隔的运行参数
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
string enumDeviceRunParam(const string &szDeviceIndex)
{
    string szQuery("");
    // 打开设备
    OBJECT objDevice = GetEntity(szDeviceIndex, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
    if(objDevice != INVALID_VALUE)
    {
        // 得到设备主节点
        MAPNODE mainnode = GetEntityMainAttribNode(objDevice);
        if(mainnode != INVALID_VALUE)
        {
            // 得到设备类型
            string szDeviceType("");
            map<string, string, less<string> > lsDeviceParam;
            if(FindNodeValue(mainnode, svDeviceType, szDeviceType))
            {
                // 打开设备模板
                OBJECT objDeviceTmp = GetEntityTemplet(szDeviceType, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
                if(objDeviceTmp != INVALID_VALUE)
                {
                    // 枚举每个参数
                    LISTITEM lsItem;
                    if( FindETContrlFirst(objDeviceTmp, lsItem))
                    {
                        MAPNODE objNode;
                        while( (objNode = FindNext(lsItem)) != INVALID_VALUE )
                        {
                            string szName(""), szRun("");
                            string szType("");
                            // 得到名称 是否是运行时参数 数据类型
                            FindNodeValue(objNode, svName, szName);
                            FindNodeValue(objNode, svRun, szRun);
                            FindNodeValue(objNode, svType, szType);
                            if(szRun == "true")
                                lsDeviceParam[szName] = szType;
                        }
                    }
                    // 关闭设备模板
                    CloseEntityTemplet(objDeviceTmp);
                }
            }
            // 在当前设备中枚举每个运行参数
            map<string, string, less<string> >::iterator lstItem;
            for(lstItem = lsDeviceParam.begin(); lstItem != lsDeviceParam.end(); lstItem ++)
            {
                string szValue("");
                FindNodeValue(mainnode, (lstItem->first), szValue);
                if((lstItem->second).compare(svPassword) == 0)
                {// 是否是密码类型数据
                    // 解密
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
        // 关闭设备
        CloseEntity(objDevice);
    }
    PrintDebugString(szQuery.c_str());
    return szQuery;
}

