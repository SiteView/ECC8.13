#include <iostream>
#include "MainForm.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ CMainForm::slots_[] = { WSlot_("Forword()", false), WSlot_("showAddform()", false), WSlot_("SaveNewMailList(ADD_MAIL_OK)", false), WSlot_("EditNewMailList(ADD_MAIL_OK)", false), WSlot_("BackFromAdd()", false), WSlot_("ExChangeRefresh()", false), WSlot_() };
WSignal_ CMainForm::signals_[] = { WSignal_() };

void CMainForm::buildSlotMap(WSlotMap& result)
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
void CMainForm::buildSignalMap(WSignalMap& result)
{
  WTable::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

bool CMainForm::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    Forword();
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    showAddform();
    return true;
  }
  if (slot == slots_ + 2) {
    sender_ = sender;    SaveNewMailList(*((ADD_MAIL_OK *)args[0]));
    return true;
  }
  if (slot == slots_ + 3) {
    sender_ = sender;    EditNewMailList(*((ADD_MAIL_OK *)args[0]));
    return true;
  }
  if (slot == slots_ + 4) {
    sender_ = sender;    BackFromAdd();
    return true;
  }
  if (slot == slots_ + 5) {
    sender_ = sender;    ExChangeRefresh();
    return true;
  }
  return WTable::triggerSlot(sender, slot, args);
}
bool CMainForm::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WTable::undoTriggerSlot(slot, args);
}
