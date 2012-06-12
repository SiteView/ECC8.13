#include <iostream>
#include "MainForm.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ CSVMainForm::slots_[] = { WSlot_("ShowSetForm(std::string)", false), WSlot_("ShowSmsForm()", false), WSlot_("ShowAddForm()", false), WSlot_("Save_Phone(SAVE_REPORT_LIST)", false), WSlot_("Edit_Phone(SAVE_REPORT_LIST)", false), WSlot_("ExChangeRefresh()", false), WSlot_() };
WSignal_ CSVMainForm::signals_[] = { WSignal_() };

void CSVMainForm::buildSlotMap(WSlotMap& result)
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
void CSVMainForm::buildSignalMap(WSignalMap& result)
{
  WTable::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

bool CSVMainForm::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    ShowSetForm(*((std::string *)args[0]));
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    ShowSmsForm();
    return true;
  }
  if (slot == slots_ + 2) {
    sender_ = sender;    ShowAddForm();
    return true;
  }
  if (slot == slots_ + 3) {
    sender_ = sender;    Save_Phone(*((SAVE_REPORT_LIST *)args[0]));
    return true;
  }
  if (slot == slots_ + 4) {
    sender_ = sender;    Edit_Phone(*((SAVE_REPORT_LIST *)args[0]));
    return true;
  }
  if (slot == slots_ + 5) {
    sender_ = sender;    ExChangeRefresh();
    return true;
  }
  return WTable::triggerSlot(sender, slot, args);
}
bool CSVMainForm::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WTable::undoTriggerSlot(slot, args);
}
