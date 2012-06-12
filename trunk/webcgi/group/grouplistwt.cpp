#include <iostream>
#include "grouplist.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ SVGroupList::slots_[] = { WSlot_("selAll()", false), WSlot_("selNone()", false), WSlot_("invertSel()", false), WSlot_("delSel()", false), WSlot_("add()", false), WSlot_("editGroup()", false), WSlot_("gotoGroup()", false), WSlot_("changeState()", false), WSlot_("delSelGroup()", false), WSlot_("deleteGroup()", false), WSlot_("enableSelGroup()", false), WSlot_("disableSelGroup()", false), WSlot_("disableGroupSucc()", false), WSlot_("sortGroups()", false), WSlot_() };
WSignal_ SVGroupList::signals_[] = { WSignal_("AddNewGroup()", false), WSignal_("EditGroupByID(string)", false), WSignal_("EnumDeviceByID(string)", false), WSignal_("sortGroupsList(int)", false), WSignal_("ChangeGroupState(string,int)", false), WSignal_("DeleteGroupSucc(string,string)", false), WSignal_("DeleteDeviceSucc(string,string)", false), WSignal_() };

void SVGroupList::buildSlotMap(WSlotMap& result)
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
void SVGroupList::buildSignalMap(WSignalMap& result)
{
  WContainerWidget::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

void SVGroupList::AddNewGroup()
{
  void **args = 0;
  triggerSignal(signals_ + 0, args);
}

void SVGroupList::EditGroupByID(string arg0)
{
  void *args[1] = {(void *)(&arg0)};  triggerSignal(signals_ + 1, args);
}

void SVGroupList::EnumDeviceByID(string arg0)
{
  void *args[1] = {(void *)(&arg0)};  triggerSignal(signals_ + 2, args);
}

void SVGroupList::sortGroupsList(int arg0)
{
  void *args[1] = {(void *)(&arg0)};  triggerSignal(signals_ + 3, args);
}

void SVGroupList::ChangeGroupState(string arg0,int arg1)
{
  void *args[2] = {(void *)(&arg0), (void *)(&arg1)};  triggerSignal(signals_ + 4, args);
}

void SVGroupList::DeleteGroupSucc(string arg0,string arg1)
{
  void *args[2] = {(void *)(&arg0), (void *)(&arg1)};  triggerSignal(signals_ + 5, args);
}

void SVGroupList::DeleteDeviceSucc(string arg0,string arg1)
{
  void *args[2] = {(void *)(&arg0), (void *)(&arg1)};  triggerSignal(signals_ + 6, args);
}

bool SVGroupList::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    selAll();
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    selNone();
    return true;
  }
  if (slot == slots_ + 2) {
    sender_ = sender;    invertSel();
    return true;
  }
  if (slot == slots_ + 3) {
    sender_ = sender;    delSel();
    return true;
  }
  if (slot == slots_ + 4) {
    sender_ = sender;    add();
    return true;
  }
  if (slot == slots_ + 5) {
    sender_ = sender;    editGroup();
    return true;
  }
  if (slot == slots_ + 6) {
    sender_ = sender;    gotoGroup();
    return true;
  }
  if (slot == slots_ + 7) {
    sender_ = sender;    changeState();
    return true;
  }
  if (slot == slots_ + 8) {
    sender_ = sender;    delSelGroup();
    return true;
  }
  if (slot == slots_ + 9) {
    sender_ = sender;    deleteGroup();
    return true;
  }
  if (slot == slots_ + 10) {
    sender_ = sender;    enableSelGroup();
    return true;
  }
  if (slot == slots_ + 11) {
    sender_ = sender;    disableSelGroup();
    return true;
  }
  if (slot == slots_ + 12) {
    sender_ = sender;    disableGroupSucc();
    return true;
  }
  if (slot == slots_ + 13) {
    sender_ = sender;    sortGroups();
    return true;
  }
  return WContainerWidget::triggerSlot(sender, slot, args);
}
bool SVGroupList::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WContainerWidget::undoTriggerSlot(slot, args);
}
