#include <iostream>
#include "MainForm.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ CMainForm::slots_[] = { WSlot_("Forword()", false), WSlot_("showAddform()", false), WSlot_("SaveNewPlanList(ADD_PLAN_OK)", false), WSlot_("EditNewPlanList(ADD_PLAN_OK)", false), WSlot_("CancelAdd()", false), WSlot_("showAddform1()", false), WSlot_("SaveNewPlanList1(ADD_PLAN_OK)", false), WSlot_("EditNewPlanList1(ADD_PLAN_OK)", false), WSlot_("CancelAdd1()", false), WSlot_("Translate()", false), WSlot_("ExChange()", false), WSlot_() };
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
    sender_ = sender;    SaveNewPlanList(*((ADD_PLAN_OK *)args[0]));
    return true;
  }
  if (slot == slots_ + 3) {
    sender_ = sender;    EditNewPlanList(*((ADD_PLAN_OK *)args[0]));
    return true;
  }
  if (slot == slots_ + 4) {
    sender_ = sender;    CancelAdd();
    return true;
  }
  if (slot == slots_ + 5) {
    sender_ = sender;    showAddform1();
    return true;
  }
  if (slot == slots_ + 6) {
    sender_ = sender;    SaveNewPlanList1(*((ADD_PLAN_OK *)args[0]));
    return true;
  }
  if (slot == slots_ + 7) {
    sender_ = sender;    EditNewPlanList1(*((ADD_PLAN_OK *)args[0]));
    return true;
  }
  if (slot == slots_ + 8) {
    sender_ = sender;    CancelAdd1();
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
  return WTable::triggerSlot(sender, slot, args);
}
bool CMainForm::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WTable::undoTriggerSlot(slot, args);
}
