#include <iostream>
#include "PlanSet.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ CSVPlanSet::slots_[] = { WSlot_("hidePlanList()", false), WSlot_("showPlanList()", false), WSlot_("Save()", false), WSlot_("AddPlan()", false), WSlot_("BeforeDelPlan()", false), WSlot_("DelPlan()", false), WSlot_("SelAll()", false), WSlot_("EditPlan(const std::string)", false), WSlot_("hidePlanList1()", false), WSlot_("showPlanList1()", false), WSlot_("Save1()", false), WSlot_("AddPlan1()", false), WSlot_("BeforeDelPlan1()", false), WSlot_("DelPlan1()", false), WSlot_("SelAll1()", false), WSlot_("EditPlan1(const std::string)", false), WSlot_("SelNone()", false), WSlot_("SelNone1()", false), WSlot_("SelInvert()", false), WSlot_("SelInvert1()", false), WSlot_("AdjustAbsDelState()", false), WSlot_("AdjustRangeDelState()", false), WSlot_() };
WSignal_ CSVPlanSet::signals_[] = { WSignal_("SaveSuccessful(SEND_MAIL_PARAM)", true), WSignal_("AddNewPlan()", true), WSignal_("EditPlanList(ADD_PLAN_OK)", true), WSignal_("SaveSuccessful1(SEND_MAIL_PARAM)", true), WSignal_("AddNewPlan1()", true), WSignal_("EditPlanList1(ADD_PLAN_OK)", true), WSignal_() };

void CSVPlanSet::buildSlotMap(WSlotMap& result)
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
void CSVPlanSet::buildSignalMap(WSignalMap& result)
{
  WContainerWidget::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

void CSVPlanSet::SaveSuccessful(SEND_MAIL_PARAM arg0)
{
  void *args[1] = {(void *)(&arg0)};  triggerSignal(signals_ + 0, args);
}

void CSVPlanSet::AddNewPlan()
{
  void **args = 0;
  triggerSignal(signals_ + 1, args);
}

void CSVPlanSet::EditPlanList(ADD_PLAN_OK arg0)
{
  void *args[1] = {(void *)(&arg0)};  triggerSignal(signals_ + 2, args);
}

void CSVPlanSet::SaveSuccessful1(SEND_MAIL_PARAM arg0)
{
  void *args[1] = {(void *)(&arg0)};  triggerSignal(signals_ + 3, args);
}

void CSVPlanSet::AddNewPlan1()
{
  void **args = 0;
  triggerSignal(signals_ + 4, args);
}

void CSVPlanSet::EditPlanList1(ADD_PLAN_OK arg0)
{
  void *args[1] = {(void *)(&arg0)};  triggerSignal(signals_ + 5, args);
}

bool CSVPlanSet::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    hidePlanList();
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    showPlanList();
    return true;
  }
  if (slot == slots_ + 2) {
    sender_ = sender;    Save();
    return true;
  }
  if (slot == slots_ + 3) {
    sender_ = sender;    AddPlan();
    return true;
  }
  if (slot == slots_ + 4) {
    sender_ = sender;    BeforeDelPlan();
    return true;
  }
  if (slot == slots_ + 5) {
    sender_ = sender;    DelPlan();
    return true;
  }
  if (slot == slots_ + 6) {
    sender_ = sender;    SelAll();
    return true;
  }
  if (slot == slots_ + 7) {
    sender_ = sender;    EditPlan(*((const std::string *)args[0]));
    return true;
  }
  if (slot == slots_ + 8) {
    sender_ = sender;    hidePlanList1();
    return true;
  }
  if (slot == slots_ + 9) {
    sender_ = sender;    showPlanList1();
    return true;
  }
  if (slot == slots_ + 10) {
    sender_ = sender;    Save1();
    return true;
  }
  if (slot == slots_ + 11) {
    sender_ = sender;    AddPlan1();
    return true;
  }
  if (slot == slots_ + 12) {
    sender_ = sender;    BeforeDelPlan1();
    return true;
  }
  if (slot == slots_ + 13) {
    sender_ = sender;    DelPlan1();
    return true;
  }
  if (slot == slots_ + 14) {
    sender_ = sender;    SelAll1();
    return true;
  }
  if (slot == slots_ + 15) {
    sender_ = sender;    EditPlan1(*((const std::string *)args[0]));
    return true;
  }
  if (slot == slots_ + 16) {
    sender_ = sender;    SelNone();
    return true;
  }
  if (slot == slots_ + 17) {
    sender_ = sender;    SelNone1();
    return true;
  }
  if (slot == slots_ + 18) {
    sender_ = sender;    SelInvert();
    return true;
  }
  if (slot == slots_ + 19) {
    sender_ = sender;    SelInvert1();
    return true;
  }
  if (slot == slots_ + 20) {
    sender_ = sender;    AdjustAbsDelState();
    return true;
  }
  if (slot == slots_ + 21) {
    sender_ = sender;    AdjustRangeDelState();
    return true;
  }
  return WContainerWidget::triggerSlot(sender, slot, args);
}
bool CSVPlanSet::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WContainerWidget::undoTriggerSlot(slot, args);
}
