#include "basefunc.h"

#include "../../opens/boost/regex.hpp"
#include "../../tools/usbdog/doglib/safedog.h"
#include "../../base/des.h"
#include "resstring.h"
//extern void PrintDebugString(const string &szMsg);

string makePath(string szIndex, string szIDCUser, string szIDCPwd)
{
    OBJECT objGroup;
    int nPos = static_cast<int>(szIndex.find("."));
    if(nPos < 0)
    {
        objGroup = GetSVSE(szIndex, szIDCUser, szIDCPwd);
        string szName ("");
        if(objGroup != INVALID_VALUE)
            szName = GetSVSELabel(objGroup);
        else
            szName = "localhost";
        CloseSVSE(objGroup);
        return szName;        
    }
    else
    {
        string szParent = FindParentID(szIndex);
        string szName ("");
        objGroup = GetGroup(szIndex, szIDCUser, szIDCPwd);
        if(objGroup != INVALID_VALUE)
        {
            MAPNODE node = GetGroupMainAttribNode(objGroup);
            if(node != INVALID_VALUE)
            {
                FindNodeValue(node, "sv_name", szName);  
            }
            CloseGroup(objGroup);
        }
        else
        {
            OBJECT objDevice = GetEntity(szIndex, szIDCUser, szIDCPwd);
            if(objDevice != INVALID_VALUE)
            {
                MAPNODE node = GetEntityMainAttribNode(objDevice);
                if(node != INVALID_VALUE)
                {
                    FindNodeValue(node, "sv_name", szName);  
                }
                CloseEntity(objDevice);
            } 
            else
            {
                OBJECT objMonitor = GetMonitor(szIndex, szIDCUser, szIDCPwd);
                if(objMonitor != INVALID_VALUE)
                {
                    MAPNODE node = GetMonitorMainAttribNode(objMonitor);
                    if(node != INVALID_VALUE)
                    {
                        FindNodeValue(node, "sv_name", szName);  
                    }
                    CloseMonitor(objMonitor);
                }
            }
        }
        return makePath(szParent, szIDCUser, szIDCPwd) + " : " + szName;
    }
}

int sv_split(const char* str, const char* delim, 
     list<string>& results, bool empties)
{
  char* pstr = const_cast<char*>(str);
  char* r = NULL;
  r = strstr(pstr, delim);
  int dlen = static_cast<int>(strlen(delim));
  while( r != NULL )
  {
    char* cp = new char[(r-pstr)+1];
    memcpy(cp, pstr, (r-pstr));
    cp[(r-pstr)] = '\0';
    if( strlen(cp) > 0 || empties )
    {
      string s(cp);
      results.push_back(s);
    }
    delete[] cp;
    pstr = r + dlen;
    r = strstr(pstr, delim);
  }
  if( strlen(pstr) > 0 || empties )
  {
    results.push_back(string(pstr));
  }
  return static_cast<int>(results.size());
}

int  getMonitorCountInList(list<string> &lsMonitors, string szIDCUser, string szIDCPwd)
{
    list<string>::iterator it;
    string szPoint("");
    int nMonitorCount = 0, nPoint = 0;
    for(it = lsMonitors.begin(); it != lsMonitors.end(); it++)
    {
        OBJECT objMonitor = GetMonitor((*it), szIDCUser, szIDCPwd);
        if(objMonitor != INVALID_VALUE)
        {
            MAPNODE node = GetMonitorMainAttribNode(objMonitor);
            if(node != INVALID_VALUE)
            {
                FindNodeValue(node, "sv_intpos", szPoint);
                if(szPoint.empty())
                {
                    nMonitorCount ++;
                }
                else
                {
                    nPoint = atoi(szPoint.c_str());
                    if(nPoint <= 0)
                        nPoint = 0;
                    nMonitorCount += nPoint;
                }
            }
            else
            {
                nMonitorCount ++;
            }

            CloseMonitor(objMonitor);
        }
        else
        {
            nMonitorCount ++;
        }
    }
    return nMonitorCount;
}

