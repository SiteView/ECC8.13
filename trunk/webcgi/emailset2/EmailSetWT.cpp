#include <iostream>
#include "EmailSet.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ CSVEmailSet::slots_[] = { WSlot_("Save()", false), WSlot_("AddEmail()", false), WSlot_("BeforeDelEmail()", false), WSlot_("DelEmail()", false), WSlot_("EditMail(int)", false), WSlot_("SelInvert()", false), WSlot_("SelAll()", false), WSlot_("SelNone()", false), WSlot_("Translate()", false), WSlot_("ExChange()", false),WSlot_("ShowHelp()", false), WSlot_() };
WSignal_ CSVEmailSet::signals_[] = { WSignal_("SaveSuccessful(SEND_MAIL_PARAM)", true), WSignal_("AddNewMail()", true), WSignal_("EditMailList(ADD_MAIL_OK)", true), WSignal_("ExChangeEvent()", true), WSignal_() };

void CSVEmailSet::buildSlotMap(WSlotMap& result)
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
void CSVEmailSet::buildSignalMap(WSignalMap& result)
{
  WContainerWidget::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

void CSVEmailSet::SaveSuccessful(SEND_MAIL_PARAM arg0)
{
  void *args[1] = {(void *)(&arg0)};  triggerSignal(signals_ + 0, args);
}

void CSVEmailSet::AddNewMail()
{
  void **args = 0;
  triggerSignal(signals_ + 1, args);
}

void CSVEmailSet::EditMailList(ADD_MAIL_OK arg0)
{
  void *args[1] = {(void *)(&arg0)};  triggerSignal(signals_ + 2, args);
}

void CSVEmailSet::ExChangeEvent()
{
  void **args = 0;
  triggerSignal(signals_ + 3, args);
}

bool CSVEmailSet::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    Save();
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    AddEmail();
    return true;
  }
  if (slot == slots_ + 2) {
    sender_ = sender;    BeforeDelEmail();
    return true;
  }
  if (slot == slots_ + 3) {
    sender_ = sender;    DelEmail();
    return true;
  }
  if (slot == slots_ + 4) {
    sender_ = sender;    EditMail(*((int *)args[0]));
    return true;
  }
  if (slot == slots_ + 5) {
    sender_ = sender;    SelInvert();
    return true;
  }
  if (slot == slots_ + 6) {
    sender_ = sender;    SelAll();
    return true;
  }
  if (slot == slots_ + 7) {
    sender_ = sender;    SelNone();
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
  if(slot == slots_ + 10)
  {
	  sender_ = sender;  ShowHelp();
	  return true;
  }
  return WContainerWidget::triggerSlot(sender, slot, args);
}
bool CSVEmailSet::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WContainerWidget::undoTriggerSlot(slot, args);
}
