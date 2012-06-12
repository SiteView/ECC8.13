#include <iostream>
#include "TuopList.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ CTuopList::slots_[] = { WSlot_("EditUserName(const std::string)", false), WSlot_("OpenTuop(const std::string)", false), WSlot_("SelAll()", false), WSlot_("SelNone()", false), WSlot_("SelInvert()", false), WSlot_("BeforeDelUser()", false), WSlot_("DelUser()", false), WSlot_("EditReturn(int)", false), WSlot_("Translate()", false), WSlot_("ExChange()", false), WSlot_("Sort()", false), WSlot_("SortOk()", false), WSlot_() };
WSignal_ CTuopList::signals_[] = { WSignal_() };

void CTuopList::buildSlotMap(WSlotMap& result)
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
void CTuopList::buildSignalMap(WSignalMap& result)
{
  WContainerWidget::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

bool CTuopList::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    EditUserName(*((const std::string *)args[0]));
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    OpenTuop(*((const std::string *)args[0]));
    return true;
  }
  if (slot == slots_ + 2) {
    sender_ = sender;    SelAll();
    return true;
  }
  if (slot == slots_ + 3) {
    sender_ = sender;    SelNone();
    return true;
  }
  if (slot == slots_ + 4) {
    sender_ = sender;    SelInvert();
    return true;
  }
  if (slot == slots_ + 5) {
    sender_ = sender;    BeforeDelUser();
    return true;
  }
  if (slot == slots_ + 6) {
    sender_ = sender;    DelUser();
    return true;
  }
  if (slot == slots_ + 7) {
    sender_ = sender;    EditReturn(*((int *)args[0]));
    return true;
  }
  if (slot == slots_ + 8) {
    sender_ = sender;    Translate();
    return true;
  }
  if (slot == slots_ + 9) {
    sender_ = sender;    ExChange();
    return true;
  }
  if (slot == slots_ + 10) {
    sender_ = sender;    Sort();
    return true;
  }
  if (slot == slots_ + 11) {
    sender_ = sender;    SortOk();
    return true;
  }
  return WContainerWidget::triggerSlot(sender, slot, args);
}
bool CTuopList::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WContainerWidget::undoTriggerSlot(slot, args);
}
