#include <iostream>
#include "groupview.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ SVGroupview::slots_[] = { WSlot_("MenuItemRequestProc(MENU_REQUEST)", false), WSlot_("backParent()", false), WSlot_("AddNewGroup()", false), WSlot_("EditGroupParam(string)", false), WSlot_("showIconView()", false), WSlot_("showListView()", false), WSlot_("AddGroupData(string,string)", false), WSlot_("EditGroupData(string,string)", false), WSlot_("ChangeGroupState(string,int)", false), WSlot_("showMainView()", false), WSlot_("AddNewDevice()", false), WSlot_("AddDevice2nd(string)", false), WSlot_("EnumDevice(string)", false), WSlot_("EditDeviceByIndex(string)", false), WSlot_("AddNewDeviceSucc(string,string)", false), WSlot_("EditDeviceSuccByID(string,string)", false), WSlot_("ChangeDeviceState(string,int)", false), WSlot_("EnterDeviceByID(string)", false), WSlot_("EnterNewDeviceByID(string)", false), WSlot_("AddMonitor(string,string)", false), WSlot_("CancelAddMonitor()", false), WSlot_("AddNewMonitorByType(int,string)", false), WSlot_("AddMonitorSucc(string,string)", false), WSlot_("EditMonitorSuccByID(string,string)", false), WSlot_("EditMonitorByIndex(string)", false), WSlot_("BackMonitorList()", false), WSlot_("BackGroupDeviceList(string)", false), WSlot_("EditSVSESuccByIndex(string,string)", false), WSlot_("EditSVSEByIndex(string)", false), WSlot_("enterSVSE(string)", false), WSlot_("enterGroup(string)", false), WSlot_("backSVSEView()", false), WSlot_("DelDeviceByIdProc(string,string)", false), WSlot_("DelGroupByIdProc(string,string)", false), WSlot_("BatchAddMonitor()", false), WSlot_("ReloadCurrentView()", false), WSlot_("SortObjects(int)", false), WSlot_("RefreshCurrentList()", false), WSlot_("enterGroupByID(const std::string)", false), WSlot_("Translate()", false), WSlot_("ExChange()", false), WSlot_("CopyNewDeviceSucc(string,string)", false), WSlot_("CopyNewMonitorSucc(string,string)", false), WSlot_() };
WSignal_ SVGroupview::signals_[] = { WSignal_("MenuItemResponse(MENU_RESPONSE)", true), WSignal_("ChangeSelNode(string)", true), WSignal_("TranslateSuccessful()", true), WSignal_() };

