#include <iostream>
#include "configpage.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ CSVTopnReportSet::slots_[] = { WSlot_("hideSmsList()", false), WSlot_("showSmsList()", false), WSlot_("hideSmsList1()", false), WSlot_("showSmsList1()", false), WSlot_("hideSmsList2()", false), WSlot_("showSmsList2()", false), WSlot_("ShowSendForm()", false), WSlot_("SelAll()", false), WSlot_("SelNone()", false), WSlot_("SelInvert()", false), WSlot_("BeforeDelPhone()", false), WSlot_("DelPhone()", false), WSlot_("AddPhone()", false), WSlot_("EditRow(const std::string)", false), WSlot_("MainHelp()", false), WSlot_("Translate()", false), WSlot_("ExChange()", false), WSlot_() };
WSignal_ CSVTopnReportSet::signals_[] = { WSignal_("ShowWebSend(string,string)", true), WSignal_("ShowComSend(string)", true), WSignal_("AddNewPhone()", true), WSignal_("EditPhone(SAVE_REPORT_LIST)", true), WSignal_("ExChangeEvent()", true), WSignal_() };

void CSVTopnReportSet::buildSlotMap(WSlotMap& result)
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
void CSVTopnReportSet::buildSignalMap(WSignalMap& result)
{
  WContainerWidget::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

void CSVTopnReportSet::ShowWebSend(string arg0,string arg1)
{
  void *args[2] = {(void *)(&arg0), (void *)(&arg1)};  triggerSignal(signals_ + 0, args);
}

void CSVTopnReportSet::ShowComSend(string arg0)
{
  void *args[1] = {(void *)(&arg0)};  triggerSignal(signals_ + 1, args);
}

void CSVTopnReportSet::AddNewPhone()
{
  void **args = 0;
  triggerSignal(signals_ + 2, args);
}

void CSVTopnReportSet::EditPhone(SAVE_REPORT_LIST arg0)
{
  void *args[1] = {(void *)(&arg0)};  triggerSignal(signals_ + 3, args);
}

void CSVTopnReportSet::ExChangeEvent()
{
  void **args = 0;
  triggerSignal(signals_ + 4, args);
}

bool CSVTopnReportSet::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    hideSmsList();
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    showSmsList();
    return true;
  }
  if (slot == slots_ + 2) {
    sender_ = sender;    hideSmsList1();
    return true;
  }
  if (slot == slots_ + 3) {
    sender_ = sender;    showSmsList1();
    return true;
  }
  if (slot == slots_ + 4) {
    sender_ = sender;    hideSmsList2();
    return true;
  }
  if (slot == slots_ + 5) {
    sender_ = sender;    showSmsList2();
    return true;
  }
  if (slot == slots_ + 6) {
    sender_ = sender;    ShowSendForm();
    return true;
  }
  if (slot == slots_ + 7) {
    sender_ = sender;    SelAll();
    return true;
  }
  if (slot == slots_ + 8) {
    sender_ = sender;    SelNone();
    return true;
  }
  if (slot == slots_ + 9) {
    sender_ = sender;    SelInvert();
    return true;
  }
  if (slot == slots_ + 10) {
    sender_ = sender;    BeforeDelPhone();
    return true;
  }
  if (slot == slots_ + 11) {
    sender_ = sender;    DelPhone();
    return true;
  }
  if (slot == slots_ + 12) {
    sender_ = sender;    AddPhone();
    return true;
  }
  if (slot == slots_ + 13) {
    sender_ = sender;    EditRow(*((const std::string *)args[0]));
    return true;
  }
  if (slot == slots_ + 14) {
    sender_ = sender;    MainHelp();
    return true;
  }
  if (slot == slots_ + 15) {
    sender_ = sender;    Translate();
    return true;
  }
  if (slot == slots_ + 16) {
    sender_ = sender;    ExChange();
    return true;
  }
  return WContainerWidget::triggerSlot(sender, slot, args);
}
bool CSVTopnReportSet::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WContainerWidget::undoTriggerSlot(slot, args);
}
