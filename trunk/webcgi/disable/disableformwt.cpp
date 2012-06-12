#include <iostream>
#include "disableform.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ SVDisableForm::slots_[] = { WSlot_("ShowHelp()", false), WSlot_("Disable()", false), WSlot_("ShowHideTemporary()", false), WSlot_("cancel()", false), WSlot_("eventConfirm()", false), WSlot_("Translate()", false), WSlot_("ExChange()", false), WSlot_("ViewLog()", false), WSlot_() };
WSignal_ SVDisableForm::signals_[] = { WSignal_() };

void SVDisableForm::buildSlotMap(WSlotMap& result)
{
  WTable::buildSlotMap(result);
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
void SVDisableForm::buildSignalMap(WSignalMap& result)
{
  WTable::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

bool SVDisableForm::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    ShowHelp();
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    Disable();
    return true;
  }
  if (slot == slots_ + 2) {
    sender_ = sender;    ShowHideTemporary();
    return true;
  }
  if (slot == slots_ + 3) {
    sender_ = sender;    cancel();
    return true;
  }
  if (slot == slots_ + 4) {
    sender_ = sender;    eventConfirm();
    return true;
  }
  if (slot == slots_ + 5) {
    sender_ = sender;    Translate();
    return true;
  }
  if (slot == slots_ + 6) {
    sender_ = sender;    ExChange();
    return true;
  }
  if (slot == slots_ + 7) {
    sender_ = sender;    ViewLog();
    return true;
  }
  return WTable::triggerSlot(sender, slot, args);
}
bool SVDisableForm::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WTable::undoTriggerSlot(slot, args);
}
