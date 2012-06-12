#include <iostream>
#include "AddReport.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ CSVAddReport::slots_[] = { WSlot_("Back()", false), WSlot_("Save()", false), WSlot_("hideAddPhoneList()", false), WSlot_("showAddPhoneList()", false), WSlot_("hideAddReport()", false), WSlot_("showAddReport()", false), WSlot_("AddPhoneHelp()", false), WSlot_("TestSMS()", false), WSlot_("TestSMSing()", false), WSlot_("Translate()", false), WSlot_("ExChangeAdd()", false), WSlot_("ShowHelp()", false), WSlot_() };
WSignal_ CSVAddReport::signals_[] = { WSignal_("BackTo(std::string)", true), WSignal_("SavePhone(SAVE_REPORT_LIST)", true), WSignal_("ExChangeAddEvent()", true), WSignal_() };

void CSVAddReport::buildSlotMap(WSlotMap& result)
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
void CSVAddReport::buildSignalMap(WSignalMap& result)
{
  WContainerWidget::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

void CSVAddReport::BackTo(std::string arg0)
{
  void *args[1] = {(void *)(&arg0)};  triggerSignal(signals_ + 0, args);
}

void CSVAddReport::SavePhone(SAVE_REPORT_LIST arg0)
{
  void *args[1] = {(void *)(&arg0)};  triggerSignal(signals_ + 1, args);
}

void CSVAddReport::ExChangeAddEvent()
{
  void **args = 0;
  triggerSignal(signals_ + 2, args);
}

bool CSVAddReport::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    Back();
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    Save();
    return true;
  }
  if (slot == slots_ + 2) {
    sender_ = sender;    hideAddPhoneList();
    return true;
  }
  if (slot == slots_ + 3) {
    sender_ = sender;    showAddPhoneList();
    return true;
  }
  if (slot == slots_ + 4) {
    sender_ = sender;    hideAddReport();
    return true;
  }
  if (slot == slots_ + 5) {
    sender_ = sender;    showAddReport();
    return true;
  }
  if (slot == slots_ + 6) {
    sender_ = sender;    AddPhoneHelp();
    return true;
  }
  if (slot == slots_ + 7) {
    sender_ = sender;    TestSMS();
    return true;
  }
  if (slot == slots_ + 8) {
    sender_ = sender;    TestSMSing();
    return true;
  }
  if (slot == slots_ + 9) {
    sender_ = sender;    Translate();
    return true;
  }
  if (slot == slots_ + 10) {
    sender_ = sender;    ExChangeAdd();
    return true;
  }
  if (slot == slots_ + 11) {
	  sender_ = sender;    ShowHelp();
	  return true;
  }
  return WContainerWidget::triggerSlot(sender, slot, args);
}
bool CSVAddReport::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WContainerWidget::undoTriggerSlot(slot, args);
}
