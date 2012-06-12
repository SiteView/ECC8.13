/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// adddevice1st.cpp
// 添加设备的第一步，选择设备类型（显示信息包括设备组和设备模板显示名称）
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "adddevice1st.h"
#include "listtable.h"
#include "resstring.h"
#include "mainview.h"
#include "rightview.h"
#include "basedefine.h"
#include "treeview.h"

#include "../../opens/libwt/WebSession.h"
#include "../../opens/libwt/WTableCell"
#include "../../opens/libwt/WText"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 构造函数
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
CEccAddDevice1st::CEccAddDevice1st(WContainerWidget *parent):
CEccBaseTable(parent),
m_szParentId("")
{
    setStyleClass("panel");
    initForm(false);
    connect(&m_MapperOfDT, SIGNAL(mapped(const std::string)), this, SLOT(AddDeviceByType(const std::string)));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 析构函数
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
CEccAddDevice1st::~CEccAddDevice1st()
{
    // 移除消息绑定
    removeMapping();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 移除消息绑定
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice1st::removeMapping()
{
    list<WText*>::iterator it;
    // 移除每条数据
    for(it = m_lsText.begin(); it != m_lsText.end(); it++)
        m_MapperOfDT.removeMappings((*it));
    // 可交互文字列表清空
    m_lsText.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 初始化
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice1st::initForm(bool bHasHelp)
{
    // 基础类初始化
    CEccBaseTable::initForm(bHasHelp);

    // 创建标题
    createTitle();
    // 创建操作
    createOperate();
    // 枚举设备组模板和设备模板
    if(m_pContent)
    {
        CEccBaseTable::setContentCellStyle("height95p");
        enumDeviceGroup();
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 创建标题
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice1st::createTitle()
{
    // 设置标题文字
    if(m_pTitle)
        m_pTitle->setText(SVResString::getResString("IDS_Add_Device_Title"));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 枚举设备模板组
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice1st::enumDeviceGroup()
{
    PAIRLIST lsDGName;
    PAIRLIST::iterator lsItem;

    map<int, string, less<int> > mapET;
    map<int, string, less<int> > mapETGroup;
    map<int, string, less<int> >::iterator mapETItem;
    map<int, string, less<int> >::iterator mapItem;

	OutputDebugString(" enumDeviceGroup++++++++ \n");

    // 得到所有的设备组
    if(GetAllEntityGroups(lsDGName, svLabel, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr) || 
        GetAllEntityGroups(lsDGName, svName, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr))
    {// 成功
        list<string> lsDevice;
        list<string>::iterator lstItem;
        string szHidden(""), szIndex("");
		
        for(lsItem = lsDGName.begin(); lsItem != lsDGName.end(); lsItem ++)
        {// 枚举每一个设备组
            string szValue = SVResString::getResString((*lsItem).value.c_str());
            string szID = (*lsItem).name;
            // 打开设备组
            OBJECT objDG = GetEntityGroup(szID, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
            if(objDG != INVALID_VALUE)
            {// 打开设备组成功
                // 得到 Main MAPNODE
                szHidden = "";
                szIndex = "";
                MAPNODE node = GetEntityGroupMainAttribNode(objDG);
                if(node != INVALID_VALUE)
                {
                    FindNodeValue(node, svHidden, szHidden); // 是否隐藏
                    FindNodeValue(node, svShowIndex, szIndex);   // 显示索引
                }
				//OutputDebugString(" GetEntityGroup++++++++ \n");

                if(szHidden != "true")
                {// 不是隐藏组
                    if(!szIndex.empty())
                    {// 显示顺序已定义
                        mapETGroup[atoi(szIndex.c_str())] = szID;
                    }
                    else
                    {
						//OutputDebugString(" else++++++++ \n");

                        int nRow = m_pContent->numRows();
                        // 创建隐藏/显示功能表
                        CEccListTable * pTable = new CEccListTable(m_pContent->elementAt(nRow, 0), false, false, false);
                        if(pTable)
                        {// 创建带隐藏/显示功能表成功
                            // 设置此表标题
                            if(!szValue.empty())
                                pTable->setTitle(szValue.c_str());
                            else
                                pTable->setTitle(szID.c_str());
                            
                            // 清理 设备模板 列表
                            lsDevice.clear();
                            WTable *pSubTable = pTable->getListTable();
                            if(GetSubEntityTempletIDByEG(lsDevice, objDG) && pSubTable)
                            {// 
                                for(lstItem = lsDevice.begin(); lstItem != lsDevice.end(); lstItem ++)
                                {// 枚举每一个设备模板
                                    string szDeviceID = (*lstItem).c_str(); 
                                    AddDeviceTemplet(szDeviceID, pSubTable);
                                }
                            }
							//nIndexDeviceGroup++;
							//if(nIndexDeviceGroup<4 )
							//OutputDebugString(" nIndexDeviceGroup++ \n");

							//pTable->showSubTable();

                        }
                    }
                }
                // 关闭设备模板组
                CloseEntityGroup(objDG);
            }
        }

        string szName("");
        // 根据显示顺序 创建设备组表
		int nIndexDeviceGroup=0;
        for(mapItem = mapETGroup.begin(); mapItem != mapETGroup.end(); mapItem ++)
        {
            OBJECT objDG = GetEntityGroup(mapItem->second, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
            if(objDG != INVALID_VALUE)
            {
                MAPNODE node = GetEntityGroupMainAttribNode(objDG);
                if(node != INVALID_VALUE)
                {
                    szName = ("");
                    if(!FindNodeValue(node, svLabel, szName))
                        FindNodeValue(node, svName, szName);
                    else
                        szName = SVResString::getResString(szName.c_str());

                    int nRow = m_pContent->numRows();
                    CEccListTable * pTable = new CEccListTable(m_pContent->elementAt(nRow, 0), false, false, false);
                    if(pTable)
                    {
                        pTable->setTitle(szName.c_str());
                        lsDevice.clear();

                        WTable *pSubTable = pTable->getListTable();
                        if(GetSubEntityTempletIDByEG(lsDevice, objDG) && pSubTable)
                        {
                            for(lstItem = lsDevice.begin(); lstItem != lsDevice.end(); lstItem ++)
                            {
                                string szDeviceID = (*lstItem).c_str();
                                AddDeviceTemplet(szDeviceID, pSubTable);
                            }
                        }
						//前3个展示
						nIndexDeviceGroup++;
						if(nIndexDeviceGroup>3 )
								pTable->hideSubTable();
                    }
                }
                CloseEntityGroup(objDG);
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 说明 添加设备模板
// 参数
//      设备类型
//      待添加此设备模板的表
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice1st::AddDeviceTemplet(string szDTName, WTable *pSubTable)
{
    // 得到 设备模板入口点
    OBJECT objDevice = GetEntityTemplet(szDTName, CEccMainView::m_szIDCUser, CEccMainView::m_szAddr);
    if(objDevice != INVALID_VALUE)
    {

        list<int> lsMTID;
        // 得到设备能使用的监测器模板列表
        if(GetSubMonitorTypeByET(objDevice, lsMTID))
            CEccMainView::m_pTreeView->InsertDevMTList(szDTName, lsMTID);

        MAPNODE node = GetEntityTempletMainAttribNode(objDevice);
        if(node != INVALID_VALUE)
        {
            string szLabel(""), szName(""), szHidden("");
            if(FindNodeValue(node, svDescription, szLabel))      // 说明
                szLabel = SVResString::getResString(szLabel.c_str());

            if(!FindNodeValue(node, svLabel, szName))
                FindNodeValue(node, svName, szName);             // 名称
            else
                szName = SVResString::getResString(szName.c_str());

            FindNodeValue(node, svHidden, szHidden);             // 是否隐藏
            if(szHidden != "true")
            {
                // 得到当前行
                int nRow = pSubTable->numRows();
                if(!szName.empty())
                {
                    // 创建 文本（模板的名称）
                    WText *pName = new WText(szName, pSubTable->elementAt(nRow, 0));
                    if(pName)
                    {
                        connect(pName, SIGNAL(clicked()), "showbar();" ,  &m_MapperOfDT, SLOT(map()), 
                            WObject::ConnectionType::JAVASCRIPTDYNAMIC);

                        m_MapperOfDT.setMapping(pName, szDTName);

                        // 样式表（颜色：#669 ）
                        sprintf(pName->contextmenu_, "style='color:#1E5B99;cursor:pointer;' onmouseover='" \
                            "this.style.textDecoration=\"underline\"' " \
                            "onmouseout='this.style.textDecoration=\"none\"'");
                        pName->setToolTip(szLabel);
                        m_lsText.push_back(pName);
                    }
                    new WText(szLabel, pSubTable->elementAt(nRow, 1));

                    pSubTable->GetRow(nRow)->setStyleClass("padding_top");
                    pSubTable->elementAt(nRow, 0)->setStyleClass("widthbold");
                    pSubTable->elementAt(nRow, 1)->setStyleClass("color_2");
                }
            }
        }
        // 关闭设备模板
        CloseEntityTemplet(objDevice);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 创建操作
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice1st::createOperate()
{
    if(m_pOperate)
    {
        int nRow = m_pOperate->numRows();
        // 取消添加
        CEccButton *pCancel = new CEccButton(SVResString::getResString("IDS_Cancel_Add"), SVResString::getResString("IDS_Cancel_Add_Device_Tip"), 
            "", m_pOperate->elementAt(nRow, 0));
        if(pCancel)
        {
            WObject::connect(pCancel, SIGNAL(clicked()), "showbar();", this, SLOT(Cancel()),
                WObject::ConnectionType::JAVASCRIPTDYNAMIC);
        }

        nRow = static_cast<WTableCell*>(m_pOperate->parent())->row();
        // 底部居中对齐
        elementAt(nRow, 0)->setContentAlignment(AlignBottom | AlignCenter);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 取消添加
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice1st::Cancel()
{
    // 显示主界面
    CEccRightView::showMainForm();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 说明 按设备类型添加新的设备
// 参数
//      选择的设备类型
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice1st::AddDeviceByType(const std::string szType)
{
    // 显示添加设备的第二步
    CEccRightView::showAddDevice2nd(m_szParentId, szType);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 说明 设置父节点
// 参数
//      父节点的索引
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CEccAddDevice1st::setParentID(string szIndex)
{
    m_szParentId = szIndex;
}
