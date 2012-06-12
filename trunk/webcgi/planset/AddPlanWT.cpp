#include <iostream>
#include "AddPlan.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ CSVAddPlan::slots_[] = { WSlot_("Save()", false), WSlot_("Cancel()", false), WSlot_("hidePlanList()", false), WSlot_("showPlanList()", false), WSlot_("AhidePlanList()", false), WSlot_("AshowPlanList()", false), WSlot_("AddPlanHelp()", false), WSlot_() };
WSignal_ CSVAddPlan::signals_[] = { WSignal_("Successful(ADD_PLAN_OK)", true), WSignal_("SCancel()", true), WSignal_() };

void CSVAddPlan::buildSlotMap(WSlotMap& result)
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
void CSVAddPlan::buildSignalMap(WSignalMap& result)
{
  WContainerWidget::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

void CSVAddPlan::Successful(ADD_PLAN_OK arg0)
{
  void *args[1] = {(void *)(&arg0)};  triggerSignal(signals_ + 0, args);
}

void CSVAddPlan::SCancel()
{
  void **args = 0;
  triggerSignal(signals_ + 1, args);
}

bool CSVAddPlan::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    Save();
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    Cancel();
    return true;
  }
  if (slot == slots_ + 2) {
    sender_ = sender;    hidePlanList();
    return true;
  }
  if (slot == slots_ + 3) {
    sender_ = sender;    showPlanList();
    return true;
  }
  if (slot == slots_ + 4) {
    sender_ = sender;    AhidePlanList();
    return true;
  }
  if (slot == slots_ + 5) {
    sender_ = sender;    AshowPlanList();
    return true;
  }
  if (slot == slots_ + 6) {
    sender_ = sender;    AddPlanHelp();
    return true;
  }
  return WContainerWidget::triggerSlot(sender, slot, args);
}
bool CSVAddPlan::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WContainerWidget::undoTriggerSlot(slot, args);
}
WSlot_ CSVAddAbsolutePlan::slots_[] = { WSlot_("Save1()", false), WSlot_("Cancel1()", false), WSlot_("hidePlanList1()", false), WSlot_("showPlanList1()", false), WSlot_("AhidePlanList1()", false), WSlot_("AshowPlanList1()", false), WSlot_("AddPlanHelp()", false), WSlot_() };
WSignal_ CSVAddAbsolutePlan::signals_[] = { WSignal_("Successful(ADD_PLAN_OK)", true), WSignal_("SCancel1()", true), WSignal_() };

void CSVAddAbsolutePlan::buildSlotMap(WSlotMap& result)
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
void CSVAddAbsolutePlan::buildSignalMap(WSignalMap& result)
{
  WContainerWidget::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

void CSVAddAbsolutePlan::Successful(ADD_PLAN_OK arg0)
{
  void *args[1] = {(void *)(&arg0)};  triggerSignal(signals_ + 0, args);
}

void CSVAddAbsolutePlan::SCancel1()
{
  void **args = 0;
  triggerSignal(signals_ + 1, args);
}

bool CSVAddAbsolutePlan::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    Save1();
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    Cancel1();
    return true;
  }
  if (slot == slots_ + 2) {
    sender_ = sender;    hidePlanList1();
    return true;
  }
  if (slot == slots_ + 3) {
    sender_ = sender;    showPlanList1();
    return true;
  }
  if (slot == slots_ + 4) {
    sender_ = sender;    AhidePlanList1();
    return true;
  }
  if (slot == slots_ + 5) {
    sender_ = sender;    AshowPlanList1();
    return true;
  }
  if (slot == slots_ + 6) {
    sender_ = sender;    AddPlanHelp();
    return true;
  }
  return WContainerWidget::triggerSlot(sender, slot, args);
}
bool CSVAddAbsolutePlan::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WContainerWidget::undoTriggerSlot(slot, args);
}
