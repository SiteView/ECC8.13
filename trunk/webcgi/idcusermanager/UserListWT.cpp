#include <iostream>
#include "UserList.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ CUserList::slots_[] = { WSlot_("AddUser()", false), WSlot_("BeforeDelUser()", false), WSlot_("DelUser()", false), WSlot_("SelAll()", false), WSlot_("EditUser(const std::string)", false), WSlot_("SelNone()", false), WSlot_("SelInvert()", false), WSlot_("SaveUser()", false), WSlot_("CancelUser()", false), WSlot_("Translate()", false), WSlot_("ExChange()", false), WSlot_("SelIDCBtn()", false), WSlot_("SelWeiHuBtn()", false), WSlot_("SelSysWeihuBtn()", false), WSlot_("SelYeWuBtn()", false), WSlot_("SelXiaoShouBtn()", false), WSlot_("SelChangShangBtn()", false), WSlot_("SelGuanMoBtn()", false), WSlot_() };
WSignal_ CUserList::signals_[] = { WSignal_() };

void CUserList::buildSlotMap(WSlotMap& result)
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
void CUserList::buildSignalMap(WSignalMap& result)
{
  WContainerWidget::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

bool CUserList::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    AddUser();
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    BeforeDelUser();
    return true;
  }
  if (slot == slots_ + 2) {
    sender_ = sender;    DelUser();
    return true;
  }
  if (slot == slots_ + 3) {
    sender_ = sender;    SelAll();
    return true;
  }
  if (slot == slots_ + 4) {
    sender_ = sender;    EditUser(*((const std::string *)args[0]));
    return true;
  }
  if (slot == slots_ + 5) {
    sender_ = sender;    SelNone();
    return true;
  }
  if (slot == slots_ + 6) {
    sender_ = sender;    SelInvert();
    return true;
  }
  if (slot == slots_ + 7) {
    sender_ = sender;    SaveUser();
    return true;
  }
  if (slot == slots_ + 8) {
    sender_ = sender;    CancelUser();
    return true;
  }
  if (slot == slots_ + 9) {
    sender_ = sender;    Translate();
    return true;
  }
  if (slot == slots_ + 10) {
    sender_ = sender;    ExChange();
    return true;
  }
  if (slot == slots_ + 11) {
    sender_ = sender;    SelIDCBtn();
    return true;
  }
  if (slot == slots_ + 12) {
    sender_ = sender;    SelWeiHuBtn();
    return true;
  }
  if (slot == slots_ + 13) {
    sender_ = sender;    SelSysWeihuBtn();
    return true;
  }
  if (slot == slots_ + 14) {
    sender_ = sender;    SelYeWuBtn();
    return true;
  }
  if (slot == slots_ + 15) {
    sender_ = sender;    SelXiaoShouBtn();
    return true;
  }
  if (slot == slots_ + 16) {
    sender_ = sender;    SelChangShangBtn();
    return true;
  }
  if (slot == slots_ + 17) {
    sender_ = sender;    SelGuanMoBtn();
    return true;
  }
  return WContainerWidget::triggerSlot(sender, slot, args);
}
bool CUserList::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WContainerWidget::undoTriggerSlot(slot, args);
}
