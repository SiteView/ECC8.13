#include <iostream>
#include "AddEmail.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ CSVAddEmail::slots_[] = { WSlot_("Save()", false), WSlot_("Back()", false), WSlot_("Translate()", false), WSlot_("ExChangeAdd()", false), WSlot_("ShowHelp()", false), WSlot_() };
WSignal_ CSVAddEmail::signals_[] = { WSignal_("Successful(ADD_MAIL_OK)", true), WSignal_("BackMain()", true), WSignal_("ExChangeEventAdd()", true), WSignal_() };

void CSVAddEmail::buildSlotMap(WSlotMap& result)
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
void CSVAddEmail::buildSignalMap(WSignalMap& result)
{
  WContainerWidget::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

void CSVAddEmail::Successful(ADD_MAIL_OK arg0)
{
  void *args[1] = {(void *)(&arg0)};  triggerSignal(signals_ + 0, args);
}

void CSVAddEmail::BackMain()
{
  void **args = 0;
  triggerSignal(signals_ + 1, args);
}

void CSVAddEmail::ExChangeEventAdd()
{
  void **args = 0;
  triggerSignal(signals_ + 2, args);
}

bool CSVAddEmail::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    Save();
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    Back();
    return true;
  }
  if (slot == slots_ + 2) {
    sender_ = sender;    Translate();
    return true;
  }
  if (slot == slots_ + 3) {
    sender_ = sender;    ExChangeAdd();
    return true;
  }
  if(slot == slots_ + 4) {
	  sender_ = sender;  ShowHelp();
	  return true;
  }
  return WContainerWidget::triggerSlot(sender, slot, args);
}
bool CSVAddEmail::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WContainerWidget::undoTriggerSlot(slot, args);
}
