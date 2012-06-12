#include <iostream>
#include "General.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ CGeneral::slots_[] = { WSlot_("ShowEdit()", false), WSlot_("Save()", false), WSlot_("SaveName()", false), WSlot_("Translate()", false), WSlot_("ExChange()", false), WSlot_("ShowHelp()", false), WSlot_() };
WSignal_ CGeneral::signals_[] = { WSignal_() };

void CGeneral::buildSlotMap(WSlotMap& result)
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
void CGeneral::buildSignalMap(WSignalMap& result)
{
  WContainerWidget::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

bool CGeneral::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    ShowEdit();
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    Save();
    return true;
  }
  if (slot == slots_ + 2) {
    sender_ = sender;    SaveName();
    return true;
  }
  if (slot == slots_ + 3) {
    sender_ = sender;    Translate();
    return true;
  }
  if (slot == slots_ + 4) {
    sender_ = sender;    ExChange();
    return true;
  }
  if (slot == slots_ + 5){
	  sender_ = sender;   ShowHelp();
	  return true;
  }
  return WContainerWidget::triggerSlot(sender, slot, args);
}
bool CGeneral::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WContainerWidget::undoTriggerSlot(slot, args);
}