int  getUsingMonitorCount(string szIDCUser, string szIDCPwd)
{
    PAIRLIST retlist;
    PAIRLIST::iterator lsItem;
    int nMonitorCount = 0, nPoint = 0;
    
    // 获得所有监测器并每个监测器带有点数属性
    GetAllMonitorsInfo(retlist, "sv_intpos", szIDCUser, szIDCPwd);
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

int  getUsingNetworkCount(string szIDCUser, string szIDCPwd, string szDeviceID)
{
    PAIRLIST retlist; 
    PAIRLIST::iterator lsItem;
    int nNetworkCount = 0, nMonitorCount = 0; 
    list<string> lstMonitors;
    
    // 得到所有的网络设备 
    GetAllEntitysInfo(retlist, "sv_network", szIDCUser, szIDCPwd);

    // 枚举每一个网络设备，计算已使用的网络设备点数
    for(lsItem = retlist.begin(); lsItem != retlist.end(); lsItem ++)
    {
        if((*lsItem).value == "true")
        {
            // 打开设备
            OBJECT objEntity = GetEntity((*lsItem).name,  szIDCUser, szIDCPwd);
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
                    if(nMonitorCount % 30 == 0 && nMonitorCount > 0)
                        nNetworkCount = nNetworkCount + nMonitorCount / 30;
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

bool saveDisableByParent(MAPNODE &mainnode, int nObjType, string szParentID, string szIDCUser, string szIDCPwd)
{
    bool bNoError = true;
    
    OBJECT svObj = INVALID_VALUE;
    MAPNODE objNode = INVALID_VALUE;

    switch(nObjType)
    {
    case Tree_GROUP:
        svObj = GetGroup(szParentID, szIDCUser, szIDCPwd);
        if(svObj != INVALID_VALUE)
            objNode = GetGroupMainAttribNode(svObj);
        break;
    case Tree_DEVICE:
        svObj = GetEntity(szParentID, szIDCUser, szIDCPwd);
        if(svObj != INVALID_VALUE)
            objNode = GetEntityMainAttribNode(svObj);
        break;
    }
    
    if(objNode != INVALID_VALUE)
    {
        // 禁止状态 开始时间 终止时间
        string szDisable (""), szStartTime (""), szEndTime ("");
        FindNodeValue(objNode, "sv_disable", szDisable);
        FindNodeValue(objNode, "sv_starttime", szStartTime);
        FindNodeValue(objNode, "sv_endtime", szEndTime);

        AddNodeAttrib(mainnode, "sv_disable", szDisable);
        AddNodeAttrib(mainnode, "sv_starttime", szStartTime);
        AddNodeAttrib(mainnode, "sv_endtime", szEndTime);
    }
    switch(nObjType)
    {
    case Tree_GROUP:
        CloseGroup(svObj);
        break;
    case Tree_DEVICE:
        CloseEntity(svObj);
        break;
    }
    return bNoError;
}

bool checkNetworkPoint(int nNetworkCount)
{
	SafeDog pSafeDog;
	bool IsDogExit=false;
    string szNetworkCount ("");
	
	if( !pSafeDog.DogOnUsb(IsDogExit) )
	{
		if(!pSafeDog.GetDeviceNum(szNetworkCount))
		{
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
		szNetworkCount = GetIniFileString("license", "nw", "",  "general.ini");
        char szOutput[512] = {0};
        Des des;
        if(des.Decrypt(szNetworkCount.c_str(), szOutput))
            szNetworkCount = szOutput;
        else
            return false;

        if(szNetworkCount == "9999")
            return true;

        int nPoint = atoi(szNetworkCount.c_str());
        if(nPoint < nNetworkCount)
            return false;
	}	
    return true;
}

bool checkMonitorsPoint(int nMonitorsCount)
{
	SafeDog pSafeDog;
	bool IsDogExit=false;
	string szPointCount ("");
	if(pSafeDog.DogOnUsb(IsDogExit)==0)
	{
		if(!pSafeDog.GetNodeNum(szPointCount))
		{
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
		szPointCount = GetIniFileString("license", "point", "",  "general.ini");
        char szOutput[512] = {0};
        Des des;
        if(des.Decrypt(szPointCount.c_str(), szOutput))
            szPointCount = szOutput;
        else
            return false;

        if(szPointCount == "9999")
            return true;

        int nPoint = atoi(szPointCount.c_str());

        if(nPoint < nMonitorsCount)
            return false;
	}	
    return true;
}


unsigned getOperatePostion(string s, list<string> lstOperate, string &szCondition)
{
    int nPos = 0;
    list<string>::iterator lsItem;
    szCondition = "";
    for(lsItem = lstOperate.begin(); lsItem != lstOperate.end(); lsItem++)
    {
        nPos = static_cast<int>(s.find((*lsItem)));
        if(nPos > 0 )
        {
            if((*lsItem) == "==" || (*lsItem) == "!=")
            {
                szCondition = (*lsItem);
            }
            else if(nPos > 0 && (*lsItem) == "<")
            {
                if(s.c_str()[nPos + 1] == '=')
                    szCondition = "<=";
                else if(s.c_str()[nPos - 1] == ' ')
                    szCondition = "<";
            }
            else if(nPos > 0 && (*lsItem) == ">")
            {
                if(s.c_str()[nPos + 1] == '=')
                    szCondition = ">=";
                else if(s.c_str()[nPos - 1] == ' ')
                    szCondition = ">";
            }
            else if(nPos > 0 && (*lsItem) == "contains")
            {
                if(s.c_str()[nPos - 1] == '!')
                {
                    nPos -= 1;
                    szCondition = "!contains";
                }
                else
                    szCondition = "contains";
            }
            break;
        }
    }
    return nPos;
}

unsigned getCondition(list<string>& lst, string s)
{
    static const boost::regex e("\\s+(and|or)\\s+");
    return static_cast<int>(boost::regex_split(std::back_inserter(lst), s, e));
}

unsigned getParam(list<string>&lst, string s)
{
    static const boost::regex e("([^\\[\\]]+)(?=\\])");
    return static_cast<int>(boost::regex_split(std::back_inserter(lst), s, e));
}

string getDeviceNameByType(string szDeviceType, string szIDCUser, string szIDCPwd)
{
    string szName ("");
    OBJECT objDevice = GetEntityTemplet(szDeviceType, szIDCUser, szIDCPwd);
    if(objDevice != INVALID_VALUE)
    {
        MAPNODE node = GetEntityTempletMainAttribNode(objDevice);
        if(node != INVALID_VALUE)
        {
            if(!FindNodeValue(node, "sv_label", szName))
                FindNodeValue(node, "sv_name", szName);
            else
                szName = SVResString::getResString(szName.c_str());
        }

        CloseEntityTemplet(objDevice);
    }
    return szName;
}

int isDeviceDisable(string &szDeviceID, string szIDCUser, string szIDCPwd)
{
    int nDisable = sv_enable_state;
    OBJECT objMonitor = GetEntity(szDeviceID, szIDCUser, szIDCPwd);
    if(objMonitor != INVALID_VALUE)
    {
        MAPNODE mainnode = GetEntityMainAttribNode(objMonitor);
        if(mainnode != INVALID_VALUE)
        {
            string szDisable ("");
            FindNodeValue(mainnode, "sv_disable", szDisable);
            if(szDisable == "true")
            {
                nDisable = sv_disable_state;
            }
            else if( szDisable == "time")
            {
                string szEndTime ("");
                FindNodeValue(mainnode, "sv_endtime", szEndTime);
                int nYear = 0, nMonth = 0, nDay = 0;
                int nHour = 0, nMinute = 0;
                if(!szEndTime.empty())
                {
                    sscanf(szEndTime.c_str(), "%d - %d - %d - %d : %d", &nYear, &nMonth, &nDay, &nHour, &nMinute);
                    svutil::TTime ttime = svutil::TTime::GetCurrentTimeEx();
                    svutil::TTime ttend = TTime::TTime(nYear, nMonth, nDay, nHour, nMinute, 0);
                    if(ttime < ttend)
                        nDisable = sv_time_state;                        
                }
            }
        }
        CloseEntity(objMonitor);
    }
    return nDisable;
}

int isGroupDisable(string &szGroupID, string szIDCUser, string szIDCPwd)
{
    int nDisable = sv_enable_state;
    OBJECT objMonitor = GetGroup(szGroupID, szIDCUser, szIDCPwd);
    if(objMonitor != INVALID_VALUE)
    {
        MAPNODE mainnode = GetGroupMainAttribNode(objMonitor);
        if(mainnode != INVALID_VALUE)
        {
            string szDisable ("");
            FindNodeValue(mainnode, "sv_disable", szDisable);
            if(szDisable == "true")
            {
                nDisable = sv_disable_state;
            }
            else if( szDisable == "time")
            {
                string szEndTime ("");
                FindNodeValue(mainnode, "sv_endtime", szEndTime);
                int nYear = 0, nMonth = 0, nDay = 0;
                int nHour = 0, nMinute = 0;
                if(!szEndTime.empty())
                {
                    sscanf(szEndTime.c_str(), "%d - %d - %d - %d : %d", &nYear, &nMonth, &nDay, &nHour, &nMinute);
                    
                    svutil::TTime ttime = svutil::TTime::GetCurrentTimeEx();

                    svutil::TTime ttend = TTime::TTime(nYear, nMonth, nDay, nHour, nMinute, 0);
                    if(ttime < ttend)
                        nDisable =  sv_time_state;                  
                }
            }
        }
        CloseGroup(objMonitor);
    }
    return nDisable;
}

bool isMonitorDisable(string &szMonitorID, string szIDCUser, string szIDCPwd)
{
    bool bDisable = false;
    OBJECT objMonitor = GetMonitor(szMonitorID, szIDCUser, szIDCPwd);
    if(objMonitor != INVALID_VALUE)
    {
        MAPNODE mainnode = GetMonitorMainAttribNode(objMonitor);
        if(mainnode != INVALID_VALUE)
        {
            string szDisable ("");
            FindNodeValue(mainnode, "sv_disable", szDisable);
            if(szDisable == "true")
            {
                bDisable =  true;
            }
            else if( szDisable == "time")
            {
                string szEndTime ("");
                FindNodeValue(mainnode, "sv_endtime", szEndTime);
                int nYear = 0, nMonth = 0, nDay = 0;
                int nHour = 0, nMinute = 0;
                if(!szEndTime.empty())
                {
                    sscanf(szEndTime.c_str(), "%d - %d - %d - %d : %d", &nYear, &nMonth, &nDay, &nHour, &nMinute);
                    
                    svutil::TTime ttime = svutil::TTime::GetCurrentTimeEx();

                    svutil::TTime ttend = TTime::TTime(nYear, nMonth, nDay, nHour, nMinute, 0);
                    if(ttime < ttend)
                        bDisable =  true;                        
                }
            }
        }
        CloseMonitor(objMonitor);
    }
    return bDisable;
}

int getDeviceSimpleState(string szDeviceIndex, string szIDCUser, string szIDCPwd)
{
    int ndevState = dyn_normal;
    if(!szDeviceIndex.empty())
    {
        if(isDeviceDisable(szDeviceIndex, szIDCUser, szIDCPwd) == sv_enable_state)
        {
            OBJECT entity = GetEntity(szDeviceIndex, szIDCUser, szIDCPwd);
            if (entity != INVALID_VALUE)
            {   
                list<string> lstMonitors;
                list<string>::iterator lstItem;
                if(GetSubMonitorsIDByEntity(entity, lstMonitors))
                {
                    sv_dyn dyn; 
                    for(lstItem = lstMonitors.begin(); lstItem != lstMonitors.end(); lstItem ++)
                    {
                        if(ndevState != dyn_error)
                        {
                            string szMonitorID = (*lstItem).c_str(); 
                            if(GetSVDYNNODisplayString(szMonitorID, dyn, szIDCUser, szIDCPwd))
                            {
                                switch(dyn.m_state)
                                {
                                case dyn_no_data:                               
                                case dyn_normal:
                                    if(ndevState != dyn_warnning)
                                        ndevState = dyn_normal;
                                    break;                                
                                case dyn_disable:
                                    break;
                                case dyn_warnning:
                                    ndevState = dyn_warnning;
                                    break;
                                case dyn_error:
                                case dyn_bad:
                                    ndevState = dyn_error;
                                    break;
                                }
                            }
                        }
                        else
                        {
                            break;
                        }
                    }
                }
                CloseEntity(entity);
            }
        }
        else
        {
            ndevState = dyn_disable;
        }
    }
    return ndevState;
}

void getDeviceState(string szDeviceIndex,sv_device_state &devState, string szIDCUser, string szIDCPwd)
{
    if(!szDeviceIndex.empty())
    {
        list<string> lstMonitors;
        list<string>::iterator lstItem;
        OBJECT entity = GetEntity(szDeviceIndex, szIDCUser, szIDCPwd);
        if (entity != INVALID_VALUE)
        {
            MAPNODE node = GetEntityMainAttribNode(entity);
            if(node != INVALID_VALUE)
            {
                string szDeviceType (""), szOSName ("");
                FindNodeValue(node, "sv_devicetype", szDeviceType);
                FindNodeValue(node, "_OsType", szOSName);
                if(!szOSName.empty())
                    szOSName = GetIniFileString(szOSName, "description", "", "oscmd.ini");;
                if(!szDeviceType.empty())
                    szDeviceType = getDeviceNameByType(szDeviceType);
                if(!szDeviceType.empty())
                {
                    devState.pszDeviceType = new char[szDeviceType.length() + 1];
                    strcpy(devState.pszDeviceType, szDeviceType.c_str());
                }
                if(!szOSName.empty())
                {
                    devState.pszOSName = new char[szOSName.length() + 1];
                    strcpy(devState.pszOSName, szOSName.c_str());
                }
            }
            if(GetSubMonitorsIDByEntity(entity, lstMonitors))
            {
                sv_dyn dyn;
                string szMonitorID("");             
                devState.nMonitorCount = static_cast<int>(lstMonitors.size());
                for(lstItem = lstMonitors.begin(); lstItem != lstMonitors.end(); lstItem ++)
                {
                    szMonitorID = (*lstItem).c_str();
                    if(GetSVDYNNODisplayString(szMonitorID, dyn, szIDCUser, szIDCPwd))
                    {
                        switch(dyn.m_state)
                        {
                        case dyn_no_data:
                            break;
                        case dyn_normal:
                            break;
                        case dyn_disable:
                            devState.nDisableCount ++;
                            break;
                        case dyn_warnning:
                            devState.nWarnCount ++;
                            break;
                        case dyn_error:
                        case dyn_bad:
                            devState.nErrorCount ++;
                            break;
                        }
                        if(devState.m_time < dyn.m_time)
                            devState.m_time = dyn.m_time;
                    }
                }
            }
            CloseEntity(entity);
        }
    }
    if(devState.nErrorCount > 0)
        devState.nState = 3;
    else if(devState.nWarnCount > 0)
        devState.nState = 2;
}

sv_group_state getGroupState(string szGroupIndex, CUser *pUser, string szIDCUser, string szIDCPwd)
{
    if(IsSVSEID(szGroupIndex))
        return getSVSEState(szGroupIndex, pUser, szIDCUser, szIDCPwd);

    sv_group_state state;
    list<string> lsGroupID;
    list<string> lsEntityID;
    list<string>::iterator lstItem;
    if(!szGroupIndex.empty())
    {
        OBJECT group = GetGroup(szGroupIndex, szIDCUser, szIDCPwd);
        if(group != INVALID_VALUE)
        {
            ///////////////////////////////////////////////////////////////////////////////////////////////////
            // 删除每一个设备
            if(GetSubEntitysIDByGroup(group, lsEntityID))            
            {
                sv_device_state devState;
                bool bHasRight = true;
                for(lstItem = lsEntityID.begin(); lstItem != lsEntityID.end(); lstItem ++)
                {
                    string szEntityID = (*lstItem).c_str();
                    if(pUser)
                        bHasRight = pUser->haveGroupRight(szEntityID, Tree_DEVICE);
                    if(bHasRight)
                    {
                        state.nDeviceCount ++;
                        getDeviceState(szEntityID, devState, szIDCUser, szIDCPwd);
                        state.nMonitorCount += devState.nMonitorCount;
                        state.nErrorCount += devState.nErrorCount;
                        state.nWarnCount += devState.nWarnCount;
                        state.nDisableCount += devState.nDisableCount;
                        if(state.m_time < devState.m_time)
                            state.m_time = devState.m_time;
                    }
                    devState.reset();
                }
                devState.reset();
            }
            ///////////////////////////////////////////////////////////////////////////////////////////////////
            // 删除每一个子组
            if(GetSubGroupsIDByGroup(group, lsGroupID))
            {
                sv_group_state groupState;
                bool bHasRight = true;
                for(lstItem = lsGroupID.begin(); lstItem != lsGroupID.end(); lstItem ++)
                {
                    string szSubGroupID = (*lstItem).c_str();
                    if(pUser)
                        bHasRight = pUser->haveGroupRight(szSubGroupID, Tree_GROUP);
                    if(bHasRight)
                    {
                        groupState = getGroupState(szSubGroupID, pUser, szIDCUser, szIDCPwd);
                        state.nMonitorCount += groupState.nMonitorCount;
                        state.nErrorCount += groupState.nErrorCount;
                        state.nWarnCount += groupState.nWarnCount;
                        state.nDeviceCount += groupState.nDeviceCount;
                        state.nDisableCount += groupState.nDisableCount;
                        if(state.m_time < groupState.m_time)
                            state.m_time = groupState.m_time;
                    }
                    groupState.reset();
                }                
            }
            CloseGroup(group);
        }        
    }
    if(state.nErrorCount > 0)
        state.nState = 3;
    else if(state.nWarnCount > 0)
        state.nState = 2;
    return state;
}

sv_group_state getSVSEState(string szSVSEIndex, CUser *pUser, string szIDCUser, string szIDCPwd)
{
    sv_group_state state;
    OBJECT objSE = GetSVSE(szSVSEIndex, szIDCUser, szIDCPwd);
    list<string> lsGroupID;
    list<string> lsDeviceID;
    list<string>::iterator lstItem;
    if(objSE != INVALID_VALUE)
    {
        if(GetSubGroupsIDBySE(objSE, lsGroupID))
        {  
            sv_group_state groupState;

            bool bHasRight = true;
            for(lstItem = lsGroupID.begin(); lstItem != lsGroupID.end(); lstItem ++)
            {
                string szSubGroupID = (*lstItem).c_str();
                if(pUser)
                    bHasRight = pUser->haveGroupRight(szSubGroupID, Tree_GROUP);
                if(bHasRight)
                {
                    groupState = getGroupState(szSubGroupID, pUser, szIDCUser, szIDCPwd);
                    state.nMonitorCount += groupState.nMonitorCount;
                    state.nErrorCount += groupState.nErrorCount;
                    state.nWarnCount += groupState.nWarnCount;
                    state.nDeviceCount += groupState.nDeviceCount;
                    state.nDisableCount += groupState.nDisableCount;
                    if(state.m_time < groupState.m_time)
                        state.m_time = groupState.m_time;
                }
                groupState.reset();
            }
        }

        if(GetSubEntitysIDBySE(objSE, lsDeviceID))
        {
            sv_device_state devState;
            bool bHasRight = true;
            for(lstItem = lsDeviceID.begin(); lstItem != lsDeviceID.end(); lstItem ++)
            {
                string szEntityID = (*lstItem).c_str();
                if(pUser)
                    bHasRight = pUser->haveGroupRight(szEntityID, Tree_DEVICE);
                if(bHasRight)
                {
                    state.nDeviceCount ++;
                    getDeviceState(szEntityID, devState, szIDCUser, szIDCPwd);
                    state.nMonitorCount += devState.nMonitorCount;
                    state.nErrorCount += devState.nErrorCount;
                    state.nWarnCount += devState.nWarnCount;
                    state.nDisableCount += devState.nDisableCount;
                    if(state.m_time < devState.m_time)
                        state.m_time = devState.m_time;
                }
                devState.reset();
            }
        }
        CloseSVSE(objSE);
    }
    return state;
}

string strtriml(const char * str1)
{
    string szValue ("");
    if (str1 && strlen(str1) > 0)
    {    
        char * cp = strdup(str1);
        if (cp)
        {    
            char * pos = cp;
            while (*pos)
            {
                if ( *pos == ' ' || *pos == '\r' || *pos == '\n' || *pos == '\t' )
                {
                    *pos = '\0';
                    pos ++;
                }
                else
                {
                    break;
                }
            }
            szValue = pos;
        }
        free(cp);
    }
    return szValue;
}

string strtrimr(const char * str1)
{
    string szValue ("");
    if(str1 && strlen(str1) > 0)
    {    
        char *chTemp = strdup(str1);
        if(chTemp)
        {
            char * cp = chTemp + (strlen(chTemp) - 1);
            while (*cp)
            {
                if ( *cp == ' ' || *cp == '\r' || *cp == '\n' || *cp == '\t')
                {
                    *cp = '\0';
                    cp --;
                }
                else
                {
                    break;
                }
            }
            szValue = chTemp;
            free(chTemp);
        }
    }
    return szValue;
}

string url_Encode(const char* pszValue)
{
    string szEnUrl ("");
    int nSize = static_cast<int>(strlen(pszValue) * 3) + 1;
    char *chEncode = new char[nSize];

    const char *pPos = pszValue;
    if(chEncode)
    {
        memset(chEncode, 0, nSize);
        char *pTmp = chEncode;
        while(*pPos != '\0')
        {
            if(*pPos >= 48 && *pPos <= 57)
            {
                *pTmp = *pPos;
                pTmp ++;
            }
            else if(*pPos >= 65 && *pPos <= 90)
            {
                *pTmp = *pPos;
                pTmp ++;
            }
            else if(*pPos >= 97 && *pPos <= 122)
            {
                *pTmp = *pPos;
                pTmp ++;
            }
            else if(*pPos == '.')
            {
                *pTmp = *pPos;
                pTmp ++;
            }
            else if(*pPos >=0 && *pPos <= 255)
            {
                *pTmp = '%';
                pTmp++;
                sprintf(pTmp, "%x", *pPos);
                pTmp += 2;
            }
            pPos++;
        }

        szEnUrl = chEncode; 
        delete []chEncode;
    }
    return szEnUrl;
}

string getMonitorNameMTID(string &szMonitorID, int &nMTID, string szIDCUser, string szIDCPwd)
{
    string szName("");
    OBJECT objMonitor = GetMonitor(szMonitorID,szIDCUser, szIDCPwd);
    if(objMonitor != INVALID_VALUE)
    {
        MAPNODE node = GetMonitorMainAttribNode(objMonitor);
        if(node != INVALID_VALUE)
        {
            FindNodeValue(node, "sv_name", szName);
            string szMTID (""); FindNodeValue(node, "sv_monitortype", szMTID);
            nMTID = atoi(szMTID.c_str());
        }
        CloseMonitor(objMonitor);
    }
    return szName;
}

char *buildbuf(string szData, char *pt, int &nBuflen)
{
	if(szData.empty()) 
        szData = " ";

    if(pt == NULL)
        return NULL;

    if(nBuflen < static_cast<int>(szData.length() + 1))
        return NULL;

    strcpy(pt, szData.c_str());

    pt += (szData.length() + 1);
    //(*pt) = '\0';
    //pt ++;
    
    nBuflen -= static_cast<int>(szData.length() + 1);

    return pt;
}

void DumpLog(const char * pszFileName, const char *pBuffer, const int nLen)
{
    FILE *fp = fopen (pszFileName, "w");
    if(fp)
    {
        fprintf(fp, "%s", pBuffer);
        //for (int i = 0; i < nLen; ++i)
        //{
        //    if (i != 0 && (i & 0xf) == 0)
	       // fprintf (fp, "\n");
        //    fprintf (fp, "%02x ", pBuffer[i]);
        //}
        fprintf (fp, "\n");
    }
    fclose(fp);
}

string GetDeviceTypeById(string &szDeviceID, string szIDCUser, string szIDCPwd)
{
    string strType ("");
    if(!szDeviceID.empty())
    {
        OBJECT objDevice = GetEntity(szDeviceID,  szIDCUser, szIDCPwd);
        if(objDevice != INVALID_VALUE)
        {
            MAPNODE mainnode = GetEntityMainAttribNode(objDevice);

            if(mainnode != INVALID_VALUE)
            {
                FindNodeValue(mainnode, "sv_devicetype", strType);
            }

            CloseEntity(objDevice);
        }
    }

    return strType;
}

string getDeviceNameByID(string szDeviceID, string szIDCUser, string szIDCPwd)
{
    string szName("");
    OBJECT objDevice = GetEntity(szDeviceID,  szIDCUser, szIDCPwd);
    if(objDevice != INVALID_VALUE)
    {
        MAPNODE mainnode = GetEntityMainAttribNode(objDevice);

        if(mainnode != INVALID_VALUE)
        {
            FindNodeValue(mainnode, "sv_name", szName);
        }

        CloseEntity(objDevice);
    }
    return szName;
}

string getGroupNameByID(string szGroupID, string szIDCUser, string szIDCPwd)
{
    string szName;
    OBJECT objGroup = INVALID_VALUE;
    bool bIsSE = IsSVSEID(szGroupID);
    if(bIsSE)
        objGroup = GetSVSE(szGroupID, szIDCUser, szIDCPwd);
    else
       objGroup = GetGroup(szGroupID,  szIDCUser, szIDCPwd);
    if(objGroup != INVALID_VALUE)
    {
        MAPNODE mainnode = INVALID_VALUE;
        if(bIsSE)
            szName = GetSVSELabel(objGroup);
        else
            mainnode = GetGroupMainAttribNode(objGroup);
        if(mainnode != INVALID_VALUE)
            FindNodeValue(mainnode, "sv_name", szName);

        if(bIsSE)
            CloseSVSE(objGroup);
        else
            CloseGroup(objGroup);
    }
    return szName;
}

string makeDllName(const string & szDll)
{
    string szDllName("");
    if(!isDemoMode())
        szDllName = GetSiteViewRootPath() + "\\fcgi-bin\\" + szDll;
    else
        szDllName = GetSiteViewRootPath() + "\\fcgi-bin\\GetRandomValue.dll";
    return szDllName;
}

bool ReadWriteDynQueue(const string &szIndex, const string &szDll, const string &szFunc, const char *pszQuery, 
                       const int &nSize, char *pBuffer, int &nRetSize, string szIDCUser, string szIDCPwd)
{
    static const string szLabel = "DYNPARAM";
    static const string szDLLName = "DLL";
    static const string szFUNC = "FUNC";
    static const string szParam = "PARAMS";
    static const char szSeparator = '#';

    bool bRet = false;
    string szRefreshQueue(getRefreshQueueName(szIndex)), szQueueName(makeQueueName());
    string szParamQueue(szQueueName + "_R"), szRetQueue(szQueueName + "_W");
    CreateQueue(szRetQueue, 1, szIDCUser, szIDCPwd);
    CreateQueue(szParamQueue, 1, szIDCUser, szIDCPwd);
    CreateQueue(szRefreshQueue, 1, szIDCUser, szIDCPwd);

    int nDllSize = static_cast<int>(szDll.size()) + 2, nFuncSize = static_cast<int>(szFunc.size()) + 2;

    char *pDll = new char[nDllSize];
    if(pDll)
    {
        memset(pDll, 0, nDllSize);
        strcpy(pDll, szDll.c_str());
        if(PushMessage(szParamQueue, szDLLName, pDll, nDllSize, szIDCUser, szIDCPwd))
        {
            char *pFunc = new char[nFuncSize];
            if(pFunc)
            {
                memset(pFunc, 0, nFuncSize);
                strcpy(pFunc, szFunc.c_str());
                if(PushMessage(szParamQueue, szFUNC, pFunc, nFuncSize, szIDCUser, szIDCPwd))
                {
                    if(PushMessage(szParamQueue, szParam, pszQuery, nSize, szIDCUser, szIDCPwd))
                    {
                        //string szQueue = szQueueName;// + szSeparator + szRetQueue;
                        int nQueueSize = static_cast<int>(szQueueName.size()) + 2;
                        char *pszQueue = new char[nQueueSize];
                        if(pszQueue)
                        {
                            memset(pszQueue, 0, nQueueSize);
                            strcpy(pszQueue, szQueueName.c_str());
                            if(PushMessage(szRefreshQueue, szLabel, pszQueue, nQueueSize, szIDCUser, szIDCPwd))
                            {
                                int nTimes = 0;
                                while(!bRet)
                                {
                                    if(nTimes >= 40)
                                        break;
                                    bRet = ReadFromRetQueue(szRetQueue, pBuffer, nRetSize, szIDCUser, szIDCPwd);
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
    DeleteQueue(szRetQueue, szIDCUser, szIDCPwd);

    return bRet;
}

bool ReadFromRetQueue(const string &szQueue, char *pBuffer, int &nRetSize, string szIDCUser, string szIDCPwd)
{
    bool bRet = false;
    static const string szDynLabel = "DYNPARAM";
    static const string szEnd   = "DYNEND";

    MQRECORD mrd = PopMessage(szQueue, 2000, szIDCUser, szIDCPwd);
	if(mrd != INVALID_VALUE)
	{
        string szLabel("");
        svutil::TTime ct;
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

void createAllTableOfDevice(string &szDeviceIndex, string szIDCUser, string szIDCPwd)
{
    OBJECT objDevice = GetEntity(szDeviceIndex,  szIDCUser, szIDCPwd);
    if(objDevice != INVALID_VALUE)
    {
        list<string> lsMonitorID;
        list<string>::iterator lstItem;
        if (GetSubMonitorsIDByEntity(objDevice, lsMonitorID))
        {
            int nMTID = 0;
            for(lstItem = lsMonitorID.begin(); lstItem != lsMonitorID.end(); lstItem ++)
            {
                getMonitorNameMTID((*lstItem), nMTID, szIDCUser, szIDCPwd);
                InsertTable((*lstItem), nMTID, szIDCUser, szIDCPwd);
            }
        }
    }
}

