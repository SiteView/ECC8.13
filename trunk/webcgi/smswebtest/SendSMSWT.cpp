#include "stdafx.h"
#include <iostream>
#include "SendSMS.h"
#include <WSignal_>
#include <WSignalInstance_>
#include <WSlot_>

#include <WSlotInstance_>

WSlot_ CSVSendSMS::slots_[] = { WSlot_("SendTest()", false), WSlot_("Back()", false), WSlot_("SendMouseMove()", false), WSlot_("Translate()", false), WSlot_("ExChange()", false), WSlot_() };
WSignal_ CSVSendSMS::signals_[] = { WSignal_("BackMailset()", true), WSignal_() };

void CSVSendSMS::buildSlotMap(WSlotMap& result)
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
void CSVSendSMS::buildSignalMap(WSignalMap& result)
{
  WContainerWidget::buildSignalMap(result);
  for (int i = 0; signals_[i].good(); ++i)
    result[signals_[i].name()] = new WSignalInstance_(this, signals_ + i);
}

void CSVSendSMS::BackMailset()
{
  void **args = 0;
  triggerSignal(signals_ + 0, args);
}

bool CSVSendSMS::triggerSlot(WObject *sender, const WSlot_ *slot, void **args)
{
  if (slot == slots_ + 0) {
    sender_ = sender;    SendTest();
    return true;
  }
  if (slot == slots_ + 1) {
    sender_ = sender;    Back();
    return true;
  }
  if (slot == slots_ + 2) {
    sender_ = sender;    SendMouseMove();
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
  return WContainerWidget::triggerSlot(sender, slot, args);
}
bool CSVSendSMS::undoTriggerSlot(const WSlot_ *slot, void **args)
{
  return WContainerWidget::undoTriggerSlot(slot, args);
}