void SVGroupview::buildSlotMap(WSlotMap& result)
{
  WContainerWidget::buildSlotMap(result);
  for (int i = 0; slots_[i].good(); ++i)  {
#ifdef WIN32 
	WSlotInstance_ *pw=new WSlotInstance_(this, slots_ + i);	
		std::string strkey=slots_[i].name();	
		WObject::InsertMap(result,strkey,pw);	
#else  
	result[slots_[i].name()] = new WSlotInstance_(this, slots_ + i);
#endif  
	}
}
void SVGroupview::buildSignalMap(WSignalMap& result)
{
  WContainerWidget::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

void SVGroupview::MenuItemResponse(MENU_RESPONSE arg0)
{
  void *args[1] = {(void *)(&arg0)};  triggerSignal(signals_ + 0, args);
}

void SVGroupview::ChangeSelNode(string arg0)
{
  void *args[1] = {(void *)(&arg0)};  triggerSignal(signals_ + 1, args);
}

void SVGroupview::TranslateSuccessful()
{
  void **args = 0;
  triggerSignal(signals_ + 2, args);
}

bool SVGroupview::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    MenuItemRequestProc(*((MENU_REQUEST *)args[0]));
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    backParent();
    return true;
  }
  if (slot == slots_ + 2) {
    sender_ = sender;    AddNewGroup();
    return true;
  }
  if (slot == slots_ + 3) {
    sender_ = sender;    EditGroupParam(*((string *)args[0]));
    return true;
  }
  if (slot == slots_ + 4) {
    sender_ = sender;    showIconView();
    return true;
  }
  if (slot == slots_ + 5) {
    sender_ = sender;    showListView();
    return true;
  }
  if (slot == slots_ + 6) {
    sender_ = sender;    AddGroupData(*((string *)args[0]), *((string *)args[1]));
    return true;
  }
  if (slot == slots_ + 7) {
    sender_ = sender;    EditGroupData(*((string *)args[0]), *((string *)args[1]));
    return true;
  }
  if (slot == slots_ + 8) {
    sender_ = sender;    ChangeGroupState(*((string *)args[0]), *((int *)args[1]));
    return true;
  }
  if (slot == slots_ + 9) {
    sender_ = sender;    showMainView();
    return true;
  }
  if (slot == slots_ + 10) {
    sender_ = sender;    AddNewDevice();
    return true;
  }
  if (slot == slots_ + 11) {
    sender_ = sender;    AddDevice2nd(*((string *)args[0]));
    return true;
  }
  if (slot == slots_ + 12) {
    sender_ = sender;    EnumDevice(*((string *)args[0]));
    return true;
  }
  if (slot == slots_ + 13) {
    sender_ = sender;    EditDeviceByIndex(*((string *)args[0]));
    return true;
  }
  if (slot == slots_ + 14) {
    sender_ = sender;    AddNewDeviceSucc(*((string *)args[0]), *((string *)args[1]));
    return true;
  }
  if (slot == slots_ + 15) {
    sender_ = sender;    EditDeviceSuccByID(*((string *)args[0]), *((string *)args[1]));
    return true;
  }
  if (slot == slots_ + 16) {
    sender_ = sender;    ChangeDeviceState(*((string *)args[0]), *((int *)args[1]));
    return true;
  }
  if (slot == slots_ + 17) {
    sender_ = sender;    EnterDeviceByID(*((string *)args[0]));
    return true;
  }
  if (slot == slots_ + 18) {
    sender_ = sender;    EnterNewDeviceByID(*((string *)args[0]));
    return true;
  }
  if (slot == slots_ + 19) {
    sender_ = sender;    AddMonitor(*((string *)args[0]), *((string *)args[1]));
    return true;
  }
  if (slot == slots_ + 20) {
    sender_ = sender;    CancelAddMonitor();
    return true;
  }
  if (slot == slots_ + 21) {
    sender_ = sender;    AddNewMonitorByType(*((int *)args[0]), *((string *)args[1]));
    return true;
  }
  if (slot == slots_ + 22) {
    sender_ = sender;    AddMonitorSucc(*((string *)args[0]), *((string *)args[1]));
    return true;
  }
  if (slot == slots_ + 23) {
    sender_ = sender;    EditMonitorSuccByID(*((string *)args[0]), *((string *)args[1]));
    return true;
  }
  if (slot == slots_ + 24) {
    sender_ = sender;    EditMonitorByIndex(*((string *)args[0]));
    return true;
  }
  if (slot == slots_ + 25) {
    sender_ = sender;    BackMonitorList();
    return true;
  }
  if (slot == slots_ + 26) {
    sender_ = sender;    BackGroupDeviceList(*((string *)args[0]));
    return true;
  }
  if (slot == slots_ + 27) {
    sender_ = sender;    EditSVSESuccByIndex(*((string *)args[0]), *((string *)args[1]));
    return true;
  }
  if (slot == slots_ + 28) {
    sender_ = sender;    EditSVSEByIndex(*((string *)args[0]));
    return true;
  }
  if (slot == slots_ + 29) {
    sender_ = sender;    enterSVSE(*((string *)args[0]));
    return true;
  }
  if (slot == slots_ + 30) {
    sender_ = sender;    enterGroup(*((string *)args[0]));
    return true;
  }
  if (slot == slots_ + 31) {
    sender_ = sender;    backSVSEView();
    return true;
  }
  if (slot == slots_ + 32) {
    sender_ = sender;    DelDeviceByIdProc(*((string *)args[0]), *((string *)args[1]));
    return true;
  }
  if (slot == slots_ + 33) {
    sender_ = sender;    DelGroupByIdProc(*((string *)args[0]), *((string *)args[1]));
    return true;
  }
  if (slot == slots_ + 34) {
    sender_ = sender;    BatchAddMonitor();
    return true;
  }
  if (slot == slots_ + 35) {
    sender_ = sender;    ReloadCurrentView();
    return true;
  }
  if (slot == slots_ + 36) {
    sender_ = sender;    SortObjects(*((int *)args[0]));
    return true;
  }
  if (slot == slots_ + 37) {
    sender_ = sender;    RefreshCurrentList();
    return true;
  }
  if (slot == slots_ + 38) {
    sender_ = sender;    enterGroupByID(*((const std::string *)args[0]));
    return true;
  }
  if (slot == slots_ + 39) {
    sender_ = sender;    Translate();
    return true;
  }
  if (slot == slots_ + 40) {
    sender_ = sender;    ExChange();
    return true;
  }
  if (slot == slots_ + 41) {
    sender_ = sender;    CopyNewDeviceSucc(*((string *)args[0]), *((string *)args[1]));
    return true;
  }
  if (slot == slots_ + 42) {
    sender_ = sender;    CopyNewMonitorSucc(*((string *)args[0]), *((string *)args[1]));
    return true;
  }
  return WContainerWidget::triggerSlot(sender, slot, args);
}
bool SVGroupview::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WContainerWidget::undoTriggerSlot(slot, args);
}
